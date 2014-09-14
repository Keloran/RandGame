//
//  Sleep.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Sleep.hpp"

#if defined(NordicOS_Windows)
    #include "../Windows/Sleep/Sleep.hpp"
#else
    #include "../nonWindows/Sleep/Sleep.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        void Sleep(Time oDuration) {
            if (oDuration >= Time::Zero) {
                sleepImp(oDuration);
            }
        }
    };
};
