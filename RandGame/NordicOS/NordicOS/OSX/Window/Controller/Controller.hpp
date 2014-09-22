#ifndef NordicArts_NordicOS_OSX_Window_Controller_H
#define NordicArts_NordicOS_OSX_Window_Controller_H

#include "../../Window/Window/VideoMode/VideoMode.hpp"

#import "./DelegateProtocol.hpp"

namespace NordicArts {
    namespace NordicOS {
        class WindowOS;
    };
};

@class NAOpenGLView;

@interface NAWindowController : NSResponder<WindowDelegateProtocol, NSWindowDelegate> {
    NSWindow                        *m_pWindow;
    NAOpenGLView                    *m_pOGLView;
    NordicArts::NordicOS::WindowOS  *m_pRequester;
}

-(id)initWithWindow:(NSWindow*)window;
-(id)initWithMode:(const NordicArts::NordicOS::VideoMode &)mode andStyle:(unsigned long)style;

@end

#endif
