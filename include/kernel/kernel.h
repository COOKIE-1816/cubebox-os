#ifndef _CB_KERNEL_H
#define _CB_KERNEL_H

#define KERNEL_UNSTABLE // Says that kernel release is unstable
#define KVERSION "0.0.1.0a" // Defines kernel version string



struct regs {
/*
				This struct defines the regs struct
				containing register data.
*/
	unsigned int gs, 
															fs, 
															es, 
															ds;
															
	unsigned int edi, 
															esi, 
															ebp, 
															esp, 
															ebx, 
															edx, 
															ecx, 
															eax;
															
	unsigned int int_no, 
															err_code;
															
	unsigned int eip, 
															cs, 
															eflags, 
															useresp, 
															ss;
};

#endif