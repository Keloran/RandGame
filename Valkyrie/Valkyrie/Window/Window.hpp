#ifndef NORDICARTS_VALKYRIE_WINDOW_H
#define NORDICARTS_VALKYRIE_WINDOW_H

#include "../Includes.hpp"

namespace NordicArts {
    class Window {
        // Variables
        public:
        protected:
        private:
            int m_iWidth;
            int m_iHeight;
            int m_iFrameLimit;
            
            std::string m_cTitle;

        // Methods
        public:
            Window();
            Window(int iX, int iY);
            Window(int iX, int iY, std::string cTitle);

            void setWidth(int iX);
            void setHeight(int iY);
            void setTitle(std::string cTitle);
            void setFramerateLimit(int iFrameLimit);

            virtual ~Window();

        protected:
        private:

    };
};

#endif
