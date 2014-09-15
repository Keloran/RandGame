#ifndef NordicArts_NordicOS_ThreadImp_H
#define NordicArts_NordicOS_ThreadImp_H

#include "../../NonCopyable.hpp"
#include <windows.h>

namespace NordicArts {
    namespace NordicOS {
        class Thread;

        class ThreadImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            static unsigned int __stdcall entryPoint(void *pUserData);

            HANDLE m_hThread;

            unsigned int m_iThreadID;

        // Methods
        public:
            ThreadImp(Thread *pOwner);
            ~ThreadImp();

            void wait();
            void terminate();

        protected:
        private:

        };
    };
};

#endif
