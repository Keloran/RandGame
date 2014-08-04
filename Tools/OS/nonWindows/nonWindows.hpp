#ifndef NORDICARTS_OS_NONWINDOWS_H
#define NORDICARTS_OS_NONWINDOWS_H

// Make sure we should be compiling this on nonWindows
#include "../OSLoad.hpp"

#if defined(nonWindows)
    #include <pthread.h>
    #include <sched.h>
    #include <mutex>
    
    // Void
    typedef void *PVOID; // Void
    typedef void *LPVOID; // Void

    // Handles
    typedef PVOID HANDLE; // Object Handle
    typedef HANDLE HWND; // Window Handle
    typedef HANDLE HINSTANCE; // Handle Instance
    typedef HANDLE HDC; // Device Handle
    
    // String
    typedef wchar_t WCHAR;
    typedef const char *LPCSTR;
    typedef char *LPSTR;
    typedef const WCHAR *LPCWSTR;

    // Word
    typedef unsigned short WORD;
    typedef unsigned long DWORD;

    // Security
    typedef struct _SECURITY_ATTRIBUTES {
        DWORD  nLength;
        LPVOID lpSecurityDescriptor;
        bool   bInheritHandle;} 
    SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES; // Security

    // String
    #ifdef UNICODE
        typedef LPCWSTR LPCTSTR;
    #else
        typedef LPCSTR LPCTSTR;
    #endif

    // Critical Section
    #ifndef NA_CRITICAL
        #define NA_CRITICAL pthread_mutex_t
    #endif
    #ifndef MUTEX_THREAD
        #define MUTEX_THREAD NA_CRITICAL
    #endif

    // Threads
    #if defined(PTHREAD_MUTEX_RECURSIVE_NP)
        #define PTHREAD_RECURSIVE_NA PTHREAD_MUTEX_RECURSIVE_NP
    #else
        #define PTHREAD_RECURSIVE_NA PTHREAD_MUTEX_RECURSIVE
    #endif
    
    // Time
    #ifndef NA_TIME
        #define NA_TIME time_t
    #endif
    #ifndef NA_TIMEINFO
        #define NA_TIMEINFO tm
    #endif
#endif

#endif
