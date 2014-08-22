#ifndef NORDICARTS_OS_STRING_H
#define NORDICARTS_OS_STRING_H

#include "../OS.hpp"
#include "../Time/Time.hpp"

namespace NordicArts {
    namespace NordicOS {
        std::string getString(char cChar);
        std::string getString(float fFloat);
        std::string getString(int iInt);

        std::string randString();
        std::string randString(int iLength);

        std::string toUpper(std::string &cString);
        std::string toLower(std::string &cString);

        unsigned covertToUnsigned(std::string &cString, std::ios_base &(*pFormat)(std::ios_base&));

        // Inline
        #include "./String.inl"
    };
};

#endif
