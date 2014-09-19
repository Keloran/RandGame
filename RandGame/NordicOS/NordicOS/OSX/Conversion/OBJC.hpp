#ifndef NordicArts_Nordic_OS_Conversion_OBJC_H
#define NordicArts_Nordic_OS_Conversion_OBJC_H

#include "../../String/String.hpp"
#include <string>

#import <Foundation/Foundation.h>

NSString *stringToNSString(const std::string &string);
NSString *stringToNSString(const NordicArts::NordicOS::String &string);

#endif
