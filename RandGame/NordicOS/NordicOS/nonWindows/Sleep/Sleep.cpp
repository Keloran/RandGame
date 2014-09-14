//
//  SleepImp.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Sleep.hpp"

namespace NordicArts {
    namespace NordicOS {
        void sleepImp(Time oTime) {
            uint64_t iSecs = oTime.getMicroSeconds();
            
            timespec ti;
            
            ti.tv_nsec  = ((iSecs % 100000) * 1000);
            ti.tv_sec   = (iSecs / 100000);
            
            while ((nanosleep(&ti, &ti) == -1) && (errno == EINTR)) {
                
            }
        }
    };
};