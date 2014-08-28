#ifndef NordicArts_NordicOS_FileHandler_TextFileReader_H
#define NordicArts_NordicOS_FileHandler_TextFileReader_H

#include "../../OS.hpp"
#include "../FileHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        class TextFileReader : public FileHandler {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            explicit TextFileReader(const std::string &cFileName);
            explicit TextFileReader(const std::string &cFileName, bool bFilePath);
        
            std::string readAll() const;
    
        protected:
        private:
        };
    };
};

#endif
