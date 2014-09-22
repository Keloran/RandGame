//
//  View.cpp
//  NordicOS
//
//  Created by Max Hooton on 21/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "../Window/WindowOS/WindowOS.hpp"
#include "../Input/HIDInputManager.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#import "../Input/KeyboardHelper.hpp"
#import "./View.hpp"
#import "../Window/SilentResponder/SilentResponder.hpp"

BOOL isValidTextUnicode(NSEvent *event);

@interface NAOpenGLView()

-(void)updateScaleFactor;
-(void)viewDidEndLiveResize;
-(void)updateMouseState;
-(void)windowDidBecomeKey:(NSNotification *)notification;
-(void)windowDidResignKey:(NSNotification *)notification;
-(void)enterFullScreen;
-(void)exitFullScreen;

-(BOOL)isMouseInside;

-(NordicArts::NordicOS::Mouse::Button)mouseButtonFromEvent:(NSEvent *)event;

+(NordicArts::NordicOS::Event::KeyEvent)convertNSKeyEventToNAEvent:(NSEvent *)event;

@end

@implementation NAOpenGLView

-(id)initWithFrame:(NSRect)frameRect {
    return [self initWithFrame:frameRect fullScreen:NO];
}

-(id)initWithFrame:(NSRect)frameRect fullScreen:(BOOL)isFullScreen {
    if ((self = [super initWithFrame:frameRect])) {
        [self setRequesterTo:0];
        [self enableKeyRepeat];
        
        m_bMouseIsIn = [self isMouseInside];
        
        NSUInteger opts = (NSTrackingActiveAlways | NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingEnabledDuringMouseDrag);
        m_pTrackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds] options:opts owner:self userInfo:nil];
        [self addTrackingArea:m_pTrackingArea];
        
        m_bFullScreen = isFullScreen;
        
        m_fScaleFactor = 1.0;
        
        m_pSilentResponder  = [[NASilentResponder alloc] init];
        m_pHiddenTextView   = [[NSTextView alloc] initWithFrame:NSZeroRect];
        [m_pHiddenTextView setNextResponder:m_pSilentResponder];
        
        [self setWantsBestResolutionOpenGLSurface:YES];
    }
    
    return self;
}

-(void)finishInit {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidBecomeKey:) name:NSWindowDidBecomeKeyNotification object:[self window]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResignKey:) name:NSWindowDidResignKeyNotification object:[self window]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResignKey:) name:NSWindowWillCloseNotification object:[self window]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateScaleFactor) name:NSWindowDidChangeScreenNotification object:[self window]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateScaleFactor) name:NSWindowDidChangeScreenProfileNotification object:[self window]];
    
    [self updateScaleFactor];
}

-(void)setRequesterTo:(NordicArts::NordicOS::WindowOS *)requester {
    m_pRequester = requester;
}

-(NSPoint)convertPointToScreen:(NSPoint)point {
    NSRect rect = NSZeroRect;
    rect.origin = point;
    rect = [[self window] convertRectToScreen:rect];
    
    return rect.origin;
}

-(NSPoint)computeGlobalPositionOfRelativePoint:(NSPoint)point {
    point.y = ([self frame].size.height - point.y);
    
    point = [self convertPoint:point toView:self];
    point = [self convertPoint:point toView:nil];
    point = [self convertPointToScreen:point];
    
    const float fScreenHeight = [[[self window] screen] frame].size.height;
    point.y = (fScreenHeight - point.y);
    
    return point;
}

-(void)enableKeyRepeat {
    m_bUseKeyRepeat = YES;
}
-(void)disableKeyRepeat {
    m_bUseKeyRepeat = NO;
}

-(CGFloat)displayScaleFactor {
    return m_fScaleFactor;
}

-(void)updateScaleFactor {
    NSWindow *pWindow = [self window];
    NSScreen *pScreen = (pWindow ? [pWindow screen] : [NSScreen mainScreen]);
    
    m_fScaleFactor = [pScreen backingScaleFactor];
}

-(void)viewDidEndLiveResize {
    [super viewDidEndLiveResize];
    
    [self updateMouseState];
    [self update];
    
    if (m_pRequester == 0) {
        return;
    }
    
    NSSize newSize = [self frame].size;
    m_pRequester->windowResized(newSize.width, newSize.height);
}

-(BOOL)isMouseInside {
    NSPoint relativeToWindow    = [[self window] mouseLocationOutsideOfEventStream];
    NSPoint relativeToView      = [self convertPoint:relativeToWindow fromView:nil];
    
    return NSPointInRect(relativeToView, [self bounds]);
}

