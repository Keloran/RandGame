#include "./CG.hpp"
#include "../../ExceptionHandler/Errors.hpp"

namespace NordicArts {
    namespace NordicOS {
        size_t modeBitsPerPixel(CGDisplayModeRef mode) {
            size_t bpp = 0;

            CFStringRef pixEnc = CGDisplayModeCopyPixelEncoding(mode);
            if (CFStringCompare(pixEnc, CFSTR(IO32BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
                bpp = 32;
            } else if (CFStringCompare(pixEnc, CFSTR(IO16BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
                bpp = 16;
            } else if (CFStringCompare(pixEnc, CFSTR(IO8BitIndexedPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
                bpp = 8;
            }

            CFRelease(pixEnc);

            return bpp;
        }

        size_t displayBitsPerPixel(CGDirectDisplayID displayId) {
            CGDisplayModeRef mode = CGDisplayCopyDisplayMode(displayId);

            const size_t bpp = modeBitsPerPixel(mode);

            CGDisplayModeRelease(mode);

            return bpp;
        }

        VideoMode convertCGModeToNAMode(CGDisplayModeRef cgmode) {
            return VideoMode(CGDisplayModeGetWidth(cgmode), CGDisplayModeGetHeight(cgmode), modeBitsPerPixel(cgmode));
        }

        CGDisplayModeRef convertNAModeToCGMode(VideoMode namode) {
            CGDisplayModeRef cgbestMode = NULL;

            CFArrayRef cgmodes = CGDisplayCopyAllDisplayModes(CGMainDisplayID(), NULL);
            if (cgmodes == NULL) {
                Errors() << "Can't get videomode" << std::endl;
            
                return NULL;
            }

            const CFIndex modesCount = CFArrayGetCount(cgmodes);
            for (CFIndex i = 0; i < modesCount; i++) {
                CGDisplayModeRef cgmode = (CGDisplayModeRef)CFArrayGetValueAtIndex(cgmodes, i);

                VideoMode mode = convertCGModeToNAMode(cgmode);
                if (mode == namode) {
                    cgbestMode = cgmode;
                }
            }

            CFRelease(cgmodes);

            if (cgbestMode == NULL) {
                Errors() << "Can't convert video mode" << std::endl;
            }

            return cgbestMode;
        }
    };
};
