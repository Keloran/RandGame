#include "./Strng.h"

namespace NordicArts {
    Strng::Strng() {
    }

    Strng::~Strng() {
    }

    std::string Strng::getString(char cCharacter) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << cCharacter;
        stringStream >> returnString;

        return returnString;
    }
};