-(void)updateMouseState {
    BOOL bMouseWasIn = m_bMouseIsIn;
    m_bMouseIsIn = [self isMouseInside];

    if (m_pRequester == 0) {
        return;
    }

    if (bMouseWasIn && !m_bMouseIsIn) {
        m_pRequester->mouseMovedOut();
    } else if (!bMouseWasIn && m_bMouseIsIn) {
        m_pRequester->mouseMovedIn();
    }
}

-(void)windowDidBecomeKey:(NSNotification *)notification {
    (void)notification;

    if (m_pRequester) {
        m_pRequester->windowGainedFocus();
    }

    if (m_bFullScreen) {
        [self enterFullScreen];
    }
}

-(void)windowDidResignKey:(NSNotification *)notification {
    (void)notification;
    
    if (m_pRequester) {
        m_pRequester->windowLostFocus();
    }

    if (m_bFullScreen) {
        [self exitFullScreen];
    }
}

-(void)enterFullScreen {
    [self removeTrackingArea:m_pTrackingArea];
    [self addTrackingArea:m_pTrackingArea];

    if (!m_bMouseIsIn && (m_pRequester != 0)) {
        m_pRequester->mouseMovedIn();
    }

    m_bMouseIsIn = YES;
}

-(void)exitFullScreen {
    [self removeTrackingArea:m_pTrackingArea];

    if (m_bMouseIsIn && (m_pRequester != 0)) {
        m_pRequester->mouseMovedOut();
    }

    m_bMouseIsIn = NO;
}

-(void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];

    [self removeTrackingArea:m_pTrackingArea];

    [m_pHiddenTextView release];
    [m_pSilentResponder release];
    [m_pTrackingArea release];

    [self setRequesterTo:0];

    [super dealloc];
}

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)canBecomeKeyView {
    return YES;
}

-(void)mouseDown:(NSEvent *)theEvent {
    [self otherMouseDown:theEvent];

    [[self nextResponder] mouseDown:theEvent];
}

-(void)mouseUp:(NSEvent *)theEvent {
    [self otherMouseUp:theEvent];

    [[self nextResponder] mouseUp:theEvent];
}

-(void)mouseMoved:(NSEvent *)theEvent {
    [self otherMouseDragged:theEvent];

    [[self nextResponder] mouseMoved:theEvent];
}

-(void)scrollWheel:(NSEvent *)theEvent {
    if (m_pRequester != 0) {
        NSPoint loc = [self cursorPositionFromEvent:theEvent];
        m_pRequester->mouseWheelScrolledAt([theEvent deltaY], loc.x, loc.y);
    }

    [[self nextResponder] scrollWheel:theEvent];
}

-(void)mouseEntered:(NSEvent *)theEvent {
    (void)theEvent;

    [self updateMouseState];
}

-(void)mouseExited:(NSEvent *)theEvent {
    (void)theEvent;

    [self updateMouseState];
}

-(void)rightMouseDown:(NSEvent *)theEvent {
    [self otherMouseDown:theEvent];

    [[self nextResponder] rightMouseDown:theEvent];
}

-(void)rightMouseUp:(NSEvent *)theEvent {
    [self otherMouseUp:theEvent];

    [[self nextResponder] rightMouseUp:theEvent];
}

-(void)otherMouseDown:(NSEvent *)theEvent {
    NordicArts::NordicOS::Mouse::Button button = [self mouseButtonFromEvent:theEvent];

    if (m_pRequester != 0) {
        NSPoint loc = [self cursorPositionFromEvent:theEvent];
    
        if (button != NordicArts::NordicOS::Mouse::ButtonCount) {
            m_pRequester->mouseDownAt(button, loc.x, loc.y);
        }
    }

    if ((button != NordicArts::NordicOS::Mouse::Left) && (button != NordicArts::NordicOS::Mouse::Right)) {
        [[self nextResponder] otherMouseDown:theEvent];
    }
}

-(void)otherMouseUp:(NSEvent *)theEvent {
    NordicArts::NordicOS::Mouse::Button button = [self mouseButtonFromEvent:theEvent];

    if (m_pRequester != 0) {
        NSPoint loc = [self cursorPositionFromEvent:theEvent];

        if (button != NordicArts::NordicOS::Mouse::ButtonCount) {
            m_pRequester->mouseUpAt(button, loc.x, loc.y);
        }
    }

    if ((button != NordicArts::NordicOS::Mouse::Left) && (button != NordicArts::NordicOS::Mouse::Right)) {
        [[self nextResponder] otherMouseUp:theEvent];
    }
}

-(void)rightMouseDragged:(NSEvent *)theEvent {
    [self otherMouseDragged:theEvent];

    [[self nextResponder] rightMouseDragged:theEvent];
}

-(void)mouseDragged:(NSEvent *)theEvent {
    [self otherMouseDragged:theEvent];

    [[self nextResponder] mouseDragged:theEvent];
}

