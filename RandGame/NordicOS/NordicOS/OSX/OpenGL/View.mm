//
//  View.cpp
//  NordicOS
//
//  Created by Max Hooton on 21/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "../Window/WindowOS.hpp"
#include "../Input/HIDInputManager.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#import "../Input/KeyboardHelper.hpp"
#import "./View.hpp"
#import "../Window/SilentResponder.hpp"

BOOL isValidTextUnicode(NSEvent *event);

@interface NAOpenGLView()

-(void)updateScaleFactor;
-(void)viewDidEndLiveResize;
-(void)updateMouseState;
-(void)windowDidBecomeKey:(NSNotification *)notification;
-(void)windowDidAssignKey:(NSNotification *)notification;
-(void)enterFullscreen;
-(void)exitFullscreen;

-(BOOL)isMouseInside;

-(NordicArts::NordicOS::Mouse::Button)mouseButtonFromEvent:(NSEvent *)event;

-(NordicArts::NordicOS::Keyboard::Key)convertNSKeyEventToNAEvent:(NSEvent *)event;

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

