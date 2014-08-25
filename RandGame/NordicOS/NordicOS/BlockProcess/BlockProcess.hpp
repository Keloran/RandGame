#ifndef NordicArts_NordicOS_BlockProcess_H
#define NordicArts_NordicOS_BlockProcess_H

#include "../OS.hpp"

#include "../Mutex/Mutex.hpp"
#ifndef MUTEX_THREAD
    #if defined(nonWindows)
        #define MUTEX_THREAD pthread_mutex_t
    #else
        #define MUTEX_THREAD HANDLE
    #endif
#endif

namespace NordicArts {
    namespace NordicOS {
        class BlockProcess final {
            // Variables
            public:
                MUTEX_THREAD m_pMutex;

            protected:
            private:

            // Methods
            public:
                explicit BlockProcess(const std::string &cName);
                ~BlockProcess();
    
                bool isBlocked();

            protected:
            private:
                BlockProcess(const BlockProcess &cConst);
                BlockProcess &operator=(const BlockProcess &cConst);
        };
    };
};

#endif
