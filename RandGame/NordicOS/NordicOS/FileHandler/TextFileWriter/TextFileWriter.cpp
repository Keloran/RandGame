#include "./TextFileWriter.hpp"

namespace NordicArts {
    namespace NordicOS {
        TextFileWriter::TextFileWriter(const std::string &cFileName, bool bAppend, bool bSaveException) : FileHandler(cFileName, bSaveException) {
            m_cFileStream.open(m_cFilePath.c_str(), (std::ios_base::out | (bAppend ? std::ios_base::app : std::ios_base::trunc)));
    
            if (!m_cFileStream.is_open()) {
                throwError(__FUNCTION__ + std::string(" cannot open file for writing"));
            }
        }

        void TextFileWriter::write(const std::string &cMessage) {
            m_cFileStream << cMessage;
        }
    };
};
