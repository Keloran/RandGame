//
//  SilentResponder.h
//  NordicOS
//
//  Created by Max Hooton on 21/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_OSX_Window_SilentResponder_H
#define NordicArts_NordicOS_OSX_Window_SilentResponder_H

#import <AppKit/AppKit.h>

@interface NASilentResponder : NSResponder

-(void)doCommandBySelector:(SEL)sel;

@end

#endif /* defined(__NordicOS__SilentResponder__) */
