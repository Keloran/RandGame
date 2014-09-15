#include "./Sleep.hpp"
#include <windows.h>

namespace NordicArts {
    namespace NordicOS {
        void sleepImp(Time oTime) {
            TIMECAPS tc;
            timeGetDevCaps(&tc, sizeof(TIMECAPS));

            timeBeginPeriod(tc.wPeriodMin);

            ::Sleep(time.asMilliseconds());

            timeEndPeriod(tc.wPeriodMin);
        }
    };
};
