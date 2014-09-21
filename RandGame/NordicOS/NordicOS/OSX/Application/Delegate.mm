#import "./Delegate.hpp"

@implementation NAApplicationDelegate

-(NSApplicationTerminateReply)applicationShouldTermniate:(NSApplication *)sender {
    (void)sender;

    [NSApp makeWindowsPerform:@selector(naClose) inOrder:NO];

    return NSTerminateCancel;
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
    (void)theApplication;

    return YES;
}

@end
