#ifndef NORDICARTS_OS_TIME_H
#define NORDICARTS_OS_TIME_H

#include "../OS.hpp"
#include "../OSLoad.hpp"

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
                Time(NA_TIME &oTime);

                int getDay();
                int getMonth();
                int getYear();
                int getHour();
                int getMinute();
                int getSecond();
                int getMilliSecond();
                int getNanoSeconds();

            protected:
            private:
        };
    };
};

#endif
