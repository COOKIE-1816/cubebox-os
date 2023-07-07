#ifndef _CB_SYSTEM_H_
#define _CB_SYSTEM_H_

#define KERNEL_UNAME "CubeBoxOS"
#define KERNEL_VERSION_STRING "0.0.1.0a"

#define asm __asm__
#define volatile __volatile__

#define PAUSE   { asm volatile ("hlt"); }
#define STOP while (1) { PAUSE; }


namespace Kernel {
    namespace System {
        typedef struct regs {
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
        } regs;

        void shutdown();
        void reboot();
    };
};




#endif