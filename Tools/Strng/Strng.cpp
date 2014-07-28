#include "./Strng.h"

namespace NordicArts {
    std::string getString(char cCharacter) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << cCharacter;
        stringStream >> returnString;

        return returnString;
    }
};
