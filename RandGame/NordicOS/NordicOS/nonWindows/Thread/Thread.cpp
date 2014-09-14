//
//  ThreadImp.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Thread.hpp"
#include "../../Thread/Thread.hpp"
#include <iostream>
#include <cassert>

namespace NordicArts {
    namespace NordicOS {
        ThreadImp::ThreadImp(Thread *pOwner) : m_bActive(true) {
            m_bActive = pthread_create(&m_tThread, NULL, &ThreadImp::entryPoint, pOwner) == 0;
            
            if (!m_bActive) {
                std::cerr << "Failed to create thread" << std::endl;
            }
        }
        
        void ThreadImp::wait() {
            if (m_bActive) {
                assert(pthread_equal(pthread_self(), m_tThread) == 0);
                pthread_join(m_tThread, NULL);
            }
        }
        
        void ThreadImp::terminate() {
            if (m_bActive) {
                pthread_kill(m_tThread, SIGUSR1);
            }
        }
        
        void *ThreadImp::entryPoint(void *pUserData) {
            Thread *pOwner = static_cast<Thread*>(pUserData);
            
            pOwner->run();
            
            return NULL;
        }
    };
};