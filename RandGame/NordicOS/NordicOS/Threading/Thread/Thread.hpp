//
//  Thread.h
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Thread_H
#define NordicArts_NordicOS_Thread_H

#include "../OS.hpp"
#include "../NonCopyable/NonCopyable.hpp"

namespace NordicArts {
    namespace NordicOS {
        class ThreadImp;
        struct ThreadFunc;
        
        class Thread : NonCopyable {
        // Variables
        public:
        protected:
        private:
            friend class ThreadImp;
            
            ThreadImp   *m_pImp;
            ThreadFunc  *m_pEntryPoint;
            
        // Methods
        public:
            template <typename F>
            Thread(F function);
            
            template <typename F, typename A>
            Thread(F function, A argument);
            
            template <typename C>
            Thread(void(C::*function)(), C *object);
            
            ~Thread();
            
            void launch();
            void wait();
            void terminate();
            
        protected:
        private:
            void run();
            
        };
        
        #include "./Thread.inl"
    };
};

#endif /* defined(__NordicOS__Thread__) */
