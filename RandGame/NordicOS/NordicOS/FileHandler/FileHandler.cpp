#include "./FileHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        FileHandler::FileHandler(std::string cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
            OSSpecific oOS;
            std::string cFilePath = oOS.ResourcePath(cFileName);
            std::cout << "Stuff: " << cFilePath.c_str() << std::cout;

            if (fileExists(cFilePath)) {
                if (cFileName.empty()) {
                    throw ExceptionHandler(__FUNCTION__ + std::string(" Missing FileName"), bSaveException);
                }
                m_cFilePath = cFilePath;
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
