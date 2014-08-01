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

    	srand(time(NULL));
    	for (int i = 0; i < iLength; i++) {
    		int iRand = (rand() % 36);
    		returnString.append(getString(randChars[iRand]));
    	}

    	return returnString;
    }
};
