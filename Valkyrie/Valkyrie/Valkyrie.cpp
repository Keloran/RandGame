#include "./Valkyrie.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        const char *getBuildNumber() {
            std::ostringstream output;
            output << VALKYRIE_BUILDNUMBER;
            return output.str().c_str();
        }    
    };
};
