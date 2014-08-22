#include "./FileHandler.hpp"
#include "../ExceptionHandler/ExceptionHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        FileHandler::FileHandler(const std::string &cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
            OSSpecific oOS;
            m_cFilePath = oOS.ResourcePath(cFileName);

            if (cFileName.empty()) {
                throw ExceptionHandler(__FUNCTION__ + std::string(" missing filename"), bSaveException);
            }
        }

        FileHandler::~FileHandler() {
            if (m_cFileStream.is_open()) {
                m_cFileStream.close();
            }
        }

        void FileHandler::throwError(const std::string &cMessage) const {
            throw ExceptionHandler("File [" + m_cFileName + "] " + cMessage, m_bSaveException);      
        }

        void FileHandler::throwError(const std::ostringstream &cMessage) const {
            throwError(cMessage.str().c_str());
        }
    };
};
