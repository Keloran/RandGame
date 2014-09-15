#include "./Mutex.hpp"

namespace NordicArts {
    namespace NordicOS {
        MutexImp::MutexImp() {
            InitializeCriticalSection(&m_hMutex);
        }

        MutexImp::~MutexImp() {
            DeleteCriticalSection(&m_hMutex);
        }

        void MutexImp::lock() {
            EnterCriticalSection(&m_hMutex);
        }

        void MutexImp::unlock() {
            LeaveCriticalSection(&m_hMutex);
        }
    };
};
