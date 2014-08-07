#include "./Time.hpp"

namespace NordicArts {
    TimeNA::TimeNA(NA_TIME &oTime) {
        m_oTime = oTime;

        #if defined(nonWindows)
            time(&m_oTime);
            m_sTimeInfo = localtime(&m_oTime);
        #else
            GetLocalTime(m_oTime);
        #endif
    }

    int TimeNA::getDay() {
        #if defined(nonWindows)
            return m_sTimeInfo->tm_mday;
        #else
            return m_oTime.wDay;
        #endif

        return -1;
    }

    int TimeNA::getMonth() {
        #if defined(nonWindows)
            return m_sTimeInfo->tm_mon;
        #else
            return m_oTime.wMonth;
        #endif
    
        return -1;
    }


    int TimeNA::getYear() {
        #if defined(nonWindows)
            return (1900 + m_sTimeInfo->tm_year);    
        #else
            return m_oTime.wYear;
        #endif    

        return -1;
    }

    int TimeNA::getHour() {
        #if defined(nonWindows)
            return m_sTimeInfo->tm_hour;
        #else
            return m_oTime.wHour;
        #endif    

        return -1;
    }

    int TimeNA::getMinute() {
        #if defined(nonWindows)
            return m_sTimeInfo->tm_min;
        #else
            return m_oTime.wMinute;    
        #endif
        
        return -1;
    }

    int TimeNA::getSecond() {
        #if defined(nonWindows)
            return m_sTimeInfo->tm_sec;
        #else
            return m_oTime.wSecond;
        #endif
    
        return -1;
    }

    int TimeNA::getMilliSecond() {
        #if defined(nonWindows)
            return 0;
        #else
            return m_oTime.wMilliseconds;
        #endif
    
        return -1;
    }
};
