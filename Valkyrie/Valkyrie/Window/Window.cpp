#include "./Window.hpp"

namespace NordicArts {
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
};
