#ifndef _KERNEL_DEFS_MACROS_H_
#define _KERNEL_DEFS_MACROS_H_

#define CONCAT(A,B)         A ## B
#define EXPAND_CONCAT(A,B)  CONCAT(A, B)

#define ARGN(N, LIST)       EXPAND_CONCAT(ARG_, N) LIST
#define ARG_0(A0, ...)                                              A0
#define ARG_1(A0, A1, ...)                                          A1
#define ARG_2(A0, A1, A2, ...)                                      A2
#define ARG_3(A0, A1, A2, A3, ...)                                  A3
#define ARG_4(A0, A1, A2, A3, A4, ...)                              A4
#define ARG_5(A0, A1, A2, A3, A4, A5, ...)                          A5
#define ARG_6(A0, A1, A2, A3, A4, A5, A6, ...)                      A6
#define ARG_7(A0, A1, A2, A3, A4, A5, A6, A7, ...)                  A7
#define ARG_8(A0, A1, A2, A3, A4, A5, A6, A7, A8, ...)              A8
#define ARG_9(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, ...)          A9
#define ARG_10(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, ...)    A10

// Prevents annoying 'defined but not used' warning
#define UNUSED(x) (void)(x)

#define HLT volatile asm("hlt")
#define CLI volatile asm("cli")

#define STOP CLI && HLT

#define NULL (void)(0x00)

#endif