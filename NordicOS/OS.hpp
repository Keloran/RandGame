#ifndef NORDICARTS_OS_H
#define NORDICARTS_OS_H

// OS Specific Includes
#if defined(__APPLE_CC__) || defined(__APPLE__)
    #define NordicArtsOSX true
    #include "./NordicOS/OSX/OSX.hpp"
    #include "./NordicOS/nonWindows/nonWindows.hpp"
#endif

#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #define NordicArtsWindows true
    #include "./NordicOS/Windows/Windows.hpp"
#endif

#if defined(__LINUX__) || defined(linux) || defined(__linux__)
    #define NordicArtsLinux true
    #include "./NordicOS/Linux/Linux.hpp"
    #include "./NordicOS/nonWindows/nonWindows.hpp"
#endif

// Time
#include "./NordicOS/Time/Time.hpp"
#include "./NordicOS/String/String.hpp"
#include "./NordicOS/Logger/Logger.hpp"

#endif
