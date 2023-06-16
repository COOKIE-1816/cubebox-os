;============================================================= FILE INFORMATION =============================================================
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/keyboard/i86_keyboard_irq_asm.asm
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       Netwide Assembler
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 The assembler part of i86_keyboard_irq_asm function
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
;    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 15-12 UTC
;    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
;    @@@@@@@@@@@@@&                          ,@@@@@@@                           
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                          File usage:                 
;    @@@@@@@@@@@@@&                                          Contributors:               Vaclav Hajsman
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                          Docs. reference:            
;    @@@@@@@@@@@@@&                                          Online reference:           
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                          Copyright (C) Vaclav Hajsman (A.K.A. COOKIE) 2023. All rights reserved.
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                                             
;    @@@@@@@@@@@@@&                                          This file is licensed as a part of the project inself, and licensing information
;    @@@@@@@@@@@@@&                                          Can be found in LICENSE file in root directory of this project.
;============================================================================================================================================

section .text
extern i86_keyboard_irq_asm

i86_keyboard_irq_asm:
    sti
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop edx
    pop ecx
    pop eax
    ret
