#ifndef NORDICARTS_OS_CRITICAL_H
#define NORDICARTS_OS_CRITICAL_H

#include "../OS.hpp"
#include "../OSLoad.hpp"

namespace NordicArts {
    #ifndef NA_CRITICAL
        #if defined(nonWindows)
            #define NA_CRITICAL pthread_mutex_t
        #else
            #define NA_CRITICAL CRITICAL_SECTION
        #endif
    #endif

    void createCritical(NA_CRITICAL &oCritical);
    void enterCritical(NA_CRITICAL &oCritical);
    void leaveCritical(NA_CRITICAL &oCritical);
    void deleteCritical(NA_CRITICAL &oCritical);
};

#endif
