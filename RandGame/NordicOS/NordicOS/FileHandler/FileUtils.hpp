#ifndef NordicArts_NordicOS_FileUtils_H
#define NordicArts_NordicOS_FileUtils_H

#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {
        bool fileExists(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > cFileName);
        bool fileExists(std::string cFileName);
        bool fileExists(const char *cFileName);
    };
};

#endif
