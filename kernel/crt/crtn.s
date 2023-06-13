;============================================================= FILE INFORMATION =============================================================
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
;                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/crt/crtn.s
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       i686 ELF Assembly
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 CRTN
;           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
;    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-47 UTC
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
	popl %ebp
	ret

.section .fini
	popl %ebp
	ret

    