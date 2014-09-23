#include "./Sleep.hpp"
#include "../../OS.hpp"

#if defined(NordicOS_Windows)
    #include "../Windows/Sleep/Sleep.hpp"
#else
    #include "../nonWindows/Sleep/Sleep.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        void sleep(Time duration) {
            if (duration >= Time::Zero) {
                sleepImp(duration);
            }
        }
    };
};
