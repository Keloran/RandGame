#ifndef NORDICARTS_OS_STRING_H
#define NORDICARTS_OS_STRING_H

#include "../OSLoad.hpp"
#include "../Time/Time.hpp"

namespace NordicArts {
    std::string getString(char cChar);
    std::string getString(float fFloat);
    std::string getString(int iInt);

    std::string randString();
    std::string randString(int iLength);
};

#endif
