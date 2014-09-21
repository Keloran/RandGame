#include "../../Window/Window/VideoMode/VideoMode.hpp"
#include "./WindowHandle.hpp"
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

        m_pWindow = window;
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
        
        if (style & NordicArts::NordicOS::FullScreen) {
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
    m_pWindow = [[NAWindow alloc] initWithContentRect:windowRect styleMask:NSBorderlessWindowMask backing:NSBackingStoreBuffered defer:NO];
    if (m_pWindow == nil) {
        NordicArts::NordicOS::Errors() << "Can't create window" << std::endl;
    
        return;
    }

    [m_pWindow setLevel:(NSMainMenuWindowLevel + 1)];
    [m_pWindow setOpaque:YES];
    [m_pWindow setHidesOnDeactivate:YES];
    [m_pWindow setAutodisplay:YES];
    [m_pWindow setReleasedWhenClosed:NO];
    [m_pWindow setDelegate:self];
    [m_pWindow setAcceptsMouseMovedEvents:YES];
    [m_pWindow setIgnoresMouseEvents:NO];

    NSView *pMasterView = [[NABlackView alloc] initWithFrame:windowRect];
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

-(void)setupWindowWithMode:(const NordicArts::NordicOS::VideoMode&)mode andStyle:(unsigned long)style {
    NSRect rect = NSMakeRect(0, 0, mode.getWidth(), mode.getHeight());
    
    unsigned int nsStyle = NSBorderlessWindowMask;
    if (style && NordicArts::NordicOS::TitleBar) {
        nsStyle |= (NSTitledWindowMask | NSMiniaturizableWindowMask);
    }
    if (style && NordicArts::NordicOS::Resize) {
        nsStyle |= NSResizableWindowMask;
    }
    if (style && NordicArts::NordicOS::Close) {
        nsStyle |= NSClosableWindowMask;
    }
    
    m_pWindow = [[NAWindow alloc] initWithContentRect:rect styleMask:nsStyle backing:NSBackingStoreBuffered defer:NO];
    if (m_pWindow == nil) {
        NordicArts::NordicOS::Errors() << "NSWindow failed" << std::endl;
        
        return;
    }
    
    m_pOGLView = [[NAOpenGLView alloc] initWithFrame:[[m_pWindow contentView] frame] fullscreen:NO];
    if (m_pOGLView == nil) {
        NordicArts::NordicOS::Errors() << "OGL failed" << std::endl;
        
        return;
    }
    
    [m_pWindow setContentView:m_pOGLView];
    [m_pWindow setDelegate:self];
    [m_pWindow setIgnoresMouseEvents:NO];
    [m_pWindow center];
    [m_pWindow setAutodisplay:YES];
    [m_pWindow setReleasedWhenClosed:NO];
}

-(CGFloat)displayScaleFactor {
    return [m_pOGLView displayScaleFactor];
}

-(void)setRequesterTo:(NordicArts::NordicOS::WindowOS *)requester {
    [m_pOGLView setRequesterTo:requester];
    
    m_pRequester = requester;
}

-(NordicArts::NordicOS::WindowHandle)getSystemHandle {
    return m_pWindow;
}

-(void)hideMouseCursor {
    [NSCursor hide];
}
-(void)showMouseCursor {
    [NSCursor show];
}

-(NSPoint)position {
    const NSPoint origin                = [m_pOGLView frame].origin;
    const NSSize size                   = [m_pOGLView frame].size;
    const NSPoint topLeftCornerOfView   = [NSMakePoint(origin.x, (origin.y + size.height))];
    const NSPoint positionInView        = [m_pOGLView convertPointToBacking:topLeftCornerOfView];
    const NSPoint positionInWindow      = [m_pOGLView convertPoint:positionInView toView:nil];
    const NSPoint positionInScreen      = [[m_pOGLView window] convertBaseToScreen:positionInWindow];
    const NSPoint positionInNordicOS    = NSMakePoint(positionInScreen.x, (([self screenHeight] - [self titlebarHeight]) - positionInScreen.y));
    
    return positionInNordicOS;
}

-(void)setWindowPositionToX:(int)x Y:(int)y {
    NSPoint point = NSMakePoint(x, y);
    
    point.y = ([self screenHeight] - point.y);
    
    [m_pWindow setFrameTopLeftPoint:point];
}

-(NSSize)size {
    return [m_pOGLView frame].size;
}

-(void)resizeTo:(unsigned int)width by:(unsigned int)height {
    NSUInteger styleMask = [m_pWindow styleMask];
    
    [m_pWindow setStyleMask:styleMask ^ NSResizableWindowMask];
    
    height += [self titlebarHeight];
    
    NSRect screenFrame = [[NSScreen mainScreen] visibleFrame];
    CGFloat maxVisibleHeight = screenFrame.size.height;
    if (height > maxVisibleHeight) {
        height = maxVisibleHeight;
        
        if (m_pRequester != 0) {
            m_pRequester->windowResized(width, (height - [self titlebarHeight]));
        }
    }
    
    NSRect frame = NSMakeRect([m_pWindow frame].origin.x, [m_pWindow frame].origin.y, width, height);
    [m_pWindow setFrame:frame display:YES];
    
    [m_pWindow setStyleMask:styleMask];
}

-(void)changeTitle:(NSString *)title {
    [m_pWindow setTitle:title];
}

-(void)hideWindow {
    [m_pWindow orderOut:nil];
}
-(void)showWindow {
    [m_pWindow makeKeyAndOrderFront:nil];
}
-(void)closeWindow {
    [self applyContext:nil];
    [m_pWindow close];
    [m_pWindow setDelegate:nil];
    [self setRequesterTo:0];
}

-(void)enableKeyRepeat {
    [m_pOGLView enableKeyRepeat];
}
-(void)disableKeyRepeat {
    [m_pOGLView disableKeyRepeat];
}

-(void)setIconTo:(unsigned int)width by:(unsigned int)height width:(id)pixels {
    NSBitmapImageRep *pBitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:0 pixelsWide:width pixelsHigh:height bitsPerSample:8 samplesPerPixel:4 hasAlpha:YES isPlanar:NO colorSpaceName:NSCalibratedRGBColorSpace bytesPerRow:0 bitsPerPixel:0];
    
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            NSUInteger pixel[4] = {
                pixels[0],
                pixels[1],
                pixels[2],
                pixels[3]
            };
            [bitmap setPixel:pixel atX:x y:y];
        }
    }
    
    NSImage *pIcon = [[NSImage alloc] initWithSize:NSMAkeSize(width, height)];
    [pIcon addRepresentation:pBitmap];
    
    [[NAApplication sharedApplication] setApplicationIconImage:pIcon];
    
    [pIcon release];
    [pBitmap release];
}

-(void)processEvent {
    if ([NSThread currentThread] != [NSThread mainThread]) {
        NordicArts::NordicOS::Errors() << "Can't fetch worker thread" << std::endl;
        
        return;
    }
    
    if (m_pRequester != 0) {
        [NAApplication processEvent];
    }
}

-(void)applyContext:(NSOpenGLContext *)context {
    [m_pOGLView setOpenGLContext:context];
    [context setView:m_pOGLView];
}

-(BOOL)windowShouldClose:(id)sender {
    (void)sender;
    
    if (m_pRequester == 0) {
        return YES;
    }
    
    m_pRequester->windowClosed();
    
    return NO;
}

-(float)screenHeight {
    NSDictionary *pDescription = [[m_pWindow screen] deviceDescription];
    NSNumber *pScreenNumber    = [pDescription valueForKey:@"NSScreenNumber"];
    CGDirectDisplayID screenId = (CGDirectDisplayID)[pScreenNumber intValue];
    CGFloat height             = CGDisplayPixelsHigh(screenId);
    
    return height;
}


-(float)titlebarHeight {
    return (NSHeight([m_pWindow frame]) - (NSHeight([[m_pWindow contentView] frame]));
}

@end