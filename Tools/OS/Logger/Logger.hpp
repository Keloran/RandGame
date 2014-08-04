#ifndef NORDICARTS_OS_LOGGER_H
#define NORDICARTS_OS_LOGGER_H

#include "../OSLoad.hpp"
#include "../Time/Time.hpp"

namespace NordicArts {
    class Logger final {
        // Variables   
        public:
            enum LoggerType {
                TYPE_INFO = 0,
                TYPE_WARNING,
                TYPE_ERROR,
            };

        protected:
        private:
            std::string                 m_cLogFile;
            const std::string           m_cUnknownLogType;

            unsigned long               m_ulFileLength;

            std::array<std::string, 3>  m_aLogTypes;

        // Methods
        public:
            explicit Logger(const std::string &cFileName);
            virtual ~Logger();

            static void log(const char *cLog);
            static void log(int iUnknown, const char *cLog);
            static void log(LoggerType eType, const std::string &cLog);
            static void log(LoggerType eType, const std::ostringstream &cLog);
            static void log(LoggerType eType, const char *cLog);

        protected:
        private:


    };
};

#endif
