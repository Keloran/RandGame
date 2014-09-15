//
//  ThreadLocal.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//
#ifndef NordicArts_NordicOS_ThreadLocal_H
#define NordicArts_NordicOS_ThreadLocal_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include <cstdlib>

namespace NordicArts {
    namespace NordicOS {
        class ThreadLocalImp;
        
        class ThreadLocal : NonCopyable {
        // Variables
        public:
        protected:
        private:
            ThreadLocalImp *m_pImp;
            
        // Methods
        public:
            ThreadLocal(void *pValue = NULL);
            ~ThreadLocal();
            
            void setValue(void *pValue);
            
            void *getValue() const;
            
        protected:
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__ThreadLocal__) */
