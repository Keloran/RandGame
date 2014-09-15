#ifndef NordicArts_NordicOS_MutexImp_H
#define NordicArts_NordicOS_MutexImp_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include <windows.h>

namespace NordicArts {
    namespace NordicOS {
        class MutexImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            CRITICAL_SECTION m_hMutex;

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

#endif
