//
//  Lock.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Lock_H
#define NordicArts_NordicOS_Lock_H

#include "../OS.hpp"
#include "../NonCopyable/NonCopyable.hpp"

namespace NordicArts{
    namespace NordicOS {
        class Mutex;
        
        class Lock : NonCopyable {
        // Variables
        public:
        protected:
        private:
            Mutex &m_oMutex;
            
        // Methods
        public:
            explicit Lock(Mutex &oMutex);
            
            ~Lock();
            
        protected:
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__Lock__) */
