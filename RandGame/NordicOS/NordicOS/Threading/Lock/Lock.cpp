//
//  Lock.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Lock.hpp"
#include "../Mutex/Mutex.hpp"

namespace NordicArts {
    namespace NordicOS {
        Lock::Lock(Mutex &oMutex) : m_oMutex(oMutex) {
            m_oMutex.lock();
        }
        
        Lock::~Lock() {
            m_oMutex.unlock();
        }
    };
};
