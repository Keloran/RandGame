#ifndef NordicArts_NordicOS_FileHandler_H
#define NordicArts_NordicOS_FileHandler_H

#include "./FileUtils.hpp"
#include "../OS.hpp"
#include "../ExceptionHandler/ExceptionHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
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
            
                std::string getFilePath() const;

            protected:
                FileHandler(const std::string &cFileName, bool bSaveException);

                void throwError(const std::string &cMessage) const;
                void throwError(const std::ostringstream &cMessage) const;

            private:
        };
    };
};

#endif
