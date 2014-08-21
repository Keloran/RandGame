#include "./OS.hpp"

namespace NordicArts {
    namespace NordicOS {
        const char *getBuildNumber() {
            std::ostringstream output;
            output << NORDICOS_BUILDNUMBER;
            return output.str().c_str();
        }
    }
};
