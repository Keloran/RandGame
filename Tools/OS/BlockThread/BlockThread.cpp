#include "./BlockThread.hpp"

namespace NordicArts {
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
