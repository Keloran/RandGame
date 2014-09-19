#ifndef NordicArts_NordicOS_OSX_View_H
#define NordicArts_NordicOS_OSX_View_H

#import "../Window/DelegateProtocol.hpp"

@class NAOpenGLView;

@interface NAViewController : NSObject<WindowDelegateProtocol> {
    NSView                          *m_pView;
    NAOpenGLView                    *m_pOGLView;
    NordicArts::NordicOS::WindowOS  *m_pRequester;
}

-(id)initWithView:(NSView*)view;

@end

#endif
