//
//  ThreadLocal.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./ThreadLocal.hpp"

namespace NordicArts {
    namespace NordicOS {
        ThreadLocalImp::ThreadLocalImp() {
            pthread_key_create(&m_tKey, NULL);
        }
        
        ThreadLocalImp::~ThreadLocalImp() {
            pthread_key_delete(m_tKey);
        }
        
        void ThreadLocalImp::setValue(void *pValue) {
            pthread_setspecific(m_tKey, pValue);
        }
        
        void *ThreadLocalImp::getValue() const {
            return pthread_getspecific(m_tKey);
        }
    };
};
