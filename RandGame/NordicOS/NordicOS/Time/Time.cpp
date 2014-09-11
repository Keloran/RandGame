#include "./Time.hpp"

namespace NordicArts {
    namespace NordicOS {
        // Time
        Time::Time() {
            m_tpSystemTime      = std::chrono::system_clock::now();
            m_tpHighClock       = std::chrono::high_resolution_clock::now();
        }

        Time::Time(NA_TIME &oTime) {
            m_oTime = oTime;

            #if defined(nonWindows)
                time(&m_oTime);
                m_sTimeInfo = localtime(&m_oTime);
            #else
                GetLocalTime(m_oTime);
            #endif
        }

        int Time::getDay() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_mday;
            #else
                return m_oTime.wDay;
            #endif

            return -1;
        }

        int Time::getMonth() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_mon;
            #else
                return m_oTime.wMonth;
            #endif

            return -1;
        }


        int Time::getYear() const {
            #if defined(nonWindows)
                return (1900 + m_sTimeInfo->tm_year);
            #else
                return m_oTime.wYear;
            #endif

            return -1;
        }

        int Time::getHour() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_hour;
            #else
                return m_oTime.wHour;
            #endif

            return -1;
        }

        int Time::getMinute() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_min;
            #else
                return m_oTime.wMinute;
            #endif

            return -1;
        }

        int Time::getSecond() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_sec;
            #else
                return m_oTime.wSecond;
            #endif

            return -1;
        }
        
        int Time::getSeconds() const {
            std::chrono::seconds timeDuration = std::chrono::duration_cast<std::chrono::seconds>(m_tpHighClock.time_since_epoch());
            return (int)timeDuration.count();
        }

        int Time::getMilliSeconds() const {
            std::chrono::milliseconds timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(m_tpHighClock.time_since_epoch());
            return (int)timeDuration.count();
        }

        int Time::getNanoSeconds() const {
            std::chrono::nanoseconds timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_tpHighClock.time_since_epoch());
            return (int)timeDuration.count();
        }
        
        int Time::getMicroSeconds() const {
            std::chrono::microseconds timeDuration = std::chrono::duration_cast<std::chrono::microseconds>(m_tpHighClock.time_since_epoch());
            
            return (int)timeDuration.count();
        }
        
        // Clock
        Clock::Clock() {
            Time oTime;
            
            m_iStartTime = oTime.getSeconds();
        }
        
        int Clock::getElapsedTime() const {
            Time oTime;
            
            return (oTime.getSeconds() - m_iStartTime);
        }
        
        int Clock::restart() {
            Time oTime;
            int iElapsed    = (oTime.getSeconds() - m_iStartTime);
            m_iStartTime    = oTime.getSeconds();
            
            return iElapsed;
        }
    };
};
