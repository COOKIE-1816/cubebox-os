#ifndef _CB_KERNEL_H
#define _CB_KERNEL_H

#define KERNEL_UNSTABLE
#define KVERSION "0.0.1.0a"

struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

#endif