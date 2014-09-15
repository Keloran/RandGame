//
//  Thread.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Thread.hpp"

#if defined(__WIN32__) || defined(_WIN64)
    #include "../Windows/Thread/Thread.hpp"
#else
    #include "../nonWindows/Thread/Thread.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        Thread::~Thread() {
            wait();
            
            delete m_pEntryPoint;
        }
        
        void Thread::launch() {
            wait();
            
            m_pImp = new ThreadImp(this);
        }
        
        void Thread::wait() {
            if (m_pImp) {
                m_pImp->wait();
                delete m_pImp;
                
                m_pImp = NULL;
            }
        }
        
        void Thread::terminate() {
            if (m_pImp) {
                m_pImp->terminate();
                delete m_pImp;
                m_pImp = NULL;
            }
        }
        
        void Thread::run() {
            m_pEntryPoint->run();
        }
    };
};
