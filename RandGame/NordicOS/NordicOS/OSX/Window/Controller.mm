#include "../../Window/Window/VideoMode/VideoMode.hpp"
#include "../../Window/Window/WindowHandle.hpp"
#include "../../Window/Window/WindowStyle.hpp"
#include "./WindowOS.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#include <ApplicationServices/ApplicationServices.h>

#import "../Application/Application.hpp"
#import "../OpenGL/View.hpp"
#import "./Window.hpp"
#import "./Controller.hpp"

#import <OpenGL/OpenGL.h>

@interface NABlackView : NSView
@end

@implementation NABlackView

-(void)drawRect:(NSRect)dirtyRect {
    [[NSColor blackColor] setFill];
    NSRectFill(dirtyRect);
}

@end

@interface NAWindowController()

-(float)screenHeight;
-(float)titlebarHeight;

@end

@implementation NAWindowController

-(id)initWithWindow:(NSWindow*)window {
    if (self = [super init]) {
        m_pWindow       = nil;
        m_pOGLView      = nil;
        m_pRequester    = 0;

        m_pWindow = [window retain];
        if (m_pWindow == nil) {
            NordicArts::NordicOS::Errors() << "No window given" << std::endl;

            return self;
        }

        m_pOGLView = [[NAOpenGLView alloc] initWithFrame:[[m_pWindow contentView] frame] fullscreen:NO];
        if(m_pOGLView == nil) {
            NordicArts::NordicOS::Errors() << "OGL not working" << std::endl;

            return self;
        }

        [m_pWindow setContentView:m_pOGLView];
    }

    return self;
}

-(id)initWithMode:(const NordicArts::NordicOS::VideoMode&)mode andStyle:(unsigned long)style {
    if ([NSThread currentThread] != [NSThread mainThread]) {
        NordicArts::NordicOS::Errors() << "Not a worker thread" << std::endl;
        
        return nil;
    }

    if (self == [super init]) {
        m_pWindow       = nil;
        m_pOGLView      = nil;
        m_pRequester    = 0;
        
        if (style & NordicArts::NordicOS::Style::FullScreen) {
            [self setupFullScreenViewWithMode:mode];
        } else {
            [self setupWindowWithMode:mode andStyle:style];
        }

        [m_pOGLView finishInit];
    }

    return self;
}

-(void)setupFullScreenWithMode:(const NordicArts::NordicOS::VideoMode&)mode {
    NordicArts::NordicOS::VideoMode desktop = NordicArts::NordicOS::VideoMode::getDesktopMode();

    NSRect windowRect = NSMakeRect(0, 0, desktop.getWidth(), desktop.getHeight());
    m_pWindow = [[NAWindow alloc] initWithContentRect::windowRect styleMask:NSBorderlessWindowMask backing:NSBackingStoreBuffered defer:NO];
    if (m_pWindow == nil) {
        NordicArts::NordicOS::Errors() << "Can't create window" << std::endl;
    
        return;
    }

    [m_pWindow setLevel:(NSMainMenuWindowLevel + 1)];
    [m_pWindow setOpaque:YES];
    [m_pWindow setHidesOnDeactivate:YES];
    [m_pWindow setAutodisplay:YES];
    [m_pWindow setReleaseWhenClosed:NO];
    [m_pWindow setDelegate:self];
    [m_pWindow setAcceptsMouseMovedEvents:YES];
    [m_pWndow setIgnoresMouseEvents:NO];

    NSView *pMasterView = [[[NABlackView alloc] initWithFrame:windowRect] autorelease];
    if (pMasterView == nil) {
        NordicArts::NordicOS::Errors() << "Can't create view" << std::endl;

        return;
    }

    CGFloat x = ((desktop.getWidth() - mode.getWidth()) / 2.0);
    CGFloat y = ((desktop.getHeight() - mode.getHeight()) / 2.0);

    NSRect OGLRect = NSMakeRect(x, y, mode.getWidth(), mode.getHeight());

    m_pOGLView = [[NAOpenGLView alloc] initWithFrame:OGLRect fullscreen:YES];
    if (m_pOGLView == nil) {
        NordicArts::NordicOS::Errors() << "Can't create OGL" << std::endl;
    
        return;
    }

    [pMasterView addSubview:m_pOGLView];
    [m_pWindow setContentView:pMasterView];
}
