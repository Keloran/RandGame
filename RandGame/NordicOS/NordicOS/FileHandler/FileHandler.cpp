#include "./FileHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        FileHandler::FileHandler(const std::string &cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
            OSSpecific oOS;
            std::string cLogFind(".log");
            std::size_t szFound = cFileName.find(cLogFind);
            
            if (fileExists(cFileName.c_str()) || szFound) {
                m_cFilePath = oOS.ResourcePath(cFileName);

                if (cFileName.empty()) {
                    throw ExceptionHandler(__FUNCTION__ + std::string(" missing filename"), bSaveException);
                }
            } else {
                throw ExceptionHandler(__FUNCTION__ + std::string(" Missing File ") + cFileName, bSaveException);
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
        
        std::string FileHandler::getFilePath() const {
            return m_cFilePath;
        }
    };
};
