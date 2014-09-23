#include "../../Window/WindowOS/WindowOS.hpp"

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
    BOOL bRightShiftWasDown;
    BOOL bLeftShiftWasDown;
    BOOL bRightCommandWasDown;
    BOOL bLeftCommandWasDown;
    BOOL bRightAlternateWasDown;
    BOOL bLeftAlternateWasDown;
    BOOL bRightControlWasDown;
    BOOL bLeftControlWasDown;
};

static ModifiersState sState;

static BOOL bIsStateInitalized = NO;

BOOL isKeyMaskActive(NSUInteger modifiers, NSUInteger mask);

void processOneModifier(NSUInteger modifiers, NSUInteger mask, BOOL &wasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &requester);
void processLeftRightModifiers(NSUInteger modifiers, NSUInteger leftMask, NSUInteger rightMask, BOOL &leftWasDown, BOOL &rightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &requester);

void initaliseKeyboardHelper(void) {
    if (bIsStateInitalized) {
        return;
    }

    NSUInteger modifiers = [[NSApp currentEvent] modifierFlags];

    sState.bRightShiftWasDown         = isKeyMaskActive(modifiers, NSRightShiftKeyMask);
    sState.bLeftShiftWasDown          = isKeyMaskActive(modifiers, NSLeftShiftKeyMask);
    sState.bRightCommandWasDown       = isKeyMaskActive(modifiers, NSRightCommandKeyMask);
    sState.bLeftCommandWasDown        = isKeyMaskActive(modifiers, NSLeftCommandKeyMask);
    sState.bRightAlternateWasDown     = isKeyMaskActive(modifiers, NSRightAlternateKeyMask);
    sState.bLeftAlternateWasDown      = isKeyMaskActive(modifiers, NSLeftAlternateKeyMask);
    sState.bRightControlWasDown       = isKeyMaskActive(modifiers, NSRightControlKeyMask);
    sState.bLeftControlWasDown        = isKeyMaskActive(modifiers, NSLeftControlKeyMask);

    bIsStateInitalized = YES;
}

NordicArts::NordicOS::Event::KeyEvent keyEventWithModifiers(NSUInteger modifiers, NordicArts::NordicOS::Keyboard::Key key) {
    NordicArts::NordicOS::Event::KeyEvent event;

    event.code      = key;
    event.bAlt       = (modifiers & NSAlternateKeyMask);
    event.bControl   = (modifiers & NSControlKeyMask);
    event.bShift     = (modifiers & NSShiftKeyMask);
    event.bSystem    = (modifiers & NSCommandKeyMask);

    return event;
}

void handleModifiersChanged(NSUInteger modifiers, NordicArts::NordicOS::WindowOS &requester) {
    processLeftRightModifiers(modifiers, NSLeftShiftKeyMask, NSRightShiftKeyMask, sState.bLeftShiftWasDown, sState.bRightShiftWasDown, NordicArts::NordicOS::Keyboard::LShift, NordicArts::NordicOS::Keyboard::RShift, requester);
    processLeftRightModifiers(modifiers, NSLeftCommandKeyMask, NSRightCommandKeyMask, sState.bLeftCommandWasDown, sState.bRightCommandWasDown, NordicArts::NordicOS::Keyboard::LSystem, NordicArts::NordicOS::Keyboard::RSystem, requester);
    processLeftRightModifiers(modifiers, NSLeftAlternateKeyMask, NSRightAlternateKeyMask, sState.bLeftAlternateWasDown, sState.bRightAlternateWasDown, NordicArts::NordicOS::Keyboard::LAlt, NordicArts::NordicOS::Keyboard::RAlt, requester);
    processLeftRightModifiers(modifiers, NSLeftControlKeyMask, NSRightControlKeyMask, sState.bLeftControlWasDown, sState.bRightControlWasDown, NordicArts::NordicOS::Keyboard::LControl, NordicArts::NordicOS::Keyboard::RControl, requester);
}

BOOL isKeyMaskActive(NSUInteger modifiers, NSUInteger mask) {
    return ((modifiers & mask) == mask);
}

void processOneModifier(NSUInteger modifiers, NSUInteger mask, BOOL &bWasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &requester) {
    NordicArts::NordicOS::Event::KeyEvent event = keyEventWithModifiers(modifiers, key);
    
    BOOL bIsDown = isKeyMaskActive(modifiers, mask);
    if (bIsDown && !bWasDown) {
        requester.keyDown(event);
    } else if (!bIsDown && bWasDown) {
        requester.keyUp(event);
    }

    bWasDown = bIsDown;
}

void processLeftRightModifiers(NSUInteger modifiers, NSUInteger leftMask, NSUInteger rightMask, BOOL &leftWasDown, BOOL &rightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &requester) {
    processOneModifier(modifiers, leftMask, leftWasDown, leftKey, requester);
    processOneModifier(modifiers, rightMask, rightWasDown, rightKey, requester);
}
