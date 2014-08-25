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

        Window::~Window() {
        }

        void Window::debugStuff() {
            std::cout << "Resolution: " << "Width: " << m_iWidth << ", Height: " << m_iHeight << std::endl;
            std::cout << "OpenGL: " << "Major: " << m_iOpenGLMajor << ", Minor: " << m_iOpenGLMinor << std::endl;
            std::cout << "FrameRate: " << m_iFrameLimit << std::endl;
        }
    };
};
