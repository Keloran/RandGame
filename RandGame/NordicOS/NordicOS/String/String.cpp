#include "./String.hpp"
#include "../Time/Time.hpp"

namespace NordicArts {
    namespace NordicOS {
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

        std::string getString(int64_t iInt) {
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
            Time::Time oTime;
            Time::Time *pTime = &oTime;
            srand(pTime->getNanoSeconds());

            // generate the string
            for (int i = 0; i < iLength; i++) {
                int iRand = ((rand() % 36) + 1);
                returnString.append(getString(randChars[iRand]));
            }

            return returnString;
        }

        // Case
        std::string toUpper(std::string &cString) {
            std::transform(cString.begin(), cString.end(), cString.begin(), ::toupper);

            return cString;
        }
        std::string toLower(std::string &cString) {
            std::transform(cString.begin(), cString.end(), cString.begin(), ::tolower);

            return cString;
        }

        // Signed
        unsigned convertToUnsigned(const std::string &cString, std::ios_base &(*pFormat)(std::ios_base&)) {
            try {
                return convertToType<unsigned>(cString, pFormat);
            } catch ( ... ) {
                return 0;
            }
        }
    };
};
