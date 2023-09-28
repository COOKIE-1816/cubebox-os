#include "kernel/gdt.h"
#include "kernel/terminal.h"
#include "kernel/kmsg.h"
#include "kernel/panic.h"
#include <stdio.h>

struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_setGate(	int 			__num, 
					unsigned long 	__base, 
					unsigned long 	__limit, 
					unsigned char 	__access, 
					unsigned char 	__granularity
) {
	if(__limit > 0xFFFFFFFF) {
		kmsg(KMSG_LVL_ERROR, "GDT", "GDT limit too large.");
		panic("GDT_ENCODE_FAIL");
		
		// Actually never reached
		return;
	}
	
    gdt[__num].base_low = 		(__base 		& 0xFFFF);
    gdt[__num].base_middle = 	(__base >> 16) 	& 0xFF;
    gdt[__num].base_high = 		(__base >> 24) 	& 0xFF;

    gdt[__num].limit_low = 		( __limit 		& 0xFFFF);
    gdt[__num].granularity = 	((__limit >> 16)& 0x0F);

    gdt[__num].granularity |= 	(__granularity & 0xF0);
    gdt[__num].access = __access;
}

void gdt_install() {
	size_t sizeOfStruct = sizeof(/*struct*/ /*gdt_entry*/ gdt[0]);
	
    gp.limit = (sizeOfStruct * 3) - 1;
    gp.base = &gdt;

    gdt_setGate(0x00, 0x00, 0x00000000, 0x00, 0x00);
    gdt_setGate(0x01, 0x00, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_setGate(0x02, 0x00, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush();
	
	terminal_wstring("Global Descriptor Table (GDT) set up.\n");
}