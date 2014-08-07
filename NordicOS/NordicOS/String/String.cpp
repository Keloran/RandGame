#include "./String.hpp"

namespace NordicArts {
    // Get String from input
    std::string getString(char cChar) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << cChar;
        stringStream >> returnString;

        return returnString;
    }
    std::string getString(float fFloat) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << fFloat;
        stringStream >> returnString;

        return returnString;
    }
    std::string getString(int iInt) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << iInt;
        stringStream >> returnString;

        return returnString;
    }

    // Generate Random String
    std::string randString() {
        return randString(15);
    }
    std::string randString(int iLength) {
        std::string returnString;

        char randChars[37] = "abcdefghijklmnopqrstuvwxyz1234567890";

        // Seed
        std::chrono::high_resolution_clock::time_point timePoint    = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds timeDuration                       = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        int timeCount                                               = timeDuration.count();
        srand(timeCount);

        // generate the string
        for (int i = 0; i < iLength; i++) {
            int iRand = (rand() % 36);
            returnString.append(getString(randChars[iRand]));
        }

        return returnString;
    }
};
