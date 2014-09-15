#ifndef NordicArts_NordicOS_String_H
#define NordicArts_NordicOS_String_H

#include "../OS.hpp"
#include "../Time/Time.hpp"
#include "./UTF.hpp"

namespace NordicArts {
    namespace NordicOS {
        class String {
        // Variables
        public:
            typedef std::basic_string<int32_t>::iterator        Iterator;
            typedef std::basic_string<int32_t>::const_iterator  ConstIterator;
            
            static const std::size_t                            InvalidPos;
            
        protected:
        private:
            std::basic_string<int32_t>  m_cString;
            
        // Methods
        public:
            String();
            String(char cChar, const std::locale &oLocale = std::locale());
            String(wchar_t cChar);
            String(int32_t iChar);
            String(const char *pChar, const std::locale &oLocale = std::locale());
            String(const wchar_t *pChar);
            String(const std::wstring &oString);
            String(const int32_t *pString);
            String(const std::basic_string<int32_t> &oString);
            String(const String &oCopy);
            
            template<typename T>
            static String fromUTF32(T begin, T end);
            
            operator std::string() const;
            operator std::wstring() const;
            
            std::string toAnsiString(const std::locale &oLocale = std::locale()) const;
            
            std::wstring toWideString() const;
            
            std::basic_string<int8_t> toUTF8() const;
            std::basic_string<int16_t> toUTF16() const;
            std::basic_string<int32_t> toUTF32() const;
            
            String &operator =(const String &oRight);
            String &operator +=(const String &oRight);
            
            int32_t operator [](std::size_t index) const;
            int32_t &operator [](std::size_t index);
            
            void clear();
            void erase(std::size_t position, std::size_t count = 1);
            void insert(std::size_t position, const String &oString);
            void replace(std::size_t position, std::size_t length, const String &oReplace);
            void replace(const String &oSearch, const String &oReplace);
            
            std::size_t getSize() const;
            std::size_t find(const String &oString, std::size_t start = 0) const;
            
            String substring(std::size_t position, std::size_t length = InvalidPos) const;
            
            bool isEmpty();
            
            const int32_t *getData() const;
            
            Iterator begin();
            Iterator end();
            
            ConstIterator begin() const;
            ConstIterator end() const;
            
        protected:
        private:
            friend bool operator ==(const String &oLeft, const String &oRight);
            friend bool operator <(const String &oLeft, const String &oRight);
            
        };
        
        std::string getString(char cChar);
        std::string getString(float fFloat);
        std::string getString(int iInt);
        std::string getString(int64_t iInt);

        std::string randString();
        std::string randString(int iLength);

        std::string toUpper(std::string &cString);
        std::string toLower(std::string &cString);

        unsigned covertToUnsigned(std::string &cString, std::ios_base &(*pFormat)(std::ios_base&));
        
        // Operators
        bool operator ==(const String &oLeft, const String &oRight);
        bool operator !=(const String &oLeft, const String &oRight);
        bool operator <(const String &oLeft, const String &oRight);
        bool operator >(const String &oLeft, const String &oRight);
        bool operator <=(const String &oLeft, const String &oRight);
        bool operator >=(const String &oLeft, const String &oRight);
        
        String operator +(const String &oLeft, const String &oRight);

        // Inline
        #include "./String.inl"
    };
};

#endif
