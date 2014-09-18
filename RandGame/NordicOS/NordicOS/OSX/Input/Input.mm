#include "../../Window/VideoMode/VideoMode.hpp"
#include "../../Window/Window.hpp"
#include "./Input.hpp"
#include "./HIDInputManager.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#import "../Window/OpenGLView.hpp"
#import <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        NAOpenGLView *getNAOpenGLViewFromWindow(const Window &oWindow) {
            id nsHandle = (id)oWindow.getSystemHandle();

            NAOpenGLView *pView = nil;
            if([nsHandle isKindOfClass:[NSWindow class]]) {
                pView = [nsHandle contentView];
                if ([pView isKindOfClass:[NAOpenGLView class]]) {
                    error() << "Not valid view" << std::endl;
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
                    error() << "Can't handle the window" << std::endl;
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
        glm::vec2 InputImp::getMousePosition() {
            NSPoint pos = [NSEvent mouseLocation];
            pos.y       = (VideoMode::getDesktopMode().iHeight - pos.y);
            
            int iScale = [[NSScreen mainScreen] backingScaleFactor];
        
            return (glm::vec2(pos.x, pos.y) * iScale);
        }
        glm::vec2 InputImp::getMousePositon(const Window &oWindow) {
            NAOpenGLView *pView = getNAOpenGLViewFromWindow(oWindow);
            if (pView == nil) {
                return glm::vec2();
            }

            NSPoint pos = [pView cursorPositionFromEvent:nil];

            int iScale = [pView displayScaleFactor];

            return (glm::vec2(pos.x, pos.y) * iScale);
        }
        void InputImp::setMousePositon(const glm::vec2 &vPosition) {
            int iScale = [[NSScreen mainScreen] backingScaleFactor];

            CGPoint pos = CGPointMake((vPosition.x / iScale), (vPosition.y / iScale));

            CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, pos, 0);
            CGEventPost(kCGHIDEventTab, event);
            CFRelease(event);
        }
        void InputImp::setMousePosition(const glm::vec2 &vPosition, const Window &oWindow) {
            NAOpenGLView *pView = getNAOpenGLViewFromWindow(oWindow);
            if (pView == nil) {
                return;
            }

            int iScale  = [pView displayScaleFactor];
            NSPoint p   = NSMakePoint((vPosition.x / iScale), (vPosition.y / iScale));
            p           = [pView computeGlobalPositionOfRelativePoint:p];
            
            setMousePosition(glm::vec2(p.x, p.y) * iScale);
        }
    };
};
