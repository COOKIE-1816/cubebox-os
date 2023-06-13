;============================================================= FILE INFORMATION =============================================================
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/crt/crti.s
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       i686 ELF assembly
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 CRTI
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
;    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-45 UTC
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

.section .init
.global _init
.type _init, @function
_init:
	push %ebp
	movl %esp, %ebp

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %ebp
	movl %esp, %ebp

	