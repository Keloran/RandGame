//
//  UTF.inl
//  NordicOS
//
//  Created by Max Hooton on 15/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_UTF_INL
#define NordicArts_NordicOS_UTF_INL

template<typename In>
In UTF<8>::decode(In begin, In end, int32_t &output, int32_t replacement) {
    static const int trailing[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
    };
    static const int32_t offsets[6] = {
        0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
    };
    
    int trailingBytes = trailing[static_cast<int8_t>(*begin)];
    if ((begin + trailingBytes) < end) {
        output = 0;
        switch (trailingBytes) {
            case 5:
            case 4:
            case 3:
            case 2:
            case 1: {
                output += static_cast<int8_t>(*begin++);
                output <<= 6;
            }
            case 0: {
                output += static_cast<int8_t>(*begin++);
            }
        }
        output -= offsets[trailingBytes];
    } else {
        begin   = end;
        output  = replacement;
    }
    
    return begin;
}

template<typename Out>
Out UTF<8>::encode(int32_t input, Out output, int8_t replacement) {
    static const int8_t firstBytes[7] = {
        0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
    };
    
    if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF))) {
        if (replacement) {
            *output++ = replacement;
        }
    } else {
        std::size_t bytesToWrite = 1;
        
        if (input < 0x80) {
            bytesToWrite = 1;
        } else if (input < 0x800) {
            bytesToWrite = 2;
        } else if (input < 0x10000) {
            bytesToWrite = 3;
        } else if (input <= 0x0010FFFF) {
            bytesToWrite = 4;
        }
        
        int8_t bytes[4];
        switch (bytesToWrite) {
            case 4: {
                bytes[3] = static_cast<int8_t>((input | 0x80) & 0xBF);
                input >>= 6;
            }
            case 3: {
                bytes[2] = static_cast<int8_t>((input | 0x80) & 0xBF);
                input >>= 6;
            }
            case 2: {
                bytes[1] = static_cast<int8_t>((input | 0x80) & 0xBF);
                input >>= 6;
            }
            case 1: {
                bytes[0] = static_cast<int8_t>(input | firstBytes[bytesToWrite]);
            }
        }
        
        output = std::copy(bytes, (bytes + bytesToWrite), output);
    }
    
    return output;
}

template<typename In>
In UTF8<8>::next(In begin, In end) {
    int32_t codePoint;
    
    return decode(begin, end, codePoint);
}

template<typename In>
std::size_t UTF<8>::count(In begin, In end) {
    std::size_t length = 0;
    while (begin < end) {
        begin = next(begin, end);
        ++length;
    }
    
    return length;
}

