#include "./Logger.hpp"
#include "../ExceptionHandler/ExceptionHandler.hpp"
#include "../FileHandler/TextFileWriter/TextFileWriter.hpp"
#include "../Critical/Critical.hpp"
#include "../BlockThread/BlockThread.hpp"

namespace NordicArts {
    static Logger *s_pLogger = nullptr;

    Logger::Logger(const std::string &cFile) : Singleton(TYPE_LOGGER), m_cLogFile(cFile), m_ulFileLength(0), m_cUnknownLogType("UNKNOWN") {
        m_aLogTypes[0] = "Info";
        m_aLogTypes[1] = "Warning";
        m_aLogTypes[2] = "Error";

        // File Length
        m_ulFileLength = m_cUnknownLogType.size();
        for (const std::string &cType : m_aLogTypes) {
            if (m_ulFileLength < cType.size()) {
                m_ulFileLength = cType.size();
            }
        }

        createCritical(m_Critical);
        BlockThread blockThread(m_Critical);

        TextFileWriter file(m_cLogFile, false, false);

        s_pLogger = this;
    }

    Logger::~Logger() {
        s_pLogger = nullptr;   

        deleteCritical(m_Critical);
    }

    // Logger polymorph
    void Logger::log(const char *cLog) {
        log(Logger::TYPE_INFO, cLog);
    }
    void Logger::log(float fLog) {
        log(getString(fLog).c_str());
    }
    void Logger::log(int iUnknown, const char *cLog) {
        log(static_cast<LoggerType>(iUnknown), cLog);
    }
    void Logger::log(LoggerType eLogType, const std::string &cLog) {
        log(eLogType, cLog.c_str());
    }
    void Logger::log(LoggerType eLogType, const std::ostringstream &cLog) {
        log(eLogType, cLog.str().c_str());
    }

    // Real Logger
    void Logger::log(LoggerType eLogType, const char *cLog) {
        if (s_pLogger == nullptr) {
            std::cout << "Logger not Started: " << cLog << std::endl;
            
            return;
        }

        BlockThread oBlockThread(s_pLogger->m_Critical);

        std::ostringstream cStream;
        cStream << std::setfill(' ') << std::setw((int)s_pLogger->m_ulFileLength);

        try {
            cStream << s_pLogger->m_aLogTypes.at(eLogType);
        } catch( ... ) {
            cStream << s_pLogger->m_cUnknownLogType;
        }

        NA_TIME sTime;
        TimeNA oTime(sTime);
    
        // Output the time
        cStream << " [ " << oTime.getYear() << ".";
        cStream << std::setfill('0') << std::setw(2) << oTime.getMonth() << ".";
        cStream << std::setfill('0') << std::setw(2) << oTime.getDay() << ".";
        cStream << std::setfill(' ') << std::setw(2) << oTime.getHour() << ":";
        cStream << std::setfill('0') << std::setw(2) << oTime.getMinute() << ":";
        cStream << std::setfill('0') << std::setw(2) << oTime.getSecond() << ".";
        cStream << std::setfill('0') << std::setw(3) << oTime.getMilliSecond() << "] ";

        // Message
        cStream << cLog << std::endl;

        // Write to file
        try {
            TextFileWriter file(s_pLogger->m_cLogFile, true, false);
            file.write(cStream.str());
        } catch( ... ) {
            std::cout << __FUNCTION__ << " using Logger write failed: " << cStream.str() << std::endl;
        }
    }
};
