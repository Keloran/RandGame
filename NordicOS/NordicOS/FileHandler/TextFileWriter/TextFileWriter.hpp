#ifndef NORDICARTS_OS_FILEHANDLER_TEXTFILEWRITER_H
#define NORDICARTS_OS_FILEHANDLER_TEXTFILEWRITER_H

#include "../OS.hpp"
#include "../FileHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        class TextFileWriter : public FileHandler {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                TextFileWriter(const std::string &cFileName, bool bAppend, bool bSaveException = true);
        
                void write(const std::string &cMessage);
        
            protected:
            private:
        };
    };
};

#endif
