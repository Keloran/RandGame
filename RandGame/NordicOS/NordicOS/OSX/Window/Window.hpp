//
//  Window.h
//  NordicOS
//
//  Created by Max Hooton on 17/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Window_OS_H
#define NordicArts_NordicOS_Window_OS_H

#include "../../Window/Event/Event.hpp"
#include "../../Window/Window/WindowImp.hpp"
#include "../../String/String.hpp"

#ifdef __OBJC__
#import "../Window/DelegateProtocol.hpp"
typedef id<DelegateProtocol, NSObject> DelegateRef;

@class NSOpenGLContext;
typedef NSOpenGLContext *OpenGLRef;
#else
typedef unsigned short unichar;
typedef void *DelegateRef;
typedef void *OpenGLRef;
#endif

namespace NordicArts {
    namespace NordicOS {
        class WindowOS : public WindowImp {
        // Variables
        public:
        protected:
        private:
            DelegateRef m_Delegate;
            
            bool        m_bShowCursor;
            
        //Methods
        public:
            WindowOS(VideoMode mode, const String &cString, unsigned long lStyle, const ContextSettings &oSettings);
            
            ~WindowOS();
            
            void windowClosed(void);
            void windowResized(unsigned int iWidth, unsigned int iHeight);
            void windowLostFocus(void);
            void windowGainedFocus(void);
            void mouseDownAt(Mouse::Button eButton, int iX, int iY);
            void mouseUpAt(Mouse::Button eButton, int iX, int iY);
            void mouseMovedAt(int iX, int iY);
            void mouseWheelScrolledAt(float fDelta, int iX, int iY);
            void mouseMovedIn(void);
            void mouseMovedOut(void);
            void keyDown(Event::KeyEvent eKey);
            void keyUp(Event::KeyEvent eKey);
            void textEntered(unichar charCode);
            void applyContext(OpenGLRef context) const;
            
            static void setUpProcess(void);
            
            virtual WindowHandle getSystemHandle() const;

            virtual glm::vec2 getPosition() const;
            virtual glm::vec2 getSize() const;
            
            virtual void setPosition(const glm::vec2 &vPosition);
            virtual void setSize(const glm::vec2 &vSize);
            virtual void setTitle(const String &cTitle);
            virtual void setIcon(unsigned int iWidth, unsigned int iHeight, const UINT8 *pPixels);
            virtual void setVisible(bool bVisible);
            virtual void setMouseCursorVisible(bool bVisible);
            virtual void setKeyRepeatEnabled(bool bEnabled);
            
        protected:
            virtual void processEvents();
            
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__Window__) */
