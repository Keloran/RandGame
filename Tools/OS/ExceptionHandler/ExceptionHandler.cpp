#include "./ExceptionHandler.hpp"
#include "../Logger/Logger.hpp"

namespace NordicArts {
    ExceptionHandler::ExceptionHandler(const std::string &cMessage, bool bSaveToFile) : m_cMessage(cMessage) {
        if (bSaveToFile) {
            Logger::log(Logger::TYPE_ERROR, m_cMessage);
        }
    }

    ExceptionHandler::ExceptionHandler(const std::ostringstream &cMessage, bool bSaveToFile) : m_cMessage(cMessage.str().c_str()) {
        if (bSaveToFile) {
            Logger::log(Logger::TYPE_ERROR, m_cMessage);
        }
    }

    const std::string &ExceptionHandler::getMessage() const {
        return m_cMessage;
    }
};
