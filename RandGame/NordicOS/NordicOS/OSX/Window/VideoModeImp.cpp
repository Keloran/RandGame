#include "../../Window/Window/VideoMode/VideoModeImp.hpp"
#include "../Conversion/CG.hpp"
#include "../../ExceptionHandler/Errors.hpp"
#include <algorithm>

namespace NordicArts {
    namespace NordicOS {
        std::vector<VideoMode> VideoModeImp::getFullScreenModes() {
            std::vector<VideoMode> modes;

            CFArrayRef cgmodes = CGDisplayCopyAllDisplayModes(CGMainDisplayID(), NULL);
            if (cgmodes == NULL) {
                Errors() << "Cant get videomodes" << std::endl;

                return modes;
            }

            const CFIndex modesCount = CFArrayGetCount(cgmodes);
            for (CFIndex i = 0; i < modesCount; i++) {
                CGDisplayModeRef cgmode = (CGDisplayModeRef)CFArrayGetValueAtIndex(cgmodes, i);

                VideoMode mode = convertCGModeToNAMode(cgmode);

                if (std::find(modes.begin(), modes.end(), mode) == modes.end()) {
                    modes.push_back(mode);
                }
            }

            CFRelease(cgmodes);

            return modes;
        }

        VideoMode VideoModeImp::getDesktopMode() {
            CGDirectDisplayID display = CGMainDisplayID();
        
            return VideoMode(CGDisplayPixelsWide(display), CGDisplayPixelsHigh(display), displayBitsPerPixel(display));
        }
    };
};
