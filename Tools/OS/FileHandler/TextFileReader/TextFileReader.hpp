#ifndef NORDICARTS_FILEHANDLER_TEXTFILEREADER_H
#define NORDICARTS_FILEHANDLER_TEXTFILEREADER_H

#include "../../OSLoad.hpp"
#include "../../OS.hpp"
#include "../FileHandler.hpp"

namespace NordicArts {
    class TextFileReader : public FileHandler {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            explicit TextFileReader(const std::string &cFileName);
        
            std::string readAll() const;

        protected:
        private:

    };
};

#endif
