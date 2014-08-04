#ifndef NORDICARTS_OS_STRING_H
#define NORDICARTS_OS_STRING_H

#include "../OSLoad.hpp"

namespace NordicArts {
    std::string getString(char cCharacter);
    std::string randString();
    std::string randString(int iLength);
};

#endif
