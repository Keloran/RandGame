#import "./Application.hpp"

@implementation NAApplication

+(void)processEvent {
    [NAApplication sharedApplication];

    NSEvent *pEvent = nil;
    while ((pEvent = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES])) {
        [NSApp sendEvent:pEvent];
    }
}

+(void)setUpMenuBar {
    [NAApplication sharedApplication];

    NSMenu *pMainMenu = [NSApp mainMenu];
    if (pMainMenu != nil) {
        return;
    }
    pMainMenu = [[NSMenu alloc] initWithTitle:@""];
    [NSApp setMainMenu:pMainMenu];

    // Apple Menu
    NSMenuItem  *pAppleItem = [pMainMenu addItemWithTitle:@"" action:nil keyEquivalent:@""];
    NSMenu      *pAppleMenu = [NAApplication newAppleMenu];
    [pAppleItem setSubmenu:pAppleMenu];

    // File Menu
    NSMenuItem  *pFileItem  = [pMainMenu addItemWithTitle:@"" action:nil keyEquivalent:@""];
    NSMenu      *pFileMenu  = [NAApplication newFileMenu];
    [pFileItem setSubmenu:pFileMenu];

    // Window Menu
    NSMenuItem  *pWindowItem = [pMainMenu addItemWithTitle:@"" action:nil keyEquivalent:@""];
    NSMenu      *pWindowMenu = [NAApplication newWindowMenu];
    [pWindowItem setSubmenu:pWindowMenu];
    [NSApp setWindowsMenu:pWindowMenu];
}

+(NSMenu*)newAppleMenu {
    NSString *pAppName = [NAApplication applicationName];
    
    NSMenu *pAppleMenu = [[NSMenu alloc] initWithTitle:@""];

    // About
    [pAppleMenu addItemWithTitle:[@"About " stringByAppendingString:pAppName] action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    [pAppleMenu addItem:[NSMenuItem separatorItem]];

    // Preferences
    [pAppleMenu addItemWithTitle:@"Preferences..." action:nil keyEquivalent:@""];
    [pAppleMenu addItem:[NSMenuItem separatorItem]];

    // Services
    NSMenu      *pServiceMenu = [[NSMenu alloc] initWithTitle:@""];
    NSMenuItem  *pServiceItem = [pAppleMenu addItemWithTitle:@"Services..." action:nil keyEquivalent:@""];
    [pServiceItem setSubmenu:pServiceMenu];
    [NSApp setServicesMenu:pServiceMenu];
    [pAppleMenu addItem:[NSMenuItem separatorItem]];
    
    // Hide
    [pAppleMenu addItemWithTitle:[@"Hode " stringByAppendingString:pAppName] action:@selector(hide:) keyEquivalent:@"h"];
    NSMenuItem *pHideOtherItem = [pAppleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [pHideOtherItem setKeyEquivalentModifierMask:(NSAlternateKeyMask | NSCommandKeyMask)];

    // Show
    [pAppleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    [pAppleMenu addItem:[NSMenuItem separatorItem]];

    // Quit
    [pAppleMenu addItemWithTitle:[@"Quit " stringByAppendingString:pAppName] action:@selector(terminate:) keyEquivalent:@"q"];

    return pAppleMenu;
}

+(NSMenu*)newFileMenu {
    NSMenu *pFileMenu = [[NSMenu alloc] initWithTitle:@"File"];

    // Close Window
    NSMenuItem *pCloseItem = [[NSMenuItem alloc] initWithTitle:@"Close Window" action:@selector(performClose:) keyEquivalent:@"w"];
    [pFileMenu addItem:pCloseItem];

    return pFileMenu;
}

+(NSMenu*)newWindowMenu {
    NSMenu *pWindowMenu = [[NSMenu alloc] initWithTitle:@"Window"];

    // Minimize
    NSMenuItem *pMinimizeItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [pWindowMenu addItem:pMinimizeItem];

    // Zoom
    [pWindowMenu addItemWithTitle:@"Zoom" action:@selector(performZoom:) keyEquivalent:@""];
    [pWindowMenu addItem:[NSMenuItem separatorItem]];

    // Front
    [pWindowMenu addItemWithTitle:@"Bring All to Front" action:@selector(bringAllToFront:) keyEquivalent:@""];

    return pWindowMenu;
}

+(NSString*)applicationName {
    NSString *pAppName = [[[NSBundle mainBundle] localizedInfoDictionary] objectForKey:@"CFBundleDisplayName"];

    if ((pAppName == nil) || ([pAppName length] == 0)) {
        pAppName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"];
    }

    if ((pAppName == nil) || ([pAppName length] == 0)) {
        pAppName = [[NSProcessInfo processInfo] processName];
    }

    return pAppName;
}

-(void)bringAllToFront:(id)sender {
    (void)sender;
    [[NSApp windows] makeObjectsPerformSelector:@selector(orderFrontRegardless)];
}

-(void)sendEvent:(NSEvent*)anEvent {
    id firstResponder = [[anEvent window] firstResponder];
    if (([anEvent type] != NSKeyUp) || (![firstResponder tryToPerform:@selector(naKeyUp:) with:anEvent])) {
        [super sendEvent:anEvent];
    }
}
    
@end