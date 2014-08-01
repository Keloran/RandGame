#include "./Strng.h"

namespace NordicArts {
    std::string getString(char cCharacter) {
        std::stringstream stringStream;
        std::string returnString;

        stringStream << cCharacter;
        stringStream >> returnString;

        return returnString;
    }

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