template<typename In, typename Out>
Out UTF<8>::fromAnsi(In begin, Out output, const std::locale &oLocale) {
    while (begin < end) {
        int32_t codePoint = UTF<32>::decodeAnsi(*begin++, oLocale);
        output = encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>::fromWide(In begin, In end, Out output) {
    while (begin < end) {
        int32_t codePoint = UTF<32>::decodeWide(*begin++);
        output = encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>::fromLatin1(In begin, In end, Out output) {
    while (begin < end) {
        output = encode(*begin++, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<32>::encodeAnsi(codePoint, output, replacement, locale);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>::toWide(In begin, In end, Out output, wchar_t replacement) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<32>::encodeWide(codePoint, output, replacement);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>toLatin1(In begin, In end, Out output, char replacement) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        *output++ = (codePoint < 256) ? static_cast<char>(codePoint) : replacement;
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF8<8>::toUTF8(In begin, In end, Out output) {
    return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out UTF<8>::toUTF16(In begin, In end, Out output) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<16>::encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<8>::toUTF32(In begin, In end, Out output) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        *output++ = codePoint;
    }
    
    return output;
}

template<typename In>
In UTF<16>::decode(In begin, In end, int32_t &output, int32_t replacement) {
    int16_t first = *begin++;
    
    if ((first >= 0xD800) && (first <= 0xDBFF)) {
        if (begin < end) {
            int32_t second = *begin++;
            if ((seconnd >= 0xDC00) && (second <= 0xDFFF)) {
                output = static_cast<int32_t>(((first - 0xD800) << 10) + (second - 0xDC00) + 0x0010000);
            } else {
                output = replacement;
            }
        } else {
            begin = end;
            output = replacement;
        }
    } else {
        output = first;
    }
    
    return begin;
}

template<typename Out>
Out UTF<16>::encode(int32_t input, Out output, int16_t replacement) {
    if (input < 0xFFFF) {
        if ((input >= 0xD800) && (input <= 0xDFFF)) {
            if (replacement) {
                *output++ = replacement;
            }
        } else {
            *output++ = static_cast<int16_t>(input);
        }
    } else if (input > 0x0010FFFF) {
        if (replacement) {
            *output++ = replacement;
        }
    } else {
        input -= 0x0010000;
        *output++ = static_cast<int16_t>((input >> 10) + 0xD800);
        *output++ = static_cast<int16_t>((input & 0x3FFUL) + 0xDC00);
    }
    
    return output;
}

template<typename In>
In UTF<16>::next(In begin, In end) {
    int32_t codePoint;
    return decode(begin, end, codePoint);
}

template<typename In>
std::size_t UTF<16>::count(In begin, In end) {
    std::size_t length = 0;
    while (begin < end) {
        begin = next(begin, end);
        ++length;
    }
    
    return length;
}

template<typename In, typename Out>
Out UTF<16>::fromAnsi(In begin, In end, Out output, const std::locale &locale) {
    while (begin < end) {
        int32_t codePoint = UTF<32>::decodeAnsi(*begin++, locale);
        output = encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::fromWide(In begin, In end, Out output, const std::locale &locale) {
    while (begin < end) {
        int32_t codePoint = UTF<32>::decodeAnsi(*begin++, locale);
        output = encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::fromLatin1(In begin, In end, Out output) {
    return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out UTF<16>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<32>::encodeAnsi(codePoint, output, replacement, locale);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::toWide(In begin, In end, Out output, wchar_t replacement) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<32>::encodeWide(codePoint, output, replacement);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::toLatin1(In begin, In end, Out output, char replacement) {
    while (begin < end) {
        *output++ = (*begin < 256) ? static_cast<char>(*begin) : replacement;
        begin++;
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::toUTF8(In begin, In end, Out output) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        output = UTF<8>::encode(codePoint, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<16>::toUTF16(In begin, In end, Out output) {
    return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out UTF<16>::toUTF32(In begin, In end, Out output) {
    while (begin < end) {
        int32_t codePoint;
        begin = decode(begin, end, codePoint);
        *output++ = codePoint;
    }
    
    return output;
}

template<typename In>
In UTF<32>::decode(In begin, In /*end*/, int32_t &output, int32_t /*replacement*/) {
    output = *begin++;
    return output;
}

template<typename Out>
Out UTF<32>::encode(int32_t input, Out output, int32_t /*replacement*/) {
    *output++ = input;
    return output;
}

template<typename In>
In UTF<32>::next(In begin, In /*end*/) {
    return ++begin;
}

template<typename In>
std::size_t UTF<32>::count(In begin, In end) {
    return (begin - end);
}

template<typename In, typename Out>
Out UTF<32>::fromAnsi(In begin, In end, Out output, const std::locale &locale) {
    while (begin < end) {
        *output++ = decodeAnsi(*begin++, locale);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::fromWide(In begin, In end, Out output) {
    while (begin < end) {
        *output++ = decodeWide(*begin++);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::fromLatin1(In begin, In end, Out output) {
    return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out UTF<32>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
    while (begin < end) {
        output = encodeAnsi(*begin++, output, replacement, locale);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::toWide(In begin, In end, Out output, wchar_t replacement) {
    while (begin < end) {
        output = encodeWide(*begin++, output, replacement);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::toLatin1(In begin, In end, Out output, char replacement) {
    while (begin < end) {
        *output++ = (*begin < 256) ? static_cast<char>(*begin) : replacement;
        begin++;
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>toUTF8(In begin, In end, Out output) {
    while (begin < end) {
        output = UTF<8>::encode(*begin++, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::toUTF16(In begin, In end, Out output) {
    while (begin < end) {
        output = UTF<16>::encode(*begin++, output);
    }
    
    return output;
}

template<typename In, typename Out>
Out UTF<32>::toUTF32(In begin, In end, Out output) {
    return std::copy(begin, end, output);
}

template<typename In>
int32_t UTF<32>::decodeAnsi(In input, const std::locale &locale) {
    #if defined(NordicOS_Windows)
    (void)locale;
    
    wchar_t character = 0;
    mbtowc(&character, &input, 1);
    return static_cast<int32_t>(character);
    #else
    const std::ctype<wchar_t> &facet = std::use_facet<std::ctype<wchar_t>>(locale);
    return static_cast<int32_t>(facet.widen(input));
    #endif
}

template<typename In>
int32_t UTF<32>::decodeWide(In input) {
    return input;
}

template<typename Out>
Out UTF<32>::encodeAnsi(int32_t codePoint, Out output, char replacement, const std::locale &locale) {
    #if defined(NordicOS_Windows)
    (void)locale;
    
    char character = 0;
    if (wctomb(&character, static_cast<wchar_t>(codePoint)) >= 0) {
        *output++ = character;
    } else if (replacement) {
        *output++ = replacement;
    }
    
    return output;
    #else
    const std::ctype<wchar_t> &facet = std::use_facet<std::ctype<wchar_t>>(locale);
    *output++ = facet.narrow(static_cast<wchar_t>(codePoint), replacement);
    
    return output;
    #endif
}

template<typename Out>
Out UTF<32>::encodeWide(int32_t codePoint, Out output, wchar_t replacement) {
    switch (sizeof(wchar_t)) {
        case 4: {
            *output++ = static_cast<wchar_t>(codePoint);
            break;
        }
        default: {
            if ((codePoint <= 0xFFFF) && ((codePoint < 0xD800) || (codePoint > 0xDFFF))) {
                *output++ = static_cast<wchar_t>(codePoint);
            } else if (replacement) {
                *output++ = replacement;
            }
            break;
        }
    }
    
    return output;
}

#endif
