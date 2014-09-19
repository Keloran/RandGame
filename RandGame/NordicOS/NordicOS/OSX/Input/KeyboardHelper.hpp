#ifndef NordicArts_NordicOS_OSX_KeyBoardHelper_H
#define NordicArts_NordicOS_OSX_KeyBoardHelper_H

#import <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        class WindowOS;
    };
};

void initaliseKeyboardHelper(void);
void handleModifiersChanged(NSUInteger modifiers, NordicArts::NordicOS::WindowOS &requester);

NordicArts::NordicOS::Event::KeyEvent keyEventWithModifiers(NSUInteger modifiers, NordicArts::NordicOS::Keyboard::Key key);

#endif
