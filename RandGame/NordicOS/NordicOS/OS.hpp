#ifndef NordicArts_NordicOS_H
#define NordicArts_NordicOS_H

#include "./buildNumber.hpp"
#include "./OSLoad.hpp"

// OS Specific Includes
#if defined (__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #include "./Windows/Windows.hpp"
#else
    #include "./nonWindows/nonWindows.hpp"

    #if defined(__APPLE__) || defined(__APPLE_CC__)
        #include "./OSX/OSX.hpp"
    #else
        #include "./Linux/Linux.hpp"
    #endif
#endif

// ExceptionHandler
#include "./ExceptionHandler/ExceptionHandler.hpp"

// SQLite
extern "C" {
//    #include <sqlite3.h>
}

namespace NordicArts {
    namespace NordicOS {
        const char *getBuildNumber();
    };
};

#endif
