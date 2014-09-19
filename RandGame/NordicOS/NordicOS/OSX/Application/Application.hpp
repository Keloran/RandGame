#ifndef NordicArts_NordicOS_OSX_Application_H
#define NordicArts_NordicOS_OSX_Application_H

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface NAApplication : NSApplication

+(void)processEvent;
+(void)setUpMenuBar;

-(void)sendEvent:(NSEvent*)anEvent;

@end

#endif
