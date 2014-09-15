//
//  Mutex.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Mutex.hpp"

#if defined(NordicOS_Windows)
    #include "../../Windows/Mutex/Mutex.hpp"
#else
    #include "../../nonWindows/Mutex/Mutex.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        Mutex::Mutex() {
            m_pMutexImp = new MutexImp;
        }
        
        Mutex::~Mutex() {
            delete m_pMutexImp;
        }
        
        void Mutex::lock() {
            m_pMutexImp->lock();
        }
        
        void Mutex::unlock() {
            m_pMutexImp->unlock();
        }
    };
};