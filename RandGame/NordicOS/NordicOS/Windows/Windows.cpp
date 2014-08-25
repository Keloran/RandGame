#include "./Windows.hpp"

namespace NordicArts {
    namespace NordicOS {
        std::string OSSpecific::ResourcePath(std::string cFileName) {
            std::string cFilePath;

            std::string::size_type iLastIndex = cFileName.find_last_of("/\\");
            if (iLastIndex != std::string::npos) {
                cFilePath = cFileName.substr(0, iLastIndex);
            } else {
                cFilePath = ("./" + cFileName);
            }

            return cFilePath;
        }
    };
};
