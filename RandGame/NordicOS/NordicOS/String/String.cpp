#include "./String.hpp"
#include "../Time/Time.hpp"
#include "./UTF.hpp"

namespace NordicArts {
    namespace NordicOS {
        const std::size_t String::InvalidPos = std::basic_string<UINT32>::npos;
        
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
        
        // Class Stuff
        String::String() {
        }
        String::String(char cString, const std::locale &oLocale) {
            m_cString += UTF32::decodeAnsi(cString, oLocale);
        }
        String::String(wchar_t cString) {
            m_cString += UTF32::decodeWide(cString);
        }
        String::String(UINT32 cString) {
            m_cString += cString;
        }
        String::String(const char *pString, const std::locale &locale) {
            if (pString) {
                std::size_t length = strlen(pString);
                if (length > 0) {
                    m_cString.reserve(length + 1);
                    UTF32::fromAnsi(pString, (pString + 1), std::back_inserter(m_cString), locale);
                }
            }
        }
        String::String(const std::string &oString, const std::locale &oLocale) {
            m_cString.reserve(oString.length() + 1);
            UTF32::fromAnsi(oString.begin(), oString.end(), std::back_inserter(m_cString), oLocale);
        }
        String::String(const wchar_t *pString) {
            if (pString) {
                std::size_t length = std::wcslen(pString);
                if (length > 0) {
                    m_cString.reserve(length + 1);
                    UTF32::fromWide(pString, (pString + length), std::back_inserter(m_cString));
                }
            }
        }
        String::String(const std::wstring &oString) {
            m_cString.reserve(oString.length() + 1);
            UTF32::fromWide(oString.begin(), oString.end(), std::back_inserter(m_cString));
        }
        String::String(const UINT32 *pString) {
            if (pString) {
                m_cString = pString;
            }
        }
        String::String(const std::basic_string<UINT32> &oString) : m_cString(oString) {
        }
        String::String(const String &oCopy) : m_cString(oCopy.m_cString) {
        }
        
        String::operator std::string() const {
            return toAnsiString();
        }
        String::operator std::wstring() const {
            return toWideString();
        }
        
        std::string String::toAnsiString(const std::locale &locale) const {
            std::string cOutput;
            cOutput.reserve(m_cString.length() + 1);
            
            UTF32::toAnsi(m_cString.begin(), m_cString.end(), std::back_inserter(cOutput), 0, locale);
            
            return cOutput;
        }
        
        std::wstring String::toWideString() const {
            std::wstring cOutput;
            cOutput.reserve(m_cString.length() + 1);
            
            UTF32::toWide(m_cString.begin(), m_cString.end(), std::back_inserter(cOutput), 0);
            
            return cOutput;
        }
        
        std::basic_string<UINT8> String::toUTF8() const {
            std::basic_string<UINT8> cOutput;
            cOutput.reserve(m_cString.length());
            
            UTF32::toUTF8(m_cString.begin(), m_cString.end(), std::back_inserter(cOutput));
            
            return cOutput;
        }
        std::basic_string<UINT16> String::toUTF16() const {
            std::basic_string<UINT16> cOutput;
            cOutput.reserve(m_cString.length());
            
            UTF32::toUTF16(m_cString.begin(), m_cString.end(), std::back_inserter(cOutput));
            
            return cOutput;
        }
        std::basic_string<UINT32> String::toUTF32() const {
            return m_cString;
        }
      
        String &String::operator =(const String &oRight) {
            m_cString = oRight.m_cString;
            return *this;
        }
        String &String::operator +=(const String &oRight) {
            m_cString += oRight.m_cString;
            return *this;
        }
        
        UINT32 String::operator [](std::size_t index) const {
            return m_cString[index];
        }
        UINT32 &String::operator [](std::size_t index) {
            return m_cString[index];
        }
        
        void String::clear() {
            m_cString.clear();
        }
        
        std::size_t String::getSize() const {
            return m_cString.size();
        }
        
        bool String::isEmpty() const {
            return m_cString.empty();
        }
        
        void String::erase(std::size_t position, std::size_t count) {
            m_cString.erase(position, count);
        }
        
        void String::insert(std::size_t position, const String &oString) {
            m_cString.insert(position, oString.m_cString);
        }
        
        std::size_t String::find(const String &oString, std::size_t start) const {
            return m_cString.find(oString.m_cString, start);
        }
        
        void String::replace(std::size_t position, std::size_t length, const String &oReplace) {
            m_cString.replace(position, length, oReplace.m_cString);
        }
        void String::replace(const String &oSearch, const String &oReplace) {
            std::size_t step        = oReplace.getSize();
            std::size_t length      = oSearch.getSize();
            std::size_t position    = find(oSearch);
            
            while (position != InvalidPos) {
                replace(position, length, oReplace);
                position = find(oSearch, (position + step));
            }
        }
        
        String String::substring(std::size_t position, std::size_t length) const {
            return m_cString.substr(position, length);
        }
        
        const UINT32 *String::getData() const {
            return m_cString.c_str();
        }
        
        String::Iterator String::begin() {
            return m_cString.begin();
        }
        String::Iterator String::end() {
            return m_cString.end();
        }
        
        String::ConstIterator String::begin() const {
            return m_cString.begin();
        }
        String::ConstIterator String::end() const {
            return m_cString.end();
        }
        
        bool operator ==(const String &oLeft, const String &oRight) {
            return (oLeft.m_cString == oRight.m_cString);
        }
        bool operator !=(const String &oLeft, const String &oRight) {
            return !(oLeft == oRight);
        }
        bool operator <(const String &oLeft, const String &oRight) {
            return (oLeft.m_cString < oRight.m_cString);
        }
        bool operator >(const String &oLeft, const String &oRight) {
            return (oRight < oLeft);
        }
        bool operator <=(const String &oLeft, const String &oRight) {
            return !(oRight < oLeft);
        }
        bool operator >=(const String &oLeft, const String &oRight) {
            return !(oLeft < oRight);
        }
        
        String operator +(const String &oLeft, const String &oRight) {
            String oString = oLeft;
            oString += oRight;
            
            return oString;
        }
    };
};
