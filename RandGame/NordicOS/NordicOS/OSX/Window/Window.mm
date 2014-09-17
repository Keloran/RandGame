//
//  Window.cpp
//  NordicOS
//
//  Created by Max Hooton on 17/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Window.hpp"
#include "../../ExceptionHandler/Errors.hpp"
#include "../../String/String.hpp"
#include "../AutoReleasePoolWrapper.hpp"
#include "../Conversion.hpp"
#include "../Application/Application.hpp"
#include "../Application/Delegate.hpp"
#include "../KeyBoardHelper.hpp"
#include "../Application/View.hpp"
#include "../Application/Window.hpp"

namespace NordicArts {
    namespace NordicOS {
        CGFloat getDefaultScaleFactor() {
            return [[NSScreen mainScreen] backingScaleFactor];
        }
        
        template<class T>
        void scaleIn(T &in, id<DelegateProtocol> delegate) {
            in /= (delegate ? [delegate displayScaleFactor] : getDefaultScaleFactor());
        }
        
        template<class T>
        void scaleInWidthHeight(T &in, id<DelegateProtocol> delegate) {
            scaleIn(in.width, delegate);
            scaleIn(in.height, delegate);
        }
        
        template<class T>
        void scaleInXY(T &in, id<DelegateProtocol> delegate) {
            scaleIn(in.x, delegate);
            scaleIn(in.y, delegate);
        }
        
        template<class T>
        void scaleOut(T &out, id<DelegateProtocol> delegate) {
            out *= (delegate ? [delegate displayScaleFactor] : getDefaultScaleFactor());
        }
        
        template<class T>
        void scaleOutWidthHeight(T &out, id<DelegateProtocol> delegate) {
            scaleOut(out.width, delegate);
            scaleOut(out.height, delegate);
        }
        
        template<class T>
        void scaleOutXY(T &out, id<DelegateProtocol> delegate) {
            scaleOut(out.x, delegate);
            scaleOut(out.y, delegate);
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
            
            initalizeKeyboardHelper();
        }
        
        WindowOS::WindowOS(VideoMode mode, const String &cTitle, unsigned long lStyle, const ContextSettings &) : m_bShowCursor(true) {
            setUpProcess();
            
            retainPool();
            
            scaleInWidthHeight(mode, nil);
            
            m_Delegate = [[NAWindowController alloc] initWithMode:mode andStyle:lStyle];
            [m_Delegate changeTitle:StringToNSString(cTitle)];
            [m_Delegate setRequesterTo:this];
            
            initalizeKeyboardHelper();
        }
        
        WindowOS::~WindowOS() {
            [m_Delegate closeWindow];
            [m_Delegate release];
            
            NSArray *aWindows = [NSApp orderedWindows];
            if ([aWindows count] > 0) {
                [[aWindoiws objectAtIndex:0] makeKeyAndOrderFront:nil];
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
                
                if (![[NAApplicatgion sharedApplication] delegate]) {
                    [NSApp setDelegate:[[[NAApplicationDelegate alloc] init] autorelease]];
                }
                
                [NAApplication setUpMenuBar];
                [[NAApplication sharedApplication] finishLoading];
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
            oEvent.size.width   = iWidth;
            oEvent.size.height  = iHeight;
            
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
            oEvent.mouseButton.x        = iX;
            oEvent.mouseButton.y        = iY;
            
            scaleOutXY(oEvent.mouseButton, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        void WindowOS::mouseUpAt(Mouse::Button eButton, int iX, int iY) {
            Event oEvent;
            oEvent.type             = Event::MouseButtonReleased;
            oEvent.mouseButton      = eButton;
            oEvent.mouseButton.x    = iX;
            oEvent.mouseButton.y    = iY;
            
            scaleOutXY(oEvent.mouseButton, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        void WindowOS::mouseMovedAt(int iX, int iY) {
            Event oEvent;
            oEvent.type             = Event::MouseMoved;
            oEvent.mouseMove.x      = iX;
            oEvent.MouseMove.y      = iY;
            
            scaleOutXY(oEvent.mouseMove, m_Delegate);
            
            pushEvent(oEvent);
        }
        
        
    };
};
