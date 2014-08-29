#ifndef NordicArts_NordicOS_Logger_H
#define NordicArts_NordicOS_Logger_H

#include "../OS.hpp"
#include "../Time/Time.hpp"
#include "../Threads/Critical.hpp"
#include "../Singleton/Singleton.hpp"
#include "../String/String.hpp"

namespace NordicArts {
    namespace NordicOS {
        class Logger final : public Singleton {
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
    
            NA_CRITICAL                 m_Critical;

        // Methods
        public:
            explicit Logger(const std::string &cFileName);
            virtual ~Logger();

            static void log(const char *cLog);
            static void log(std::string cString);
            static void log(float fLog);
            static void log(int iUnknown, const char *cLog);
            static void log(LoggerType eType, const std::string &cLog);
            static void log(LoggerType eType, const std::ostringstream &cLog);
            static void log(LoggerType eType, const char *cLog);
            
        protected:
        private:

        };
    };
};

#endif
