#include "../../Window/Window/VideoMode/VideoMode.hpp"
#include "../../Window/Window.hpp"
#include "./Input.hpp"
#include "./HIDInputManager.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#import "../OpenGL/View.hpp"
#import <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        NAOpenGLView *getNAOpenGLViewFromWindow(const Window &oWindow) {
            //id nsHandle = (id)oWindow.getSystemHandle();
            id nsHandle = (__bridge id)oWindow.getSystemHandle();

            NAOpenGLView *pView = nil;
            if([nsHandle isKindOfClass:[NSWindow class]]) {
                pView = [nsHandle contentView];
                if ([pView isKindOfClass:[NAOpenGLView class]]) {
                    Errors() << "Not valid view" << std::endl;
                    pView = nil;
                }
            } else if ([nsHandle isKindOfClass:[NSView class]]) {
                NSArray *aSubViews = [nsHandle subviews];
                for (NSView *pSubView in aSubViews) {
                    if ([pSubView isKindOfClass:[NAOpenGLView class]]) {
                        pView = (NAOpenGLView*)pSubView;
                        break;
                    }
                }

                if (pView == nil) {
                    Errors() << "Can't handle the window" << std::endl;
                }
            }

            return pView;
        }

        // Keyboard
        bool InputImp::isKeyPressed(Keyboard::Key key) {
            return HIDInputManager::getInstance().isKeyPressed(key);
        }
        void InputImp::setVirtualKeyboardVisible(bool /*bVisible*/) {}

        // Mouse
        bool InputImp::isMouseButtonPressed(Mouse::Button button) {
            return HIDInputManager::getInstance().isMouseButtonPressed(button);
        }
        Vector2i InputImp::getMousePosition() {
            NSPoint pos = [NSEvent mouseLocation];
            pos.y       = (VideoMode::getDesktopMode().getHeight() - pos.y);
            
            int iScale = [[NSScreen mainScreen] backingScaleFactor];
        
            return (Vector2i(pos.x, pos.y) * iScale);
        }
        Vector2i InputImp::getMousePosition(const Window &oWindow) {
            NAOpenGLView *pView = getNAOpenGLViewFromWindow(oWindow);
            if (pView == nil) {
                return Vector2i();
            }

            NSPoint pos = [pView cursorPositionFromEvent:nil];

            int iScale = [pView displayScaleFactor];

            return (Vector2i(pos.x, pos.y) * iScale);
        }
        void InputImp::setMousePosition(const Vector2i &vPosition) {
            int iScale = [[NSScreen mainScreen] backingScaleFactor];

            CGPoint pos = CGPointMake((vPosition.x / iScale), (vPosition.y / iScale));

            CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, pos, 0);
            CGEventPost(kCGHIDEventTap, event);
            CFRelease(event);
        }
        void InputImp::setMousePosition(const Vector2i &vPosition, const Window &oWindow) {
            NAOpenGLView *pView = getNAOpenGLViewFromWindow(oWindow);
            if (pView == nil) {
                return;
            }

            int iScale  = [pView displayScaleFactor];
            NSPoint p   = NSMakePoint((vPosition.x / iScale), (vPosition.y / iScale));
            p           = [pView computeGlobalPositionOfRelativePoint:p];
            
            setMousePosition(Vector2i(p.x, p.y) * iScale);
        }
    };
};
