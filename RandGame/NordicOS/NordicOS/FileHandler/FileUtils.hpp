#ifndef NordicArts_NordicOS_FileUtils_H
#define NordicArts_NordicOS_FileUtils_H

#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {
        bool fileExists(std::string cFileName);
        bool fileExists(char const *cFileName);
        bool fileExists(const char *cFileName);
    };
};

#endif
