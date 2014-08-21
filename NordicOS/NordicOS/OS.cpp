#include "./OS.hpp"

namespace NordicArts {
    const char *getBuildNumber() {
        std::ostringstream output;
        output << NORDICOS_BUILDNUMBER;
        return output.str().c_str();
    }
};
