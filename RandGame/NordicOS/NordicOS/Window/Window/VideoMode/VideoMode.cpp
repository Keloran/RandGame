#include "./VideoMode.hpp"
#include "./VideoModeImp.hpp"
#include <algorithm>
#include <functional>

namespace NordicArts {
    namespace NordicOS {
        VideoMode::VideoMode() : m_iWidth(0), m_iHeight(0), m_iBitsPerPixel(0) {}
        VideoMode::VideoMode(unsigned int iWidth, unsigned int iHeight, unsigned int iBitsPerPixel) : m_iWidth(iWidth), m_iHeight(iHeight), m_iBitsPerPixel(iBitsPerPixel) {}

        VideoMode VideoMode::getDesktopMode() {
            return VideoModeImp::getDesktopMode();
        }

        const std::vector<VideoMode> &VideoMode::getFullScreenModes() {
            static std::vector<VideoMode> vModes;

            if (vModes.empty()) {
                vModes = VideoModeImp::getFullScreenModes();
                std::sort(vModes.begin(), vModes.end(), std::greater<VideoMode>());
            }
        
            return vModes;
        }

        bool VideoMode::isValid() const {
            const std::vector<VideoMode> &vModes = getFullScreenModes();

            return (std::find(vModes.begin(), vModes.end(), *this) != vModes.end());
        }

        unsigned int VideoMode::getWidth() const {
            return m_iWidth;
        }
    
        unsigned int VideoMode::getHeigt() const {
            return m_iHeight;
        }

        bool operator ==(const VideoMode &oLeft, const VideoMode &oRight) {
            return (
                (oLeft.m_iWidth == oRight.m_iWidth) &&
                (oLeft.m_iHeight == oRight.m_iHeight) &&
                (oLeft.m_iBitsPerPixel == oRight.m_iBitsPerPixel)
            );
        }
        bool operator !=(const VideoMode &oLeft, const VideoMode &oRight) {
            return !(oLeft == oRight);
        }

        bool operator <(const VideoMode &oLeft, const VideoMode &oRight) {
            if (oLeft.m_iBitsPerPixel == oRight.m_iBitsPerPixel) {
                if (oLeft.m_iWidth == oRight.m_iHeight) {
                    return (oLeft.m_iHeight < oRight.m_iHeight);
                } else {
                    return (oLeft.m_iWidth > oRight.m_iWidth);
                }
            } else {
                return (oLeft.m_iBitsPerPixel < oRight.m_iBitsPerPixel);
            }
        }
        bool operator >(const VideoMode &oLeft, const VideoMode &oRight) {
            return (oRight < oLeft);
        }
        bool operator <=(const VideoMode &oLeft, const VideoMode &oRight) {
            return !(oRight < oLeft);
        }
        bool operator >=(const VideoMode &oLeft, const VideoMode &oRight) {
            return !(oLeft < oRight);
        }
    };
};
