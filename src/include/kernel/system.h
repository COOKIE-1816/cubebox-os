#ifndef _CB_SYSTEM_H_
#define _CB_SYSTEM_H_

void shutdown();
void reboot();

typedef struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
} regs;

#endif