#include "./Time.hpp"

namespace NordicArts {
    namespace NordicOS {
        const Time Time::Zero;

        // Time
        Time::Time() : m_iMicroseconds(0) {
            m_tpSystemTime      = std::chrono::system_clock::now();
            m_tpHighClock       = std::chrono::high_resolution_clock::now();
        }
        
        Time::Time(INT64 iMicroSeconds) : m_iMicroseconds(iMicroSeconds) {
            m_tpSystemTime  = std::chrono::system_clock::now();
            m_tpHighClock   = std::chrono::high_resolution_clock::now();
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
        
        float Time::asSeconds() const {
            return m_iMicroseconds / 1000000.0f;
        }
        
        INT32 Time::asMilliseconds() const {
            return static_cast<INT32>(m_iMicroseconds / 1000);
        }
        
        INT64 Time::asMicroseconds() const {
            return m_iMicroseconds;
        }
        
        Time seconds(float fAmount) {
            return Time(static_cast<INT64>(fAmount * 1000000));
        }
        Time milliseconds(INT32 iAmount) {
            return Time(static_cast<INT64>(iAmount) * 1000);
        }
        Time microseconds(INT64 iAmount) {
            return Time(iAmount);
        }
        
        float operator /(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() / oRight.asMicroseconds());
        }
        
        bool operator ==(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() == oRight.asMicroseconds());
        }
        bool operator !=(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() != oRight.asMicroseconds());
        }
        bool operator <(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() < oRight.asMicroseconds());
        }
        bool operator >(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() > oRight.asMicroseconds());
        }
        bool operator <=(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() <= oRight.asMicroseconds());
        }
        bool operator >=(Time oLeft, Time oRight) {
            return (oLeft.asMicroseconds() >= oRight.asMicroseconds());
        }
        
        Time operator -(Time oRight) {
            return microseconds(-oRight.asMicroseconds());
        }
        Time operator -(Time oLeft, Time oRight) {
            return microseconds(oLeft.asMicroseconds() - oRight.asMicroseconds());
        }
        Time operator +(Time oLeft, Time oRight) {
            return microseconds(oLeft.asMicroseconds() + oRight.asMicroseconds());
        }
        Time operator *(Time oLeft, float fRight) {
            return microseconds(oLeft.asSeconds() * fRight);
        }
        Time operator *(Time oLeft, INT64 iRight) {
            return microseconds(oLeft.asMicroseconds() * iRight);
        }
        Time operator *(float fLeft, Time oRight) {
            return (oRight * fLeft);
        }
        Time operator *(INT64 iLeft, Time oRight) {
            return (oRight * iLeft);
        }
        Time operator /(Time oLeft, float fRight) {
            return seconds(oLeft.asSeconds() / fRight);
        }
        Time operator /(Time oLeft, INT64 iRight) {
            return microseconds(oLeft.asMicroseconds() / iRight);
        }
        Time operator %(Time oLeft, Time oRight) {
            return microseconds(oLeft.asMicroseconds() % oRight.asMicroseconds());
        }
        
        Time &operator +=(Time &oLeft, Time oRight) {
            return (oLeft = (oLeft + oRight));
        }
        Time &operator -=(Time &oLeft, Time oRight) {
            return (oLeft = (oLeft - oRight));
        }
        Time &operator *=(Time &oLeft, float fRight) {
            return (oLeft = (oLeft * fRight));
        }
        Time &operator *=(Time &oLeft, INT64 iRight) {
            return (oLeft = (oLeft * iRight));
        }
        Time &operator /=(Time &oLeft, float fRight) {
            return (oLeft = (oLeft / fRight));
        }
        Time &operator /=(Time &oLeft, INT64 iRight) {
            return (oLeft = (oLeft / iRight));
        }
        Time &operator %=(Time &oLeft, Time oRight) {
            return (oLeft = (oLeft % oRight));
        }
        
        // Clock
        Clock::Clock() {
            Time oTime;
            
            m_iStartTime = oTime.getMicroSeconds();
        }
        
        INT64 Clock::getElapsedTime() const {
            Time oTime;
            
            return (oTime.getMicroSeconds() - m_iStartTime);
        }
        
        INT64 Clock::restart() {
            Time oTime;
            INT64 iElapsed    = (oTime.getMicroSeconds() - m_iStartTime);
            m_iStartTime        = oTime.getMicroSeconds();
            
            return iElapsed;
        }
    };
};
