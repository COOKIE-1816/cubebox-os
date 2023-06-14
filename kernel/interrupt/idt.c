/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/interrupt/idt.c
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Interrupt Descriptor Table (IDT) implementation
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-56 UTC
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
    @@@@@@@@@@@@@&                          ,@@@@@@@                           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          File usage:                 Vaclav Hajsman
    @@@@@@@@@@@@@&                                          Contributors:               
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          Docs. reference:            
    @@@@@@@@@@@@@&                                          Online reference:           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          Copyright (C) Vaclav Hajsman (A.K.A. COOKIE) 2023. All rights reserved.
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          This file is licensed as a part of the project inself, and licensing information
    @@@@@@@@@@@@@&                                          Can be found in LICENSE file in root directory of this project.
============================================================================================================================================
*/

#include "kernel/interrupt/idt.h"

#define false 0
#define true 1

uint8_t* vectors;
InterruptDescriptor interruptVectorTable[IDT_MAX_DESCRIPTORS];

void idt_setDescriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &interruptVectorTable[vector];
 
    descriptor->isr_low        = (uint32_t) isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t) isr >> 16;
    descriptor->reserved       = 0;
}

void idt_init() {
//    uint8_t* vectors;

    idtr.base = (uintptr_t) &interruptVectorTable[0];
    idtr.limit = (uint16_t) sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_setDescriptor(vector, isr_stubTable[vector], 0x8E);
        vectors[vector] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}

inline void setVect(uint8_t __vector, InterruptHandler __handler) {
    InterruptDescriptor* _interruptDescriptor = &interruptVectorTable[__vector];
    uint32_t handler_address = (uint32_t) __handler;

    _interruptDescriptor->isr_low    = handler_address & 0xFFFF;
    _interruptDescriptor->kernel_cs  = 0x0008;
    _interruptDescriptor->reserved   = 0;
    _interruptDescriptor->attributes = 0x8E;
    _interruptDescriptor->isr_high   = (handler_address >> 16) & 0xFFFF;
}