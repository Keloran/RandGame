#ifndef NordicArts_NordicOS_Window_Window_H
#define NordicArts_NordicOS_Window_Window_H

#include "./ContextSettings.hpp"
#include "./VideoMode/VideoMode.hpp"
#include "./WindowHandle.hpp"
#include "./WindowStyle.hpp"
#include "./GL/Resource.hpp"
#include "../../Time/Time.hpp"
#include "../../Maths/Vector2.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include "../../String/String.hpp"
#include "../../Logger/Logger.hpp"

namespace NordicArts {
    namespace NordicOS {
        class GLContext;
        class WindowImp;
        class Event;

        class Window : GLResource, NonCopyable {
        // Variables
        public:
        protected:
        private:
            WindowImp       *m_pImp = nullptr;
            GLContext       *m_pContext = nullptr;

            Clock           m_oClock;
            Time            m_oFrameTimeLimit;
        
            Vector2u       m_vSize;

            Logger         *m_pLogger = nullptr;

        // Methods
        public:
            Window();
            Window(Logger *pLogger, VideoMode mode, const String &cTitle, UINT32 iStyle = Style::Default, const ContextSettings &oSettings = ContextSettings());
            explicit Window(Logger *pLogger, WindowHandle hHandle, const ContextSettings &oSettings = ContextSettings());

            virtual ~Window();

            void create(VideoMode mode, const String &cTitle, UINT32 iStyle = Style::Default, const ContextSettings &oSettings = ContextSettings());
            void create(WindowHandle hHandle, const ContextSettings &oSettings = ContextSettings());
            void close();
            void setPosition(const Vector2i &oPosition);
            void setSize(const Vector2u &oSize);
            void setTitle(const String &cTitle);
            void setIcon(unsigned int iWidth, unsigned int iHeight, const UINT8 *pPixels);
            void setVisible(bool bVisible);
            void setVerticalSyncEnabled(bool bEnabled);
            void setMouseCursorVisible(bool bVisible);
            void setKeyRepeatEnabled(bool bEnabled);
            void setFramerateLimit(unsigned int iLimit);
            void display();

            bool isOpen() const;
            bool pollEvent(Event &oEvent);
            bool waitEvent(Event &oEvent);
            bool setActive(bool bActive = true) const;

            Vector2i getPosition() const;
            Vector2u getSize() const;

            const ContextSettings &getSettings() const;

            WindowHandle getSystemHandle() const;

        protected:
            virtual void onCreate();
            virtual void onResize();

        private:
            bool filterEvent(const Event &oEvent);

            void initalize();

        };    
    };
};

#endif
