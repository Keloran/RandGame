#ifndef NordicArts_NordicOS_Time_H
#define NordicArts_NordicOS_Time_H

#include "../OS.hpp"

// Time Defs
#ifndef NA_TIME
    #if defined(nonWindows)
        #define NA_TIME time_t
        #define NA_TIMEINFO tm
    #else
        #define NA_TIME SYSTEMTIME
        #define NA_TIMEINFO NULL
    #endif
#endif

namespace NordicArts {
    namespace NordicOS {
        // Time
        class Time {
        // Variables
        public:
        protected:
        private:
            NA_TIME m_oTime;
            NA_TIMEINFO *m_sTimeInfo;

            std::chrono::system_clock::time_point           m_tpSystemTime;
            std::chrono::high_resolution_clock::time_point  m_tpHighClock;

        // Methods
        public:
            Time();
            Time(INT64 iMicroSeconds);
            Time(NA_TIME &oTime);

            int getDay() const;
            int getMonth() const;
            int getYear() const;
            int getHour() const;
            int getMinute() const;
            int getSecond() const;
            int getSeconds() const;
            int getMilliSeconds() const;
            int getNanoSeconds() const;
            int getMicroSeconds() const;
            
            float asSeconds() const;
            INT32 asMilliseconds() const;
            INT64 asMicroseconds() const;
            
            static const Time Zero;

        protected:
        private:
            INT64 m_iMicroseconds;
            
        };
        
        Time seconds(float fAmount);
        Time milliseconds(INT32 iAmount);
        Time microseconds(INT64 iAmount);
        
        float operator /(Time oLeft, Time oRight);
        
        bool operator ==(Time oLeft, Time oRight);
        bool operator !=(Time oLeft, Time oRight);
        bool operator <(Time oLeft, Time oRight);
        bool operator >(Time oLeft, Time oRight);
        bool operator <=(Time oLeft, Time oRight);
        bool operator >=(Time oLeft, Time oRight);
        
        Time operator -(Time right);
        Time operator -(Time oLeft, Time oRight);
        Time operator +(Time oLeft, Time oRight);
        Time operator *(Time oLeft, INT64 iRight);
        Time operator *(Time oLeft, float fRight);
        Time operator *(float fLeft, Time oRight);
        Time operator *(INT64 iLeft, Time oRight);
        Time operator /(Time oLeft, float fRight);
        Time operator /(Time oLeft, INT64 iRight);
        Time operator %(Time oLeft, Time oRight);
        
        Time &operator +=(Time &oLeft, Time oRight);
        Time &operator -=(Time &oLeft, Time oRight);
        Time &operator *=(Time &oLeft, float fRight);
        Time &operator *=(Time &oLeft, INT64 iRight);
        Time &operator /=(Time &oLeft, float fRight);
        Time &operator %=(Time &oLeft, Time oRight);
        
        // Clock
        class Clock {
        // Variables
        public:
        protected:
        private:
            INT64 m_iStartTime;
            
        // Methods
        public:
            Clock();
            
            INT64 getElapsedTime() const;
            INT64 restart();
            
        protected:
        private:
            
        };
    };
};

#endif
