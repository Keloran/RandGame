#ifndef NordicArts_NordicOS_OSX_Conversion_CG_H
#define NordicArts_NordicOS_OSX_Conversion_CG_H

#include "../../Window/Window/VideoMode/VideoMode.hpp"
#include <ApplicationServices/ApplicationServices.h>

namespace NordicArts {
    namespace NordicOS {
        size_t modeBitsPerPixel(CGDisplayModeRef mode);
        size_t displayBitsPerPixel(CGDirectDisplayID displayId);

        VideoMode convertCGModeToNAMode(CGDisplayModeRef cgmode);
    
        CGDisplayModeRef convertNAModeToCGMode(VideoMode namode);
    };
};

#endif
