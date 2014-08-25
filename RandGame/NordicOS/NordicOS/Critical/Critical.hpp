#ifndef NordicArts_NordicOS_Critical_H
#define NordicArts_NordicOS_Critical_H

#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {
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
};

#endif
