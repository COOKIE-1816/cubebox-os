/*
	This file are a headers for serial port drivers
	using UART protocol (UART interface).
*/

#ifndef SERIAL_H
#define SERIAL_H

#include "kernel/irq/irqdef.h"
#include "kernel/kernel.h"
#include <string.h>

#define BAUDRATE_DEFAULT 115200

/*
	ADDRESS INACCURACY PROBLEMS
	=============================
	These first two ports are always on the
	address, as provided here. Other ports 
	also should be, but it is actually not 
	too reliable.
	
	See https://wiki.osdev.org/Serial_Ports#Port_Addresses
	
	Also reccommend to see 
	https://upload.wikimedia.org/wikipedia/commons/1/1f/Serial_Programming.pdf
*/

#define COM1	0x3F8
#define COM2	0x2F8
#define COM3	0x3E8
#define COM4	0x2E8
#define COM5	0x5F8
#define COM6	0x4F8
#define COM7	0x5E8
#define COM8	0x4E8
// #define ALL  	0xFFF

/*
#define SERIAL_OFFSET_CMD_DISABLE_IRQ 0x00
#define SERIAL_OFFSET_CMD_DLAB_ENABLE 0x03
*/

extern int serial_com1com2only;

void serial_init();

int serial_received(u16 __port);
char serial_read(u16 __port);

int serial_isReady(u16 __port);
void serial_write(u16 __port, char __value);

void serial_writeString(u16 __port, String __string);

/*
	Checks, if serial port's communication chip operates
	correctly using UART protocol (interface).
	
	Returns 0 if UART chip operates correctly.
	Returns 1 otherwise.
	
	Checked by sending test packet, then waiting for 
	response. If target responds by same packet,
	everything is fine.
*/
int serial_checkFaultyPort(u16 __port);

/*
	SERIAL DATA TRANSMISSION DIRECTORY
	====================================
	From master device perspective.
	
	RX:		Receive 	| <-
	TX:		Transmit	| ->
*/

#define SERIAL_RX 0x01
#define SERIAL_TX 0x02

typedef struct {
	u8 	data;
	int	direction;
} serial_record_packet;

typedef struct {
	size_t length;
	u16		port;
	
	serial_record_packet packets[0xffff];
} serial_record;

void serial_record_startRecording(	u16 __port, 
									int __record_length, 
									int __record_directions
);

void serial_record_pauseRecording(u16 __port);
serial_record serial_record_stopRecording(u16 __port);

void serial_record_replay(		int __start,
								int __end,
								int __replay_directions,
								serial_record __record);
							
void serial_record_replay_on(	u16 __port,
								int __start,
								int __end,
								int __replay_directions,
								serial_record __record);

#endif