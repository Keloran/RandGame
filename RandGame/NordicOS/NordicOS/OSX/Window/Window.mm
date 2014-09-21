//
//  Window.cpp
//  NordicOS
//
//  Created by Max Hooton on 20/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#import "./Window.hpp"

@implementation NAWindow

-(BOOL)acceptsFirstResponder {
    return YES;
}

-(BOOL)canBecomeKeyWindow {
    return YES;
}

-(BOOL)validateMenuItem:(NSMenuItem *)menuItem {
    return ([menuItem action] == @selector(performClose:));
}

-(void)keyDown:(NSEvent *)theEvent {
    (void)theEvent;
}

-(void)performClose:(id)sender {
    BOOL shouldClose = NO;
    
    if ([self delegate] && [[self delegate] respondsToSelector:@selector(windowShouldClose:)]) {
        shouldClose = [[self delegate] windowShouldClose:sender];
    }
    
    if (shouldClose) {
        [self close];
    }
}

@end

@implementation NSWindow(NordicOS)
            
-(id)naClose {
    [self performClose:nil];
    
    return nil;
}

@end