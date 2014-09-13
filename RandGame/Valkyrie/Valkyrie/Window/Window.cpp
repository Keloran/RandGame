#include "./Window.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        Window::Window() {}
        Window::Window(int iX, int iY) : m_iWidth(iX), m_iHeight(iY) {}
        Window::Window(int iX, int iY, std::string cTitle) : m_iWidth(iX), m_iHeight(iY), m_cTitle(cTitle) {}     

        void Window::setWidth(int iX) {
            m_iWidth = iX;
        }
        void Window::setHeight(int iY) {
            m_iHeight = iY;
        }
        void Window::setDimensions(int iX, int iY) {
            m_iWidth    = iX;
            m_iHeight   = iY;
        }
        void Window::setTitle(std::string cTitle) {
            m_cTitle = cTitle;
        }
        void Window::setFramerateLimit(int iFrameLimit) {
            m_iFrameLimit = iFrameLimit;
        }
        void Window::setOpenGL(int iMajor, int iMinor) {
            m_iOpenGLMajor = iMajor;
            m_iOpenGLMinor = iMinor;
        }
        
        bool Window::isOpen() const {
            return m_pWindow->isOpen();
        }
        
        void Window::clear(const ValkyrieNS::Color &oColor) {
            sf::Color sfColor(oColor.m_iRed, oColor.m_iGreen, oColor.m_iBlue, oColor.m_iAlpha);
            
            m_pWindow->clear(sfColor);
        }
        
        void Window::createWindow() {
            sf::RenderWindow oWindow;
            m_pWindow = &oWindow;
            
            m_pWindow->create(sf::VideoMode(m_iWidth, m_iHeight), m_cTitle);
            m_pWindow->setFramerateLimit(m_iFrameLimit);
        }
        void Window::display() {
            m_pWindow->display();
        }
        
        Window::~Window() {
        }

        void Window::debugStuff() {
            std::cout << "Resolution: " << "Width: " << m_iWidth << ", Height: " << m_iHeight << std::endl;
            std::cout << "OpenGL: " << "Major: " << m_iOpenGLMajor << ", Minor: " << m_iOpenGLMinor << std::endl;
            std::cout << "FrameRate: " << m_iFrameLimit << std::endl;
        }
    };
};
