#include "drivers/serial/serial.h"
#include "kernel/interrupts.h"
#include "kernel/common/io.h"
#include "kernel/terminal.h"
#include "kernel/kmsg.h"

/*
	Stores 1, if waiting for a response to a test packet.
	Purpose is to prevent incorrect behaivour of serial 
	communication.
*/

int serial_com1com2only = 1;

int activeOngoingTestReq = 0;

static u16 _ports[8] = {
	COM1, COM2, COM3, COM4,
	COM5, COM6, COM7, COM8
};

static String _portNames[8] = {
	"COM1", "COM2", "COM3", "COM4",
	"COM5", "COM6", "COM7", "COM8"
};

int serial_checkFaultyPort(u16 __port) {
	activeOngoingTestReq = 1;
	
	// After sending test packet (0xAE), target device
	// should give the same response, if everything
	// works fine.
	outb(__port + 0, 0xAE);
	u8 faulty = inb(__port + 0) ;
	
	activeOngoingTestReq = 0;
	
	/*
	if(__port == COM1 || __port == COM2)
		_record_irq(__port, SERIAL_RX, 0xAE);
	*/
	
	if(faulty == 0) {
		// No connection
		return 2;
	}
	
	if(faulty != 0xAE)
		return 1;
	
	return 0;
}

void _init__port(u16 __port, int __iterator) {
	outb(__port + 0x01, 0x00);
	outb(__port + 0x03, 0x80);
	outb(__port + 0x00, 0x03);
	outb(__port + 0x01, 0x00);
	outb(__port + 0x03, 0x03);
	outb(__port + 0x02, 0xC7);
	outb(__port + 0x04, 0x0B);
	outb(__port + 0x04, 0x1E);
 
	// Check if specified port and client device operates correctly.
	int isFaulty = serial_checkFaultyPort(__port);
	if(isFaulty != 0x00) {
		/*kmsg(KMSG_LVL_WARNING, "Serial", "Writing SERIAL_TEST command resulted with incorrect response.");*/
		
		// No response = no connection.
		if(isFaulty == 2)
			return;
		
		// Connected, but bad response.
		terminal_wstring("WARN [Serial] ");
		terminal_wstring(_portNames[__iterator]);
		terminal_wstring(": Serial port test resulted with incorrect response.\n");
		
		return;
	}
 
	outb(__port + 4, 0x0F);
}

static void _irq_com1(void);
static void _irq_com2(void);

void serial_init() {
	int ports;
	
	if(serial_com1com2only) {
		ports = 2;
	} else {
		ports = 8;
	}
	
	for(int i = 0; i < ports; i++) {
		_init__port(_ports[i], i);
	}
	
	idt_installHandler(IRQ_COM1, &_irq_com1);
	idt_installHandler(IRQ_COM2, &_irq_com2);
	
	//idt_enable();
	
	/*
	idt_setDescriptor(IRQ_COM1, &_irq_com1, 0x8E);
	idt_setDescriptor(IRQ_COM2, &_irq_com2, 0x8E);
	*/
	
	if(serial_com1com2only) {
		terminal_wstring("Initialized serial COM1 - COM2. Interface: UART\n");
	} else {
		terminal_wstring("Initialized serial COM1 - COM8. Interface: UART\n");		
	}
	
	// terminal_wstring("Debug port set to COM1.\n");
}

int serial_received(u16 __port) {
	return inb(__port + 0x05) & 0x01;
}

char serial_read(u16 __port) {
	while (serial_received(__port) == 0x00);
	return inb(__port);
}

int serial_isReady(u16 __port) {
	return inb(__port + 0x05) & 0x20;
}

void serial_write(u16 __port, char __value) {
	while (serial_isReady(__port) == 0x00);
	outb(__port, (u8) __value);
	
	if(__port == COM1 || __port == COM2)
		_record_irq(__port, SERIAL_TX, __value);
}

void serial_writeString(u16 __port, String __string) {
	size_t length = sizeof(__string) / sizeof(__string[0]);
	
	for(size_t i = 0; i < length; i++) {
		serial_write(__port, __string[i]);
	}
}

/*
	===========================================================
	============== SERIAL PORT TRANSSCRIPT RECORD =============
	===========================================================
*/

int _com1_recording 	= 0;
int _com2_recording 	= 0;

int _com1_pause 		= 0;
int _com2_pause 		= 0;

int _com1_record_packet	= 0;
int _com2_record_packet	= 0;

int _com1_record_packet_max;
int _com2_record_packet_max;

int _com1_record_directions;
int _com2_record_directions;

static char 	_com1_record_data[0xFFFF];
static char	_com2_record_data[0xFFFF];

static int 	_com1_record_dirs[0xFFFF];
static int 	_com2_record_dirs[0xFFFF];


