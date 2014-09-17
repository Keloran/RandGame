#ifndef NordicArts_NordicOS_Window_ContextSettings_H
#define NordicArts_NordicOS_Window_ContextSettings_H

namespace NordicArts {
    namespace NordicOS {
        struct ContextSettings {
            explicit ContextSettings(unsigned int iDepth = 0, unsigned int iStencil = 0, unsigned int iAntiAliasing = 0, unsigned int iMajor = 0, unsigned int iMinor = 0) : iDepthBits(iDepth), iStencilBits(iStencil), iAntiAliasingLevel(iAntiAliasing), iMajorVersion(iMajor), iMinorVersion(iMinor) {}

            unsigned int iDepthBits;
            unsigned int iStencilBits;
            unsigned int iAntiAliasingLevel;
            unsigned int iMajorVersion;
            unsigned int iMinorVersion;
        };
    };
};

#endif
