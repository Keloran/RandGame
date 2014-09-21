//
//  Window.h
//  NordicOS
//
//  Created by Max Hooton on 20/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_OSX_Window_H
#define NordicArts_NordicOS_OSX_Window_H

#import <AppKit/AppKit.h>

@interface NAWindow : NSWindow

-(BOOL)acceptsFirstResponder;
-(BOOL)canBecomeKeyWindow;
-(BOOL)validateMenuItem:(NSMenuItem *)menuItem;

-(void)keyDown:(NSEvent *)theEvent;
-(void)performClose:(id)sender;

@end

@interface NSWindow(NordicOS)

-(id)naClose;

@end


#endif /* defined(__NordicOS__Window__) */
