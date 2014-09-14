//
//  MutexImp.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_MutexImp_H
#define NordicArts_NordicOS_MutexImp_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include <pthread.h>

namespace NordicArts {
    namespace NordicOS {
        class MutexImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            pthread_mutex_t m_tMutex;
            
        // Methods
        public:
            MutexImp();
            ~MutexImp();
            
            void lock();
            void unlock();
            
        protected:
        private:
            
        };
    };
};


#endif /* defined(__NordicOS__MutexImp__) */
