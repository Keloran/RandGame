#ifndef NordicArts_NordicOS_Mutex_H
#define NordicArts_NordicOS_Mutex_H

#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {
        #ifndef MUTEX_THREAD
            #if defined(nonWindows)
                #define MUTEX_THREAD pthread_mutex_t
            #else
                #define MUTEX_THREAD HANDLE
            #endif
        #endif

        int mutexInit(MUTEX_THREAD *pMutex);
        int mutexLock(MUTEX_THREAD *pMutex);
        int mutexUnlock(MUTEX_THREAD *pMutex);
    };
};

#endif
