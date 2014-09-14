//
//  MutexImp.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Mutex.hpp"

namespace NordicArts {
    namespace NordicOS {
        MutexImp::MutexImp() {
            pthread_mutexattr_t tAttributes;
            pthread_mutexattr_init(&tAttributes);
            pthread_mutexattr_settype(&tAttributes, PTHREAD_MUTEX_RECURSIVE);
            
            pthread_mutex_init(&m_tMutex, &tAttributes);
        }
        
        MutexImp::~MutexImp() {
            pthread_mutex_destroy(&m_tMutex);
        }
        
        void MutexImp::lock() {
            pthread_mutex_lock(&m_tMutex);
        }
        void MutexImp::unlock() {
            pthread_mutex_unlock(&m_tMutex);
        }
    };
};
