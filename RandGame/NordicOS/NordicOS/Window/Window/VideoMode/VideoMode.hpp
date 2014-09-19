#ifndef NordicArts_NordicOS_Window_VideoMode_H
#define NordicArts_NordicOS_Window_VideoMode_H

#include <vector>

namespace NordicArts {
    namespace NordicOS {
        class VideoMode {
        // Variable
        public:
            unsigned int m_iWidth;
            unsigned int m_iHeight;
            unsigned int m_iBitsPerPixel;

        protected:
        private:

        // Methods
        public:
            VideoMode();
            VideoMode(unsigned int iWidth, unsigned int iHeight, unsigned int iBitsPerPixel = 32);

            static VideoMode getDesktopMode();

            static const std::vector<VideoMode> &getFullScreenModes();

            bool isValid() const;

            unsigned int getWidth() const;
            unsigned int getHeight() const;

        protected:
        private:

        };

        bool operator ==(const VideoMode &oLeft, const VideoMode &oRight);
        bool operator !=(const VideoMode &oLeft, const VideoMode &oRight);
        bool operator <(const VideoMode &oLeft, const VideoMode &oRight);
        bool operator >(const VideoMode &oLeft, const VideoMode &oRight);
        bool operator <=(const VideoMode &oLeft, const VideoMode &oRight);
        bool operator >=(const VideoMode &oLeft, const VideoMode &oRight);
    };
};

#endif
