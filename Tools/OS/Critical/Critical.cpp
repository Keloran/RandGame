#include "./Critical.hpp"

namespace NordicArts {
    void createCritical(NA_CRITICAL &oCritical) {
        #if defined(nonWindows)
            pthread_mutexattr_t mAttr;
            pthread_mutexattr_settype(&mAttr, PTHREAD_RECURSIVE_NA);
            pthread_mutex_init(&oCritical, &mAttr);
            pthread_mutexattr_destroy(&mAttr);
        #else 
            InitalizeCriticalSection(&oCritical);
        #endif
    }

    void enterCritical(NA_CRITICAL &oCritical) {
        #if defined(nonWindows)
            pthread_mutex_lock(&oCritical);
        #else
            EnterCriticalSection(&oCritical);
        #endif
    }

    void leaveCritical(NA_CRITICAL &oCritical) {
        #if defined(nonWindows)
            pthread_mutex_unlock(&oCritical);
        #else
            LeaveCriticalSection(&oCritical);
        #endif
    }

    void deleteCritical(NA_CRITICAL &oCritical) {
        #if defined(nonWindows)
            pthread_mutex_unlock(&oCritical);
            pthread_mutex_destroy(&oCritical);
        #else
            DeleteCriticalSection(&oCritical);
        #endif
    }
};
