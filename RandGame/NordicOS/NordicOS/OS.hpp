#ifndef NordicArts_NordicOS_H
#define NordicArts_NordicOS_H

#include "./buildNumber.hpp"
#include "./OSLoad.hpp"

// Interesting error display
#define printIt(variable) { std::cout << #variable << " " << variable << std::endl; }

// OS Specific Includes
#if defined (__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #include "./Windows/Windows.hpp"
    #define NordicOS_Windows
#else
    #include "./nonWindows/nonWindows.hpp"

    #if defined(__APPLE__) || defined(__APPLE_CC__)
        #include "./OSX/OSX.hpp"
        #define NordicOS_OSX
    #else
        #include "./Linux/Linux.hpp"
        #define NordicOS_Linux
    #endif
#endif

// ExceptionHandler
#include "./ExceptionHandler/ExceptionHandler.hpp"

// SQLite
extern "C" {
    #include <sqlite3.h>
}

namespace NordicArts {
    namespace NordicOS {
        typedef signed char INT8;
        typedef unsigned char UINT8;
        
        typedef signed short INT16;
        typedef unsigned short UINT16;
        
        typedef signed int INT32;
        typedef unsigned int UINT32;
        
        typedef signed long long INT64;
        typedef unsigned long long UINT64;
        
        const char *getBuildNumber();
    };
};

#endif
