//
//  UTF.hpp
//  NordicOS
//
//  Created by Max Hooton on 15/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_UTF_H
#define NordicArts_NordicOS_UTF_H

#include "../OS.hpp"
#include <algorithm>
#include <string>
#include <cstdlib>

namespace NordicArts {
    namespace NordicOS {
        template<unsigned int N>
        class UTF;
        
        template<>
        class UTF<8> {
        // Variables
        public:
        protected:
        private:
            
        // Method
        public:
            template<typename In>
            static In decode(In begin, In end, UINT32 &output, UINT32 replacement = 0);
            
            template<typename Out>
            static Out encode(UINT32 input, Out output, UINT8 replacement = 0);
            
            template<typename In>
            static In next(In begin, In end);
            
            template<typename In>
            static std::size_t count(In begin, In end);
            
            template<typename In, typename Out>
            static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out fromWide(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out fromLatin1(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);
            
            template<typename In, typename Out>
            static Out toLatin1(In begin, In end, Out output, char replacement = 0);
            
            template<typename In, typename Out>
            static Out toUTF8(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF16(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF32(In begin, In end, Out output);
            
        protected:
        private:
            
        };
        
        template<>
        class UTF<16> {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            template<typename In>
            static In decode(In begin, In end, UINT32 &output, UINT32 replacement = 0);
            
            template<typename Out>
            static Out encode(UINT32 input, Out output, UINT16 replacement = 0);
            
            template<typename In>
            static In next(In begin, In end);
            
            template<typename In>
            static std::size_t count(In begin, In end);
            
            template<typename In, typename Out>
            static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out fromWide(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out fromLatin1(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);
            
            template<typename In, typename Out>
            static Out toLatin1(In begin, In end, Out output, char replacement = 0);
            
            template<typename In, typename Out>
            static Out toUTF8(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF16(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF32(In begin, In end, Out output);
            
        protected:
        private:
            
        };
        
        template<>
        class UTF<32> {
        // Variables
        public:
        protected:
        private:
            
        // Methods
        public:
            template<typename In>
            static In decode(In begin, In end, UINT32 &output, UINT32 replacement = 0);
            
            template<typename Out>
            static Out encode(UINT32 input, Out output, UINT32 replacement = 0);
            
            template<typename In>
            static In next(In begin, In end);
            
            template<typename In>
            static std::size_t count(In begin, In end);
            
            template<typename In, typename Out>
            static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out fromWide(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out fromLatin1(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());
            
            template<typename In, typename Out>
            static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);
            
            template<typename In, typename Out>
            static Out toLatin1(In begin, In end, Out output, char replacement = 0);
            
            template<typename In, typename Out>
            static Out toUTF8(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF16(In begin, In end, Out output);
            
            template<typename In, typename Out>
            static Out toUTF32(In begin, In end, Out output);
            
            template<typename In>
            static UINT32 decodeAnsi(In input, const std::locale &locale = std::locale());
            
            template<typename In>
            static UINT32 decodeWide(In input);
            
            template<typename Out>
            static Out encodeAnsi(UINT32 codePoint, Out output, char replacement = 0, const std::locale &locale = std::locale());
            
            template<typename Out>
            static Out encodeWide(UINT32 codePoint, Out output, wchar_t replacement = 0);
            
        protected:
        private:
            
        };
        
        #include "./UTF.inl"
        
        typedef UTF<8>  UTF8;
        typedef UTF<16> UTF16;
        typedef UTF<32> UTF32;
    };
};

#endif
