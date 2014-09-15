//
//  Threads.cpp
//  NordicOS
//
//  Created by Max Hooton on 31/08/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Threads.hpp"

namespace NordicArts {
    namespace NordicOS {
        // Critical
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
        
        // Mutex
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
        int mutexUnLock(MUTEX_THREAD *pMutex) {
            #if defined(nonWindows)
                return pthread_mutex_unlock(pMutex);
            #else
                return (ReleaseMutex(*pMutex) == 0);
            #endif
            
            return -1;
        }
        
        // Block Process
        BlockProcess::BlockProcess(const std::string &cName) : m_cName(cName) {
            mutexInit(&m_pMutex);
        }
        BlockProcess::~BlockProcess() {
            mutexUnLock(&m_pMutex);
        }
        bool BlockProcess::isBlocked() {
            if (mutexInit(&m_pMutex) == -1) {
                return true;
            }
            
            return false;
        }
        
        // Block Thread
        BlockThread::BlockThread(NA_CRITICAL &oCritical) {
            #if defined(nonWindows)
                oCritical = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
            #endif
            
            m_Critical = oCritical;
            
            enterCritical(m_Critical);
        }
        BlockThread::~BlockThread() {
            leaveCritical(m_Critical);
        }
    };
};
