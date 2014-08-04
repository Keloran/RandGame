#ifndef NORDICARTS_OS_WINDOWS_H
#define NORDICARTS_OS_WINDOWS_H

// Make sure its Windows
#include "../OSLoad.hpp"

#if !defined(nonWindows)
    // Strip lots of rubbish from windows builds
    #define VC_EXTRALEAN

    // System
    #include <windows.h>
    #include <conio.h>
    #include <tchar.h>
    #include <process.h>

    // MUTEX_THREAD is really a HANDLE on Windows
    typedef HANDLE MUTEX_THREAD;

    // Time
    typedef SYSTEMTIME NA_TIME;
    typedef NULL NA_TIMEINFO;

    // Critical Section
    typedef CRITICAL_SECTION NA_CRITICAL;

    namespace NordicArts {
        class OSSpecific {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                std::string ResourcePath(std::string cFileName);

            protected:
            private:
            
        };
    };
#endif

#endif
