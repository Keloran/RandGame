#ifndef NORDICARTS_OS_MUTEX_H
#define NORDICARTS_OS_MUTEX_H

#include "../../OS.hpp"
#include "../../OSLoad.hpp"

namespace NordicArts {
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

#endif
