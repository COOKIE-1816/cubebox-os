;============================================================= FILE INFORMATION =============================================================
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/gdt/gdt.asm
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       Netwide Assembler
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 Global Desrciptor Table (GDT) Flush function
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
;    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-49 UTC
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

bits 32

[GLOBAL gdt_flush]

gdt_flush:
   mov eax, [esp+4]
   lgdt [eax]

   mov ax, 0x10 
   mov ds, ax 
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax

   jmp 0x08:.flush
   
.flush:
   ret