#ifndef NORDICARTS_OS_TIME_H
#define NORDICARTS_OS_TIME_H

#include "../OS.hpp"
#include "../OSLoad.hpp"

// Time Defs
#ifndef NA_TIME
    #if defined(nonWindows)
        #define NA_TIME time_t
        #define NA_TIMEINFO tm
    #elif defined(NordicArtsWindows)
        #define NA_TIME SYSTEMTIME
        #define NA_TIMEINFO NULL
    #else
        #define NA_TIME time_t
        #define NA_TIMEINFO tm
    #endif
#endif

namespace NordicArts {
    class TimeNA {
        // Variables
        public:
        protected:
        private:
            NA_TIME m_oTime;
            NA_TIMEINFO *m_sTimeInfo;

        // Methods
        public:
            TimeNA(NA_TIME &oTime);
            
            int getDay();
            int getMonth();
            int getYear();
            int getHour();
            int getMinute();
            int getSecond();
            int getMilliSecond();

        protected:
        private:


    };
};

#endif
