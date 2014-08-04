#include "./BlockProcess.hpp"

namespace NordicArts {
    BlockProcess::BlockProcess(const std::string &cName) {
        mutexInit(&m_pMutex);
    }

    BlockProcess::~BlockProcess() {
        mutexUnlock(&m_pMutex);
    }

    bool BlockProcess::isBlocked() {
        if (mutexInit(&m_pMutex) == -1) {
            return true;
        }

        return false;
    }
};
