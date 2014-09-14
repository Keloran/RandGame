//
//  Mutex.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Mutex.hpp"

namespace NordicArts {
    namespace NordicOS {
        Mutex::Mutex() {
            m_oMutexImp = new MutexImp();
        }
        
        Mutex::~Mutex() {
            delete m_oMutexImp;
        }
        
        void Mutex::lock() {
            m_oMutexImp->lock();
        }
        
        void Mutex::unlock() {
            m_oMutexImp->unlock();
        }
    };
};
