#include "./Window.hpp"
#include "./GL/Context.hpp"
#include "./WindowImp.hpp"
#include "../../Threading/Sleep/Sleep.hpp"
#include "../../ExceptionHandler/Errors.hpp"
#include "../../Logger/Logger.hpp"

namespace NordicArts {
    namespace NordicOS {
        const Window *pFullScreenWindow = nullptr;

        Window::Window() : m_pImp(nullptr), m_pContext(nullptr), m_oFrameTimeLimit(Time::Zero), m_vSize(0, 0) {
        }

        Window::Window(Logger *pLogger, VideoMode mode, const String &cTitle, UINT32 iStyle, const ContextSettings &oSettings) : m_pImp(nullptr), m_pContext(nullptr), m_oFrameTimeLimit(Time::Zero),  m_vSize(0, 0), m_pLogger(pLogger) {
            create(mode, cTitle, iStyle, oSettings);
        }
        Window::Window(Logger *pLogger, WindowHandle hHandle, const ContextSettings &oSettings) : m_pImp(nullptr), m_pContext(nullptr), m_oFrameTimeLimit(Time::Zero), m_vSize(0, 0), m_pLogger(pLogger) { 
            create(hHandle, oSettings);
        }

        Window::~Window() {
            close();
        }

        void Window::create(VideoMode mode, const String &cTitle, UINT32 iStyle, const ContextSettings &oSettings) {
            close();
        
            if (iStyle & Style::FullScreen) {
                if (pFullScreenWindow) {
                    m_pLogger->log("Only 1 full screen window allowed");

                    iStyle &= ~Style::FullScreen;
                } else {
                    if (!mode.isValid()) {
                        m_pLogger->log("Requested video mode not avalible");

                        mode = VideoMode::getFullScreenModes()[0];
                    }

                    pFullScreenWindow = this;
                }
            }

            if ((iStyle & Style::Close) || (iStyle & Style::Resize)) {
                iStyle |= Style::TitleBar;
            }

            m_pImp      = WindowImp::create(mode, cTitle, iStyle, oSettings);
            m_pContext  = GLContext::create(oSettings, m_pImp, mode.m_iBitsPerPixel);

            initalize();
        }

        void Window::create(WindowHandle hHandle, const ContextSettings &oSettings) {
            close();
            
            m_pImp      = WindowImp::create(hHandle);
            m_pContext  = GLContext::create(oSettings, m_pImp, VideoMode::getDesktopMode().m_iBitsPerPixel);

            initalize();
        }

        void Window::close() {
            delete m_pContext;
            m_pContext = nullptr;

            delete m_pImp;
            m_pImp = nullptr;

            if (this == pFullScreenWindow) {
                pFullScreenWindow = nullptr;
            }
        }            

        bool Window::isOpen() const {
            return (m_pImp != nullptr);
        }

        const ContextSettings &Window::getSettings() const {
            static const ContextSettings pEmpty(0, 0, 0);
            
            return (m_pContext ? m_pContext->getSettings() : pEmpty);
        }

        bool Window::pollEvent(Event &oEvent) {
            if (m_pImp && m_pImp->popEvent(oEvent, false)) {
                return filterEvent(oEvent);
            } else {
                return false;
            }
        }

        bool Window::waitEvent(Event &oEvent) {
            if (m_pImp && m_pImp->popEvent(oEvent, true)) {
                return filterEvent(oEvent);
            } else {
                return false;
            }
        }

        Vector2i Window::getPosition() const {
            return (m_pImp ? m_pImp->getPosition() : Vector2i());
        }

        void Window::setPosition(const Vector2i &oPosition) {
            if (m_pImp) {
                m_pImp->setPosition(oPosition);
            }
        }

        Vector2u Window::getSize() const {
            return m_vSize;
        }

        void Window::setSize(const Vector2u &oSize) {
            if (m_pImp) {
                m_pImp->setSize(oSize);

                m_vSize.x = oSize.x;
                m_vSize.y = oSize.y;

                onResize();
            }
        }

        void Window::setTitle(const String &cTitle) {
            if (m_pImp) {
                m_pImp->setTitle(cTitle);
            }
        }

        void Window::setIcon(unsigned int iWidth, unsigned int iHeight, const UINT8 *pPixels) {
            if (m_pImp) {
                m_pImp->setIcon(iWidth, iHeight, pPixels);
            }
        }

        void Window::setVisible(bool bVisible) {
            if (m_pImp) {
                m_pImp->setVisible(bVisible);
            }
        }

        void Window::setVerticalSyncEnabled(bool bEnabled) {
            if (setActive()) {
                m_pContext->setVerticalSyncEnabled(bEnabled);
            }
        }

        void Window::setMouseCursorVisible(bool bVisible) {
            if (m_pImp) {
                m_pImp->setMouseCursorVisible(bVisible);
            }
        }

        void Window::setKeyRepeatEnabled(bool bEnabled) {
            if (m_pImp) {
                m_pImp->setKeyRepeatEnabled(bEnabled);
            }
        }

        void Window::setFramerateLimit(unsigned int iLimit) {
            if (iLimit > 0) {
                m_oFrameTimeLimit = seconds(1.0f / iLimit);
            } else {
                m_oFrameTimeLimit = Time::Zero;
            }
        }

        bool Window::setActive(bool bActive) const {
            if (m_pContext) {
                if (m_pContext->setActive(bActive)) {
                    return true;
                } else {
                    m_pLogger->log("Window context isnt active");
        
                    return false;
                }
            } else {
                return false;
            }
        }

        void Window::display() {
            if (setActive()) {
                m_pContext->display();
            }

            if (m_oFrameTimeLimit != Time::Zero) {
                sleep(m_oFrameTimeLimit - m_oClock.getElapsedTime());
                m_oClock.restart();
            }
        }

        WindowHandle Window::getSystemHandle() const {
            return (m_pImp ? m_pImp->getSystemHandle() : 0);
        }

        void Window::onCreate() {
        }

        void Window::onResize() {
        }

        bool Window::filterEvent(const Event &oEvent) {
            if (oEvent.type == Event::Resized) {
                m_vSize.x = oEvent.size.iWidth;
                m_vSize.y = oEvent.size.iHeight;
            
                onResize();
            }
            
            return true;
        }

        void Window::initalize() {
            setVisible(true);
            setMouseCursorVisible(true);
            setVerticalSyncEnabled(false);
            setKeyRepeatEnabled(true);
            setFramerateLimit(0);

            m_vSize = m_pImp->getSize();

            m_oClock.restart();

            setActive();

            onCreate();
        }
    };
};
