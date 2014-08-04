#ifndef NORDICARTS_OS_FILEHANDLER_H
#define NORDICARTS_OS_FILEHANDLER_H

#include "./FileUtils.hpp"
#include "../OSLoad.hpp"
#include "../OS.hpp"

namespace NordicArts {
    class FileHandler {
        // Variables
        public:
        protected:
            std::fstream    m_cFileStream;
            std::string     m_cFilePath;
            std::string     m_cFileName;

        private:
            bool            m_bSaveException;

        // Methods
        public:
            virtual ~FileHandler();

        protected:
            FileHandler(const std::string &cFileName, bool bSaveException);

            void throwError(const std::string &cMessage) const;
            void throwError(const std::ostringstream &cMessage) const;

        private:

    };
};

#endif
