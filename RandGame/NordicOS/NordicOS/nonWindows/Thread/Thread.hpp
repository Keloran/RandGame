//
//  ThreadImp.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_ThreadImp_H
#define NordicArts_NordicOS_ThreadImp_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include <pthread.h>

namespace NordicArts {
    namespace NordicOS {
        class Thread;
        
        class ThreadImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            pthread_t m_tThread;
            
            bool m_bActive;
            
        // Methods
        public:
            ThreadImp(Thread *pOwner);
            
            void wait();
            void terminate();
            
        protected:
        private:
            static void *entryPoint(void *pUserData);
            
        };
    };
};

#endif /* defined(__NordicOS__ThreadImp__) */
