/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /drivers/keyboard/kbderr.h
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C (header)
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 A header file which defines keyboard driver error
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           			codes.
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              13-06-2023, 13-09 UTC
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
    @@@@@@@@@@@@@&                          ,@@@@@@@                           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          File usage:                 
    @@@@@@@@@@@@@&                                          Contributors:               Vaclav Hajsman
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

#ifndef _CB_KBD_KBDERR_H_
#define _CB_KBD_KBDERR_H_

enum keyboard_ERROR {
	keyboard_ERR_BUF_OVERRUN    =	0,
	keyboard_ERR_ID_RET			=	0x83AB,
	keyboard_ERR_BAT			=	0xAA,
	keyboard_ERR_ECHO_RET		=	0xEE,
	keyboard_ERR_ACK			=	0xFA,
	keyboard_ERR_BAT_FAILED		=	0xFC,
	keyboard_ERR_DIAG_FAILED	=	0xFD,
	keyboard_ERR_RESEND_CMD		=	0xFE,
	keyboard_ERR_KEY			=	0xFF
};

#endif