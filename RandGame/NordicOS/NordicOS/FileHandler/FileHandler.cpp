#include "./FileHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        FileHandler::FileHandler(std::string cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
            doFile();
        }

        void FileHandler::doFile() {
            OSSpecific oOS;
            std::string cFilePath = oOS.ResourcePath(m_cFileName);
            if (fileExists(cFilePath)) {
                if (m_cFileName.empty()) {
                    throw ExceptionHandler(__FUNCTION__ + std::string(" Missing FileName"), m_bSaveException);
                }
                m_cFilePath = cFilePath;
            } else {
                throw ExceptionHandler(__FUNCTION__ + std::string(" Missing File ") + m_cFileName, m_bSaveException);
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
