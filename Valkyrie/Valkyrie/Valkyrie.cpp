#include "./Valkyrie.hpp"

namespace NordicArts {
    const char *getBuildNumber() {
        std::ostringstream output;
        output << VALKYRIE_BUILDNUMBER;
        return output.str().c_str();
    }    

    void randomShit() {
        getString(2.2f);
    }
};