int _isRecording(u16 __port) {
	if(__port == COM1)
		return _com1_recording && (!_com1_pause);
	if(__port == COM2)
		return _com2_recording && (!_com2_pause);
	
	return 0;
}

serial_record serial_record_stopRecording(u16 __port) {
	serial_record record;
	
	if(__port == COM1) {
		terminal_wstring("Stopped recording transmissions on serial port COM1.");
		_com1_recording = 0;
		
		record.length = _com1_record_packet + 1;
		
		for(int idx = 0; idx < _com1_record_packet; idx++) {
			serial_record_packet packet;
			
			packet.data 		= _com1_record_data[idx];
			packet.direction 	= _com1_record_dirs[idx];
			
			record.packets[idx] = packet;
		}
	}
	
	if(__port == COM2) {
		terminal_wstring("Stopped recording transmissions on serial port COM2.");
		_com1_recording = 0;
		
		record.length = _com2_record_packet + 1;
		
		for(int idx = 0; idx < _com2_record_packet; idx++) {
			serial_record_packet packet;
			
			packet.data 		= _com2_record_data[idx];
			packet.direction 	= _com2_record_dirs[idx];
			
			record.packets[idx] = packet;
		}
	}
	
	record.port = __port;
	return record;
}

void _record_irq_com1(int __direction, char __data) {
	_com1_record_dirs[_com1_record_packet] = __direction;
	_com1_record_data[_com1_record_packet] = __data;
	
	if(_com1_record_packet == _com1_record_packet_max) {
		serial_record_stopRecording(COM1);
		return;
	}
	
	_com1_record_packet++;
}

void _record_irq_com2(int __direction, char __data) {
	_com1_record_dirs[_com2_record_packet] = __direction;
	_com1_record_data[_com2_record_packet] = __data;
	
	if(_com2_record_packet == _com2_record_packet_max) {
		serial_record_stopRecording(COM2);
		return;
	}
	
	_com2_record_packet++;
}

void _record_irq(u16 __port, int __direction, char __data) {
	if(_isRecording(__port)) {
		if(__port == COM1)
			_record_irq_com1(__direction, __data);
		
		if(__port == COM2)
			_record_irq_com2(__direction, __data);
	}
}

void serial_record_startRecording(	u16 __port, 
									int __record_length, 
									int __record_directions
									){
	if(__port != COM1 && __port != COM2) {
		kmsg(KMSG_LVL_ERROR, "Serial", "Serial port specified does not support recording.");
		return;
	}
	
	if(__record_length < 0x0001 || __record_length > 0xFFFF) {
		kmsg(KMSG_LVL_WARNING, "Serial", "Invaild record length. Procceding with 0xFFFF.");
		__record_length = 0xFFFF;
	}
	
	if(	__record_directions != SERIAL_RX &&
		__record_directions != SERIAL_TX &&
		__record_directions != SERIAL_RX + SERIAL_TX)
		{
			kmsg(KMSG_LVL_WARNING, "Serial", "Invaild record directories. Procceding with SERIAL_RX+SERIAL_TX.");
			__record_directions = SERIAL_TX + SERIAL_RX; // 0x03
		}
		
	if(__port == COM1) {
		terminal_wstring("Started recording transmissions of serial port COM1.\n");
		
		// _com1_record_packetsLeft = 	__record_length;
		_com2_record_packet = 		0;
		
		_com1_record_directions = 	__record_directions;
		_com1_pause =				0;
		_com1_recording = 			1;
	}
	
	if(__port == COM2) {
		terminal_wstring("Started recording transmissions of serial port COM2.\n");
		
		// _com2_record_packetsLeft = 	__record_length;
		_com2_record_packet = 		0;
		
		_com2_record_directions = 	__record_directions;
		_com2_pause =				0;
		_com2_recording = 			1;
	}
	
	
}

/*
	===========================================================
	============= SERIAL PORT INTERRUPT HANDLERS ==============
	===========================================================
*/

void _irq_com1() {
	char data = serial_read(COM1);
	if(data == (char) 0xAE && activeOngoingTestReq == 0) {
		kmsg(KMSG_LVL_INFORMATION, "Serial", "Received test request on COM1. Confirming.\n");
		serial_write(COM1, 0xAE);
	}
	
	_record_irq(COM1, SERIAL_RX, data);
}

void _irq_com2() {
	char data = serial_read(COM2);
	if(data == (char) 0xAE && activeOngoingTestReq == 0) {
		kmsg(KMSG_LVL_INFORMATION, "Serial", "Received test request on COM2. Confirming.\n");
		serial_write(COM2, 0xAE);
	}
	
	_record_irq(COM1, SERIAL_RX, data);
}