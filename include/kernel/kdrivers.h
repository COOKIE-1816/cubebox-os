/*
============================================================= FILE INFORMATION =============================================================
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%            
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product name:               CubeBox OS
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               Product version:            0.0.1.0a, Alpha stage - unstable
                 .@@@@@@@@@@@@@@@@@@@@@@@@@@%               
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File name & path:           /kernel/kdrivers.h
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        Programming language:       C (header)
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@        File usage:                 kdrivers header
           @@@@@@@@@@@@@#             %@@@@@@@@@@@@@                           
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision:              
    @@@@@@@@@@@@@&                          ,@@@@@@@        Last revision describtion:  
    @@@@@@@@@@@@@&                          ,@@@@@@@                           
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                                             
    @@@@@@@@@@@@@&                                          File usage:                 
    @@@@@@@@@@@@@&                                          Contributors:               
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

#ifndef _CB_KDRIVERS_H_
#define _CB_KDRIVERS_H_

#include "stringt.h"

#define KDRIVERS_PENDING 0
#define KDRIVERS_FAIL 1
#define KDRIVERS_OK 2

namespace Kernel {
    namespace Kdrivers {
        typedef int (*fnPtr_int)  (int[3]);
        typedef void (*fnPtr_void)(int[3]);

        typedef struct kdriver {
            bool used;
            String name;

            int attributes[3];

            fnPtr_int load;
            fnPtr_int load_auto;
            fnPtr_void unload;
        } kdriver;

        /*kdriver driversloaded[1024];
        bool driversaddressesusage[1024];*/

        void statusMsg_create(kdriver __drv);
        void statusMsg_status(/*kdriver __drv, */ const int __status);
        void init();
    };
};



#endif