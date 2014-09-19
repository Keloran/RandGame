#ifndef NordicArts_NordicOS_OSX_Application_Delegate_H
#define NordicArts_NordicOS_OSX_Application_Delegate_H

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface NAApplicationDelegate : NSObject<NSApplicationDelegate>

-(NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender;

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication;

@end 

#endif