-(void)otherMouseDragged:(NSEvent *)theEvent {
    if (m_pRequester != 0) {
        NSPoint loc = [self cursorPositionFromEvent:theEvent];

        [self updateMouseState];
        if (m_bMouseIsIn) {
            m_pRequester->mouseMovedAt(loc.x, loc.y);
        }
    }

    NordicArts::NordicOS::Mouse::Button button = [self mouseButtonFromEvent:theEvent];
    if ((button != NordicArts::NordicOS::Mouse::Left) && (button != NordicArts::NordicOS::Mouse::Right)) {
        [[self nextResponder] otherMouseUp:theEvent];
    }
}

-(NSPoint)cursorPositionFromEvent:(NSEvent *)theEvent {
    NSPoint loc;
    if (theEvent == nil) {
        NSPoint rawPos = [[self window] mouseLocationOutsideOfEventStream];
        loc = [self convertPoint:rawPos fromView:nil];
    } else {
        loc = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    }

    float fH = [self frame].size.height;
    loc.y = (fH - loc.y);

    return loc;
}

-(NordicArts::NordicOS::Mouse::Button)mouseButtonFromEvent:(NSEvent *)theEvent {
    switch ([theEvent buttonNumber]) {
        case 0: return NordicArts::NordicOS::Mouse::Left;
        case 1: return NordicArts::NordicOS::Mouse::Right;
        case 2: return NordicArts::NordicOS::Mouse::Middle;
        case 3: return NordicArts::NordicOS::Mouse::XButton1;
        case 4: return NordicArts::NordicOS::Mouse::XButton2;

        default: return NordicArts::NordicOS::Mouse::ButtonCount;
    }
}

-(void)keyDown:(NSEvent *)theEvent {
    [[self nextResponder] keyDown:theEvent];

    if (m_pRequester == 0) {
        return;
    }

    if (m_bUseKeyRepeat || ![theEvent isARepeat]) {
        NordicArts::NordicOS::Event::KeyEvent key = [NAOpenGLView convertNSKeyEventToNAEvent:theEvent];

        if (key.code != NordicArts::NordicOS::Keyboard::Unknown) {
            m_pRequester->keyDown(key);
        }
    }

    if (m_bUseKeyRepeat || ![theEvent isARepeat]) {
        if (isValidTextUnicode(theEvent)) {
            [m_pHiddenTextView interpretKeyEvents:[NSArray arrayWithObject:theEvent]];
        }

        unsigned short keyCode = [theEvent keyCode];
        if (keyCode == 0x33) {
            m_pRequester->textEntered(8);
        } else if ((keyCode == 0x75) || (keyCode == NSDeleteFunctionKey)) {
            m_pRequester->textEntered(127);
        } else {
            NSString *pString = [m_pHiddenTextView string];

            for (NSUInteger index = 0; index < [pString length]; ++index) {
                m_pRequester->textEntered([pString characterAtIndex:index]);
            }

            [m_pHiddenTextView setString:@""];
        }
    }
}

-(void)naKeyUp:(NSEvent *)theEvent {
    [[self nextResponder] keyUp:theEvent];

    if (m_pRequester == 0) {
        return;
    }

    NordicArts::NordicOS::Event::KeyEvent key = [NAOpenGLView convertNSKeyEventToNAEvent:theEvent];
    if (key.code != NordicArts::NordicOS::Keyboard::Unknown) {
        m_pRequester->keyUp(key);
    }
}

-(void)flagsChanged:(NSEvent *)theEvent {
    [[self nextResponder] flagsChanged:theEvent];

    if (m_pRequester == 0) {
        return;
    }

    NSUInteger modifiers = [theEvent modifierFlags];
    handleModifiersChanged(modifiers, *m_pRequester);
}

+(NordicArts::NordicOS::Event::KeyEvent)convertNSKeyEventToNAEvent:(NSEvent *)theEvent {
    NordicArts::NordicOS::Keyboard::Key key = NordicArts::NordicOS::Keyboard::Unknown;

    NSString *pString = [theEvent charactersIgnoringModifiers];
    if ([pString length] > 0) {
        key = NordicArts::NordicOS::HIDInputManager::localizedKeys([pString characterAtIndex:0]);
    }

    if (key == NordicArts::NordicOS::Keyboard::Unknown) {
        key = NordicArts::NordicOS::HIDInputManager::nonLocalizedKeys([theEvent keyCode]);
    }

    return keyEventWithModifiers([theEvent modifierFlags], key);
}

@end

BOOL isValidTextUnicode(NSEvent *pEvent) {
    if ([pEvent keyCode] == 0x35) {
        return false;
    } else if ([[pEvent characters] length] > 0) {
        unichar code = [[pEvent characters] characterAtIndex:0];
    
        return ((code < 0xF700) || (code > 0xF8FF));
    } else {
        return true;
    }
}
