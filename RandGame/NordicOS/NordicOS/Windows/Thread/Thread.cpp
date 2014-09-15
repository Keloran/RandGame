#include "./Thread.hpp"
#include "../../Threading/Thread/Thread.hpp"
#include "../../ExceptionHandler/Error.hpp"
#include <cassert>
#include <process.h>

namespace NordicArts {
    namespace NordicOS {
        ThreadImp::ThreadImp(Thread *pOwner) {
            m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &ThreadImp::entryPoint, pOwner, 0, &m_iThreadID));
            if (!m_hThread) {
                err() << "Failed to craete Thread" << std::endl;
            }
        }

        ThreadImp::~ThreadImp() {
            if (m_hThread) {
                CloseHandle(m_hThread);
            }
        }

        void ThreadImp::wait() {
            if (m_hThread) {
                assert(m_iThreadID != GetCurrentThreadId());
                WaitForSingleObject(m_hThread, INFINITE);
            }
        }

        void ThreadImp::terminate() {
            if (m_hThread) {
                TerminateThread(m_hThread, 0);
            }
        }

        unsigned int __stdcall ThreadImp::entryPoint(void *pUserData) {
            Thread *pOwner = static_cast<Thread*>(pUserData);
            pOwner->run();

            _endthreadex(0);
    
            return 0;
        }
    };
};
