//
//  Mutex.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Mutex_H
#define NordicArts_NordicOS_Mutex_H

#include "../OS.hpp"
#include "../NonCopyable/NonCopyable.hpp"

namespace NordicArts {
    namespace NordicOS {
        class Mutex : NonCopyable {
        // Variables
        public:
        protected:
        private:
            MutexImp *m_oMutexImp;
            
        // Methods
        public:
            Mutex();
            ~Mutex();
            
            void lock();
            void unlock();
            
        protected:
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__Mutex__) */
