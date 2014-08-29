#include "./Mutex.hpp"

namespace NordicArts {
    namespace NordicOS {
        int mutexInit(MUTEX_THREAD *pMutex) {
            #if defined(nonWindows)
                return pthread_mutex_init(pMutex, NULL);
            #else
                *pMutex = CreateMutex(0, FALSE, 0);
                return (*pMutex == 0);
            #endif

            return -1;
        }

        int mutexLock(MUTEX_THREAD *pMutex) { 
            #if defined(nonWindows)
                return pthread_mutex_lock(pMutex);
            #else
                return (WaitForSingleObject(*pMutex, INFINITE) == (WAIT_FAILED ? 1 : 0));
            #endif

            return -1;
        }

        int mutexUnlock(MUTEX_THREAD *pMutex) {
            #if defined(nonWindows)
                return pthread_mutex_unlock(pMutex);
            #else
                return (ReleaseMutex(*pMutex) == 0);
            #endif

            return -1;
        }
    };
};
