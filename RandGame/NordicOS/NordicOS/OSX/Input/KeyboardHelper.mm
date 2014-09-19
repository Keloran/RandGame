#include "../../Window/Window.hpp"

#import "./KeyBoardModifiersHelper.hpp"

#define NSRightShiftKeyMask     0x020004
#define NSLeftShiftKeyMask      0x020002
#define NSRightCommandKeyMask   0x100010
#define NSLeftCommandKeyMask    0x100008
#define NSRightAlternateKeyMask 0x080040
#define NSLeftAlternateKeyMask  0x080020
#define NSRightControlKeyMask   0x042000
#define NSLeftControlKeyMask    0x040001

struct ModifiersState {
    BOOL rightShiftWasDown,
    BOOL leftShiftWasDown,
    BOOL rightComamndWasDown,
    BOOL leftCommandWasDown,
    BOOL rightAlternateWasDown,
    BOOL leftAlternateWasDown,
    BOOL rightControlWasDown,
    BOOL leftControlWasDown
};

static ModifiersState state;

static BOOL isStateInitalized = NO;

BOOL isKeyMaskActive(NSUInteger modifiers, NSUInteger mask);

void processOneModifier(NSUInteger modifiers, NSUInteger mask, BOOL &wasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &requester);
void processLeftRightModifiers(NSUInteger modifiers, NSUInteger leftMask, NSUInteger rightMask, BOOL &leftWasDown, BOOL &rightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &requester);

void initaliseKeyboardHelper(void) {
    if (isStateInitalized) {
        return;
    }

    NSUInteger modifiers = [[NSApp currentEvent] modifierFlags];

    state.rightShiftWasDown         = isKeyMaskActive(modifiers, NSRightShiftKeyMask);
    state.leftShiftWasDown          = isKeyMaskActive(modifiers, NSLeftShiftKeyMask);
    state.rightCommandWasDown       = isKeyMaskActive(modifiers, NSRightCommandKeyMask);
    state.leftCommandWasDown        = isKeyMaskActive(modifiers, NSLeftCommandKeyMask);
    state.rightAlternateWasDown     = isKeyMaskActive(modifiers, NSRightAlternateKeyMask);
    state.leftAlternateWasDown      = isKeyMaskActive(modifiers, NSLeftAlternateKeyMask);
    state.rightControlWasDown       = isKeyMaskActive(modifiers, NSRightControlKeyMask);
    state.leftControlWasDown        = isKeyMaskActive(modifiers, NSLeftControlKeyMask);

    isStateInitialized = YES;
}

NordicArts::NordicOS::Event::KeyEvent keyEventWithModifiers(NSUInteger modifiers, NordicArts::NordicOS::Keyboard::Key key) {
    NordicArts::NordicOS::Event::KeyEvent event;

    event.code      = key;
    event.alt       = (modifiers & NSAlternateKeyMask);
    event.control   = (modifiers & NSControlKeyMask);
    event.shift     = (modifiers & NSShiftKeyMask);
    event.system    = (modifiers & NSCommandKeyMask);

    return event;
}

void handleModifiersChanged(NSUInteger modifiers, NordicArts::NordicOS::WindowOS &requester) {
    processLeftRightModifiers(modifiers, NSLeftShiftKeyMask, NSRightShiftKeyMask, state.leftShiftWasDown, state.rightShiftWasDown, NordicArts::NordicOS::Keyboard::LShift, NordicArts::NordicOS::Keyboard:RShift, requester);
    processLeftRightModifiers(modifiers, NSLeftCommandKeyMask, NSRightCommandKeyMask, state.leftCommandWasDown, state.rightCommandWasDown, NordicArts::NordicOS::Keyboard::LSystem, NordicArts::NordicOS::Keyboard::RSystem, requester);
    processLeftRightModifiers(modifiers, NSLeftAlternateKeyMask, NSRightAlternateKeyMask, state.leftAlternateWasDown, state.rightAlternateWasDown, NordicArts::NordicOS::Keyboard::LAlt, NordicArts::NordicOS::Keyboard::RAlt, requester);
    processLeftRightModifiers(modifiers, NSLeftControlKeyMask, NSRightControlKeyMask, state.leftControlWasDown, state.rightControlWasDown, NordicArts::NordicOS::Keyboard::LControl, NordicArts::NordicOS::Keyboard::RControl, requester);
}

BOOL isKeyMaskActive(NSUInteger modifiers, NSUInteger mask) {
    return ((modifiers & mask) == mask);
}

void processOneModifier(NSUInteger modifiers, NSUInteger mask, BOOL &wasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &requester) {
    NordicArts::NordicOS::Event::KeyEvent event = keyEventWithModifiers(modifiers, key);
    
    BOOL isDown = isKeyMaskActive(modifiers, mask);
    if (isDown && !wasDown) {
        requester.keyDown(event);
    } else if (!isDown && wasDown) {
        requester.keyUp(event);
    }

    wasDown = isDown;
}

void processLeftRightModifiers(NSUInteger modifiers, NSUInteger leftMask, NSUInteger rightMask, BOOL &leftWasDown, BOOL &rightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &requester) {
    processOneModifier(modifiers, leftMask, leftWasDown, leftKey, requester);
    processOneModifier(modifiers, rightMask, rightWasDown, rightKey, requester);
}
