//
//  ThreadLocal.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_ThreadLocalImp_H
#define NordicArts_NordicOS_ThreadLocalImp_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"

namespace NordicArts {
    namespace NordicOS {
        class ThreadLocalImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            pthread_key_t m_tKey;
            
        // Methods
        public:
            ThreadLocalImp();
            ~ThreadLocalImp();
            
            void setValue(void *pValue);
            
            void *getValue() const;
            
        protected:
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__ThreadLocal__) */
