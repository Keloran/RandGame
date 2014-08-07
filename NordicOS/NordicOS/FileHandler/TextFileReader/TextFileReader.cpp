#include "./TextFileReader.hpp"

namespace NordicArts {
    TextFileReader::TextFileReader(const std::string &cFileName) : FileHandler(cFileName, true) {
        m_cFileStream.open(m_cFilePath.c_str(), std::ios_base::in);
        if (!m_cFileStream.is_open()) {
            throwError(__FUNCTION__ + std::string(" cannot open file for reading!"));
        }
    }

    std::string TextFileReader::readAll() const {
        std::ostringstream cStream;
        cStream << m_cFileStream.rdbuf();
        if (cStream.str().length() < 1) {
            throwError(__FUNCTION__ + std::string(" failed because file is empty"));
        }
        
        return cStream.str();
    }
};
