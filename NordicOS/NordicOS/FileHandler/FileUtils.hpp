#ifndef NORDICARTS_OS_FILEUTILS_H
#define NORDICARTS_OS_FILEUTILS_H

#include "../OS.hpp"

namespace NordicArts {
    static bool fileExists(const char *cFileName) {
        bool bExists = false;

        std::ifstream pFile(cFileName);
        if (pFile) {
            bExists = true;
            pFile.close();
        }

        return bExists;
    }
};

#endif
