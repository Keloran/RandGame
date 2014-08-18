#ifndef NORDICARTS_OS_H
#define NORDICARTS_OS_H

#include "./buildNumber.hpp"
#include "./OSLoad.hpp"

// OS Specific Includes
#if defined(__APPLE_CC__) || defined(__APPLE__)
    #define NordicArtsOSX true
    #include "./OSX/OSX.hpp"
    #include "./nonWindows/nonWindows.hpp"
#endif

#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #define NordicArtsWindows true
    #include "./Windows/Windows.hpp"
#endif

#if defined(__LINUX__) || defined(linux) || defined(__linux__)
    #define NordicArtsLinux true
    #include "./Linux/Linux.hpp"
    #include "./nonWindows/nonWindows.hpp"
#endif

// ExceptionHandler
#include "./ExceptionHandler/ExceptionHandler.hpp"

// SQLite
extern "C" {
    #include <sqlite3.h>
}

#endif
