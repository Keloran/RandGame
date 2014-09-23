#ifndef NordicArts_NordicOS_OSX_Keyboard_Modifiers_H
#define NordicArts_NordicOS_OSX_Keyboard_Modifiers_H

#import <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        class WindowOS;
    };
};

void initalizeKeyboardHelper(void);
void handleModifiersChanged(NSUInteger iModifiers, NordicArts::NordicOS::WindowOS &oRequester);

NordicArts::NordicOS::Event::KeyEvent keyEventWithModifiers(NSUInteger iModifiers, NordicArts::NordicOS::Keyboard::Key key);

#endif
