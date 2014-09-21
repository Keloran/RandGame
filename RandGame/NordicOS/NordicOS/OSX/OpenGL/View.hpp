//
//  View.h
//  NordicOS
//
//  Created by Max Hooton on 21/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_OSX_OpenGL_View_H
#define NordicArts_NordicOS_OSX_OpenGL_View_H

#import <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        class WindowOS;
    };
};

@class NASilentResponder;

@interface NAOpenGLView : NSOpenGLView {
    NordicArts::NordicOS::WindowOS  *m_pRequester;
    
    BOOL                             m_bUseKeyRepeat;
    BOOL                             m_bMouseIsIn;
    BOOL                             m_bFullScreen;
    
    NSTrackingArea                  *m_pTrackingArea;
    
    CGFloat                          m_fScaleFactor;
    
    NASilentResponder                *m_pSilentResponder;
    
    NSTextView                       *m_pHiddenTextView;
}

-(id)initWithFrame:(NSRect)frameRect fullScreen:(BOOL)isFullScreen;

-(void)finishInit;
-(void)enableKeyRepeat;
-(void)disableKeyRepeat;
-(void)setRequesterTo:(NordicArts::NordicOS::WindowOS *)requester;

-(NSPoint)computeGlobalPositionOfRelativePoint:(NSPoint)point;
-(NSPoint)cursorPositionFromEvent:(NSEvent *)eventOrNil;

-(CGFloat)displayScaleFactor;

@end

#endif /* defined(__NordicOS__View__) */
