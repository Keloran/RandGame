#include "../../String/UTF.hpp"

#import "./OBJC.hpp"
#import <Foundation/Foundation.h>

NSString *stringToNSString(const std::string &cString) {
    std::string cUTF8;
    cUTF8.reserve(cString.size() + 1);

    NordicArts::NordicOS::UTF8::fromAnsi(cString.begin(), cString.end(), std::back_inserter(cUTF8));

    NSString *pString = [NSString stringWithCString:cUTF8.c_str() encoding:NSUTF8StringEncoding];

    return pString;
}

NSString *stringToNSString(const NordicArts::NordicOS::String &cString) {
    NordicArts::NordicOS::UINT32 iLength = (cString.getSize() * sizeof(NordicArts::NordicOS::UINT32));
    
    const void *pData = reinterpret_cast<const void*>(cString.getData());

    NSStringEncoding encoding;
    if (NSHostByteOrder() == NS_LittleEndian) {
        encoding = NSUTF32LittleEndianStringEncoding;
    } else {
        encoding = NSUTF32BigEndianStringEncoding;
    }

    NSString *pString = [[NSString alloc] initWithBytes:pData length:iLength encoding:encoding];
    
    return [pString autorelease];
}
