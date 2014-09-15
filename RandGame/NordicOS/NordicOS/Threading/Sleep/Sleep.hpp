//
//  Sleep.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Sleep_H
#define NordicArts_NordicOS_Sleep_H

#include "../OS.hpp"
#include "../Time/Time.hpp"

namespace NordicArts {
    namespace NordicOS {
        void sleep(Time oDuration);
    };
};

#endif /* defined(__NordicOS__Sleep__) */
