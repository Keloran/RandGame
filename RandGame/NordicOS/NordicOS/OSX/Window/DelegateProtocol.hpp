#ifndef NordicArts_NordicOS_OSX_DelegateProtocol_H
#define NordicArts_NordicOS_OSX_DelegateProtocol_H

#include "../../OS.hpp"
#include "../../Window/Window/WindowHandle.hpp"

#import <AppKit/AppKit.h>

namespace NordicArts {
	namespace NordicOS {
		class WindowOS;
	};	
};

@protocol WindowDelegateProtocol

-(CGFloat)displayScaleFactor;

-(void)setRequesterTo:(NordicArts::NordicOS::WindowOS*)requester;
-(void)hideMouseCursor;
-(void)showMouseCursor;
-(void)setWindowPositionToX:(int)x Y:(int)y;
-(void)resizeTo:(unsigned int)width by:(unsigned int)height;
-(void)changeTitle:(NSString*)title;
-(void)hideWindow;
-(void)showWindow;
-(void)closeWindow;
-(void)enableKeyRepeat;
-(void)disableKeyRepeat;
-(void)setIconTo:(unsigned int)width by:(unsigned int)height width:(const NordicArts::UINT8*)pixels;
-(void)processEvent;
-(void)applyContext:(NSOpenGLContext*)context;

-(NordicArts::NordicOS::WindowHandle)getSystemHandle;

-(NSPoint)position;

-(NSSize)size;

@end

#endif
