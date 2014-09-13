#ifndef NordicArts_Valkyrie_Window_H
#define NordicArts_Valkyrie_Window_H

#include "../Includes.hpp"
#include "../Color/Color.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        class Window {
        // Variables
        public:
        protected:
        private:
            int m_iWidth;
            int m_iHeight;
            int m_iFrameLimit;
            int m_iOpenGLMajor;
            int m_iOpenGLMinor;
                
            std::string m_cTitle;
            
            sf::RenderWindow *m_pWindow;
    
        // Methods
        public:
            Window();
            Window(int iX, int iY);
            Window(int iX, int iY, std::string cTitle);

            void setWidth(int iX);
            void setHeight(int iY);
            void setDimensions(int iX, int iY);
            void setTitle(std::string cTitle);
            void setFramerateLimit(int iFrameLimit);
            void setOpenGL(int iMajor, int iMinor);
            void createWindow();
            void clear(const ValkyrieNS::Color &oColor);
            void display();
            
            bool isOpen() const;

            void debugStuff();

            virtual ~Window();
    
        protected:
        private:
        };
    };
};

#endif
