//
//  Window.cpp
//  NordicOS
//
//  Created by Max Hooton on 17/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./WindowOS.hpp"
#include "../../ExceptionHandler/Errors.hpp"
#include "../../String/String.hpp"
#include "../Wrapper/AutoReleasePool.hpp"
#include "../Conversion/OBJC.hpp"
#include "../Application/Application.hpp"
#include "../Application/Delegate.hpp"
#include "../Input/KeyboardHelper.hpp"
#include "../Application/Controller.hpp"
#include "./Controller.hpp"

namespace NordicArts {
    namespace NordicOS {
        CGFloat getDefaultScaleFactor() {
            return [[NSScreen mainScreen] backingScaleFactor];
        }
        
        template<class T>
        void scaleIn(T &in, id<WindowDelegateProtocol> delegate) {
            in /= (delegate ? [delegate displayScaleFactor] : getDefaultScaleFactor());
        }
        
        template<class T>
        void scaleInWidthHeight(T &in, id<WindowDelegateProtocol> delegate) {
            scaleIn(in.m_iWidth, delegate);
            scaleIn(in.m_iHeight, delegate);
        }
        
        template<class T>
        void scaleInXY(T &in, id<WindowDelegateProtocol> delegate) {
            scaleIn(in.iX, delegate);
            scaleIn(in.iY, delegate);
        }
        
        template<class T>
        void scaleOut(T &out, id<WindowDelegateProtocol> delegate) {
            out *= (delegate ? [delegate displayScaleFactor] : getDefaultScaleFactor());
        }
        
        template<class T>
        void scaleOutWidthHeight(T &out, id<WindowDelegateProtocol> delegate) {
            scaleOut(out.iWidth, delegate);
            scaleOut(out.iHeight, delegate);
        }
        
        template<class T>
        void scaleOutXY(T &out, id<WindowDelegateProtocol> delegate) {
            scaleOut(out.iX, delegate);
            scaleOut(out.iY, delegate);
        }
        
        WindowOS::WindowOS(WindowHandle hHandle) : m_bShowCursor(true) {
            retainPool();
            
            id nsHandle = (id)hHandle;
            if ([nsHandle isKindOfClass:[NSWindow class]]) {
                m_Delegate = [[NAWindowController alloc] initWithWindow:nsHandle];
            } else if ([nsHandle isKindOfClass:[NSView class]]) {
                m_Delegate = [[NAViewController alloc] initWithView:nsHandle];
            } else {
                error() << "Can't import this window" << std::endl;
                
                return;
            }
            
            [m_Delegate setRequesterTo:this];
            
            initaliseKeyboardHelper();
        }
        
        WindowOS::WindowOS(VideoMode mode, const String &cTitle, unsigned long lStyle, const ContextSettings &) : m_bShowCursor(true) {
            setUpProcess();
            
            retainPool();
            
            scaleInWidthHeight(mode, nil);
            
            m_Delegate = [[NAWindowController alloc] initWithMode:mode andStyle:lStyle];
            [m_Delegate changeTitle:stringToNSString(cTitle)];
            [m_Delegate setRequesterTo:this];
            
            initaliseKeyboardHelper();
        }
        
        WindowOS::~WindowOS() {
            [m_Delegate closeWindow];
            [m_Delegate release];
            
            NSArray *aWindows = [NSApp orderedWindows];
            if ([aWindows count] > 0) {
                [[aWindows objectAtIndex:0] makeKeyAndOrderFront:nil];
            }
            
            releasePool();
            drainPool();
        }
        
        void WindowOS::applyContext(OpenGLRef context) const {
            [m_Delegate applyContext:context];
        }
        
        void WindowOS::setUpProcess(void) {
            static bool bIsProcessAsApplication = false;
            if(!bIsProcessAsApplication) {
                bIsProcessAsApplication = true;
                
                [NAApplication sharedApplication];
                
                [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
                [NSApp activateIgnoringOtherApps:YES];
                
                if (![[NAApplication sharedApplication] delegate]) {
                    [NSApp setDelegate:[[[NAApplicationDelegate alloc] init] autorelease]];
                }
                
                [NAApplication setUpMenuBar];
                [[NAApplication sharedApplication] finishLaunching];
            }
        }
        
        void WindowOS::windowClosed(void) {
            Event oEvent;
            oEvent.type = Event::Closed;
            
            pushEvent(oEvent);
        }
        
        void WindowOS::windowResized(unsigned int iWidth, unsigned int iHeight) {
            Event oEvent;
            oEvent.type         = Event::Resized;
            oEvent.size.iWidth   = iWidth;
            oEvent.size.iHeight  = iHeight;
            
            scaleOutWidthHeight(oEvent.size, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        void WindowOS::windowLostFocus(void) {
            if (!m_bShowCursor) {
                [m_Delegate showMouseCursor];
            }
            
            Event oEvent;
            oEvent.type = Event::LostFocus;
            
            pushEvent(oEvent);
        }
        
        void WindowOS::windowGainedFocus(void) {
            if (!m_bShowCursor) {
                [m_Delegate hideMouseCursor];
            }
            
            Event oEvent;
            oEvent.type = Event::GainedFocus;
            
            pushEvent(oEvent);
        }
        
        void WindowOS::mouseDownAt(Mouse::Button eButton, int iX, int iY) {
            Event oEvent;
            oEvent.type                 = Event::MouseButtonPressed;
            oEvent.mouseButton.button   = eButton;
            oEvent.mouseButton.iX       = iX;
            oEvent.mouseButton.iY       = iY;
            
            scaleOutXY(oEvent.mouseButton, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        void WindowOS::mouseUpAt(Mouse::Button eButton, int iX, int iY) {
            Event oEvent;
            oEvent.type                 = Event::MouseButtonReleased;
            oEvent.mouseButton.button   = eButton;
            oEvent.mouseButton.iX       = iX;
            oEvent.mouseButton.iY       = iY;
            
            scaleOutXY(oEvent.mouseButton, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        void WindowOS::mouseMovedAt(int iX, int iY) {
            Event oEvent;
            oEvent.type             = Event::MouseMoved;
            oEvent.mouseMove.iX     = iX;
            oEvent.mouseMove.iY     = iY;
            
            scaleOutXY(oEvent.mouseMove, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        
    };
};
