#include "../Window/WindowOS/WindowOS.hpp"

#import "./KeyboardModifiersHelper.hpp"

#define NSRightShiftKeyMask     0x020004
#define NSLeftShiftKeyMask      0x200002
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

BOOL isKeyMaskActive(NSUInteger iModifiers, NSUInteger iMask);

void processOneModifier(NSUInteger iModifiers, NSUInteger iMask, BOOL &bWasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &oRequester);
void processLeftRightModifiers(NSUInteger iModifiers, NSUInteger iLeftMask, NSUInteger iRightMask, BOOL &bLeftWasDown, BOOL &bRightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &oRequester);

void initalizeKeyboardHelper(void) {
    if (bIsStateInitalized) {
        return;
    }

    NSUInteger iModifiers = [[NSApp currentEvent] modifierFlags];

    sState.bLeftShiftWasDown        = isKeyMaskActive(iModifiers, NSLeftShiftKeyMask);
    sState.bRightShiftWasDown       = isKeyMaskActive(iModifiers, NSRightShiftKeyMask);
    sState.bLeftCommandWasDown      = isKeyMaskActive(iModifiers, NSLeftCommandKeyMask);
    sState.bRightCommandWasDown     = isKeyMaskActive(iModifiers, NSRightCommandKeyMask);
    sState.bLeftAlternateWasDown    = isKeyMaskActive(iModifiers, NSLeftAlternateKeyMask);
    sState.bRightAlternateWasDown   = isKeyMaskActive(iModifiers, NSRightAlternateKeyMask);
    sState.bLeftControlWasDown      = isKeyMaskActive(iModifiers, NSLeftControlKeyMask);
    sState.bRightControlWasDown     = isKeyMaskActive(iModifiers, NSRightControlKeyMask);

    bIsStateInitalized = YES;
}

NordicArts::NordicOS::Event::KeyEvent keyEventWithModifiers(NSUInteger iModifiers, NordicArts::NordicOS::Keyboard::Key key) {
    NordicArts::NordicOS::Event::KeyEvent event;
    event.code      = key;
    event.bAlt       = (iModifiers & NSAlternateKeyMask);
    event.bControl   = (iModifiers & NSControlKeyMask);
    event.bShift     = (iModifiers & NSShiftKeyMask);
    event.bSystem    = (iModifiers & NSCommandKeyMask);

    return event;
}

void handleModifiersChanged(NSUInteger iModifiers, NordicArts::NordicOS::WindowOS &oRequester) {
    processLeftRightModifiers(iModifiers, NSLeftShiftKeyMask, NSRightShiftKeyMask, sState.bLeftShiftWasDown, sState.bRightShiftWasDown, NordicArts::NordicOS::Keyboard::LShift, NordicArts::NordicOS::Keyboard::RShift, oRequester);
    processLeftRightModifiers(iModifiers, NSLeftCommandKeyMask, NSRightCommandKeyMask, sState.bLeftCommandWasDown, sState.bRightCommandWasDown, NordicArts::NordicOS::Keyboard::LSystem, NordicArts::NordicOS::Keyboard::RSystem, oRequester);
    processLeftRightModifiers(iModifiers, NSLeftAlternateKeyMask, NSRightAlternateKeyMask, sState.bLeftAlternateWasDown, sState.bRightAlternateWasDown, NordicArts::NordicOS::Keyboard::LAlt, NordicArts::NordicOS::Keyboard::RAlt, oRequester);
    processLeftRightModifiers(iModifiers, NSLeftControlKeyMask, NSRightControlKeyMask, sState.bLeftControlWasDown, sState.bRightControlWasDown, NordicArts::NordicOS::Keyboard::LControl, NordicArts::NordicOS::Keyboard::RControl, oRequester);
}

BOOL isKeyMaskActive(NSUInteger iModifiers, NSUInteger iMask) {
    return ((iModifiers & iMask) == iMask);
}

void processOneModifier(NSUInteger iModifiers, NSUInteger iMask, BOOL &bWasDown, NordicArts::NordicOS::Keyboard::Key key, NordicArts::NordicOS::WindowOS &oRequester) {
    NordicArts::NordicOS::Event::KeyEvent event = keyEventWithModifiers(iModifiers, key);

    BOOL bIsDown = isKeyMaskActive(iModifiers, iMask);
    if (bIsDown && !bWasDown) {
        oRequester.keyDown(event);
    } else if (!bIsDown && bWasDown) {
        oRequester.keyUp(event);
    }

    bWasDown = bIsDown;
}

void processLeftRightModifiers(NSUInteger iModifiers, NSUInteger iLeftMask, NSUInteger iRightMask, BOOL &bLeftWasDown, BOOL &bRightWasDown, NordicArts::NordicOS::Keyboard::Key leftKey, NordicArts::NordicOS::Keyboard::Key rightKey, NordicArts::NordicOS::WindowOS &oRequester) {
    processOneModifier(iModifiers, iLeftMask, bLeftWasDown, leftKey, oRequester);
    processOneModifier(iModifiers, iRightMask, bRightWasDown, rightKey, oRequester);
}
