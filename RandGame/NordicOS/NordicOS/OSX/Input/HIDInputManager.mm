#include "./HIDInputManager.hpp"
#include "../../ExceptionHandler/Errors.hpp"
#include <AppKit/AppKit.h>

namespace NordicArts {
    namespace NordicOS {
        HIDInputManager &HIDInputManager::getInstance() {
            static HIDInputManager instance;
            
            return instance;
        }

        bool HIDInputManager::isKeyPressed(Keyboard::Key key) {
            return isPressed(m_keys[key]);
        }
        
        bool HIDInputManager::isMouseButtonPressed(Mouse::Button button) {
            return isPressed(m_buttons[button]);
        }

        long HIDInputManager::getLocationID(IOHIDDeviceRef device) {
            long lLoc = 0;
    
            CFTypeRef typeRef = IOHIDDeviceGetProperty(device, CFSTR(kIOHIDLocationIDKey));
            if (!typeRef || (CFGetTypeID(typeRef) != CFNumberGetTypeID())) {
                return 0;
            }

            CFNumberRef locRef = (CFNumberRef)typeRef;
            if (!CFNumberGetValue(locRef, kCFNumberLongType, &lLoc)) {
                return 0;
            }

            return lLoc;
        }

        CFDictionaryRef HIDInputManager::copyDevicesMask(UINT32 iPage, UINT32 iUsage) {
            CFMutableDictionaryRef dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
            
            CFNumberRef value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iPage);
            CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsagePageKey), value);
            CFRelease(value);

            value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUsage);
            CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsageKey), value);
            CFRelease(value);

            return dict;
        }

        HIDInputManager::HIDInputManager() : m_bIsValid(true), m_layoutData(0), m_layout(0), m_manager(0) {
            TISInputSourceRef tis = TISCopyCurrentKeyboardLayoutInputSource();
            m_layoutData = (CFDataRef)TISGetInputSourceProperty(tis, kTISPropertyUnicodeKeyLayoutData);
            if (m_layoutData == 0) {
                Errors() << "Can't get keyboard layout" << std::endl;
                
                freeUp();
                
                return;
            }

            CFRetain(m_layoutData);
            m_layout = (UCKeyboardLayout *)CFDataGetBytePtr(m_layoutData);
            CFRelease(tis);

            m_manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
            
            IOReturn openStatus = IOHIDManagerOpen(m_manager, kIOHIDOptionsTypeNone);
            if (openStatus != kIOReturnSuccess) {
                    Errors() << "Can't get HID manager" << std::endl;
            
                    freeUp();
        
                    return;
            }

            initalizeKeyboard();
            if (!m_bIsValid) {
                return;
            }

            initalizeMouse();
            if (!m_bIsValid) {
                return;
            }
        }

        HIDInputManager::~HIDInputManager() {
            freeUp();
        }

        void HIDInputManager::initalizeKeyboard() {
            CFSetRef keyboards = copyDevices(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
            if (keyboards == NULL) {
                freeUp();
                
                return;
            }

            CFIndex keyboardCount = CFSetGetCount(keyboards);

            CFTypeRef devicesArray[keyboardCount];
            CFSetGetValues(keyboards, devicesArray);

            for (CFIndex i = 0; i < keyboardCount; ++i) {
                IOHIDDeviceRef keyboard = (IOHIDDeviceRef)devicesArray[i];
                loadKeyboard(keyboard);
            }
        
            CFRelease(keyboards);
        }

        void HIDInputManager::initalizeMouse() {
            CFSetRef mice = copyDevices(kHIDPage_GenericDesktop, kHIDUsage_GD_Mouse);
            if (mice == NULL) {
                freeUp();

                return;
            }

            CFIndex mouseCount = CFSetGetCount(mice);

            CFTypeRef devicesArray[mouseCount];
            CFSetGetValues(mice, devicesArray);
    
            for (CFIndex i = 0; i < mouseCount; ++i) {
                IOHIDDeviceRef mouse = (IOHIDDeviceRef)devicesArray[i];
                loadMouse(mouse);
            }

            CFRelease(mice);
        }

        void HIDInputManager::loadKeyboard(IOHIDDeviceRef keyboard) {
            CFArrayRef keys = IOHIDDeviceCopyMatchingElements(keyboard, NULL, kIOHIDOptionsTypeNone);
            if (keys == NULL) {
                Errors() << "Keyboard has no keys" << std::endl;

                return;
            }

            CFIndex keyCount = CFArrayGetCount(keys);
            if (keyCount == 0) {
                Errors() << "Keyboard without keys" << std::endl;

                return;
            }

            for (CFIndex i = 0; i < keyCount; ++i) {
                IOHIDElementRef aKey = (IOHIDElementRef)CFArrayGetValueAtIndex(keys, i);

                if (IOHIDElementGetUsagePage(aKey) != kHIDPage_KeyboardOrKeypad) {
                    continue;
                }

                loadKey(aKey);
            }

            CFRelease(keys);
        }

        void HIDInputManager::loadMouse(IOHIDDeviceRef mouse) {
            CFArrayRef buttons = IOHIDDeviceCopyMatchingElements(mouse, NULL, kIOHIDOptionsTypeNone);
            if (buttons == NULL) {
                NordicArts::NordicOS::Errors() << "Mouse has no buttons" << std::endl;

                return;
            }

            CFIndex buttonCount = CFArrayGetCount(buttons);
            if (buttonCount == 0) {
                NordicArts::NordicOS::Errors() << "Mouse without buttons" << std::endl;

                return;
            }

            for (CFIndex i = 0; i < buttonCount; ++i) {
                IOHIDElementRef aButton = (IOHIDElementRef)CFArrayGetValueAtIndex(buttons, i);
                if (IOHIDElementGetUsage(aButton) != kHIDPage_Button) {
                    continue;
                }

                loadButton(aButton);
            }

            CFRelease(buttons);
        }

        void HIDInputManager::loadKey(IOHIDElementRef key) {
            UINT32 usageCode    = IOHIDElementGetUsage(key);            
            UINT32 virtualCode  = usageToVirtualCode(usageCode);

            if (virtualCode == 0xff) {
                return;
            }

            UINT32 deadKeyState = 0;
    
            UniCharCount maxStringLength    = 4;
            UniCharCount actualStringLength = 0;
            UniChar      unicodeString[maxStringLength];

            OSStatus    error;
            error = UCKeyTranslate(m_layout, virtualCode, kUCKeyActionDown, 0x100, LMGetKbdType(), kUCKeyTranslateNoDeadKeysBit, &deadKeyState, maxStringLength, &actualStringLength, unicodeString);
            if (error == noErr) {
                Keyboard::Key code = Keyboard::Unknown;

                if (actualStringLength > 0) {
                    code = localizedKeys(unicodeString[0]);
                }

                if (code != Keyboard::Unknown) {
                    m_keys[code].push_back(key);
                
                    CFRetain(m_keys[code].back());
                }
            } else {
                NordicArts::NordicOS::Errors() << "Cant translate virtual key, " << error << std::endl;
            }
        }

        void HIDInputManager::loadButton(IOHIDElementRef button) {
            UINT32 usage = IOHIDElementGetUsage(button);

            Mouse::Button dest = Mouse::ButtonCount;

            #define kHIDUsage_Button_5 0x05

            switch (usage) {
                case kHIDUsage_Button_1: {
                    dest = Mouse::Left;
                    break;
                }
                case kHIDUsage_Button_2: {
                    dest = Mouse::Right;
                    break;
                }
                case kHIDUsage_Button_3: {
                    dest = Mouse::Middle;
                    break;
                }
                case kHIDUsage_Button_4: {
                    dest = Mouse::XButton1;
                    break;
                }
                case kHIDUsage_Button_5: {
                    dest = Mouse::XButton2;
                    break;
                }
                default: {
                    dest = Mouse::ButtonCount;
                    break;
                }
            }

            if (dest != Mouse::ButtonCount) {
                m_buttons[dest].push_back(button);
            
                CFRetain(m_buttons[dest].back());
            }
        }

        void HIDInputManager::freeUp() {
            m_bIsValid = false;

            if (m_layoutData != 0) {
                CFRelease(m_layoutData);
            }

            if (m_manager != 0) {
                CFRelease(m_manager);
            }

            for (unsigned int i = 0; i < Keyboard::KeyCount; ++i) {
                for (IOHIDElements::iterator it = m_keys[i].begin(); it != m_keys[i].end(); ++it) {
                    CFRelease(*it);
                }
    
                m_keys[i].clear();
            }

            for (unsigned int i = 0; i < Mouse::ButtonCount; ++i) {
                for (IOHIDElements::iterator it = m_buttons[i].begin(); it != m_buttons[i].end(); ++it) {
                    CFRelease(*it);
                }

                m_buttons[i].clear();
            }
        }

        CFSetRef HIDInputManager::copyDevices(UINT32 iPage, UINT32 iUsage) {
            CFDictionaryRef mask = copyDevicesMask(iPage, iUsage);

            IOHIDManagerSetDeviceMatching(m_manager, mask);

            CFRelease(mask);
            mask = 0;

            CFSetRef devices = IOHIDManagerCopyDevices(m_manager);
            if (devices == NULL) {
                return NULL;
            }

            CFIndex deviceCount = CFSetGetCount(devices);
            if (deviceCount < 1) {
                CFRelease(devices);
            
                return NULL;
            }

            return devices;
        }

        bool HIDInputManager::isPressed(IOHIDElements &elements) {
            if (!m_bIsValid) {
                NordicArts::NordicOS::Errors() << "InputManager invalid" << std::endl;

                return false;
            }

            bool bState = false;
        
            for (IOHIDElements::iterator it = elements.begin(); it != elements.end(); ) {
                IOHIDValueRef value = 0;

                IOHIDDeviceRef device = IOHIDElementGetDevice(*it);
                IOHIDDeviceGetValue(device, *it, &value);

                if (!value) {
                    CFRelease(*it);
                    it = elements.erase(it);
                } else if (IOHIDValueGetIntegerValue(value) == 1) {
                    bState = true;
                    
                    break;
                } else {
                    ++it;
                }
            }

            return bState;
        }

        UINT8 HIDInputManager::usageToVirtualCode(UINT32 iUsage) {
            switch (iUsage) {
                case kHIDUsage_KeyboardErrorRollOver:
                case kHIDUsage_KeyboardPOSTFail:
                case kHIDUsage_KeyboardErrorUndefined: {
                    return 0xff;
                }

                // Letterss
                case kHIDUsage_KeyboardA: return 0x00;
                case kHIDUsage_KeyboardB: return 0x0b;
                case kHIDUsage_KeyboardC: return 0x08;
                case kHIDUsage_KeyboardD: return 0x02;
                case kHIDUsage_KeyboardE: return 0x0e;
                case kHIDUsage_KeyboardF: return 0x03;
                case kHIDUsage_KeyboardG: return 0x05;
                case kHIDUsage_KeyboardH: return 0x04;
                case kHIDUsage_KeyboardI: return 0x22;
                case kHIDUsage_KeyboardJ: return 0x26;
                case kHIDUsage_KeyboardK: return 0x28;
                case kHIDUsage_KeyboardL: return 0x25;
                case kHIDUsage_KeyboardM: return 0x2e;
                case kHIDUsage_KeyboardN: return 0x2d;
                case kHIDUsage_KeyboardO: return 0x1f;
                case kHIDUsage_KeyboardP: return 0x23;
                case kHIDUsage_KeyboardQ: return 0x0c;
                case kHIDUsage_KeyboardR: return 0x0f;
                case kHIDUsage_KeyboardS: return 0x01;
                case kHIDUsage_KeyboardT: return 0x11;
                case kHIDUsage_KeyboardU: return 0x20;
                case kHIDUsage_KeyboardV: return 0x09;
                case kHIDUsage_KeyboardW: return 0x0d;
                case kHIDUsage_KeyboardX: return 0x07;
                case kHIDUsage_KeyboardY: return 0x10;
                case kHIDUsage_KeyboardZ: return 0x06;

                // Numbers
                case kHIDUsage_Keyboard1: return 0x12;
                case kHIDUsage_Keyboard2: return 0x13;
                case kHIDUsage_Keyboard3: return 0x14;
                case kHIDUsage_Keyboard4: return 0x15;
                case kHIDUsage_Keyboard5: return 0x17;
                case kHIDUsage_Keyboard6: return 0x16;
                case kHIDUsage_Keyboard7: return 0x1a;
                case kHIDUsage_Keyboard8: return 0x1c;
                case kHIDUsage_Keyboard9: return 0x19;
                case kHIDUsage_Keyboard0: return 0x1d;

                // Specials
                case kHIDUsage_KeyboardReturnOrEnter:       return 0x24;
                case kHIDUsage_KeyboardEscape:              return 0x35;
                case kHIDUsage_KeyboardDeleteOrBackspace:   return 0x33;
                case kHIDUsage_KeyboardTab:                 return 0x30;
                case kHIDUsage_KeyboardSpacebar:            return 0x31;
                case kHIDUsage_KeyboardHyphen:              return 0x1b;
                case kHIDUsage_KeyboardEqualSign:           return 0x18;
                case kHIDUsage_KeyboardOpenBracket:         return 0x21;
                case kHIDUsage_KeyboardCloseBracket:        return 0x1e;
                case kHIDUsage_KeyboardBackslash:           return 0x2a;
                case kHIDUsage_KeyboardNonUSPound:          return 0xff;
                case kHIDUsage_KeyboardSemicolon:           return 0x29;
                case kHIDUsage_KeyboardQuote:               return 0x27;
                case kHIDUsage_KeyboardGraveAccentAndTilde: return 0x32;
                case kHIDUsage_KeyboardComma:               return 0x2b;
                case kHIDUsage_KeyboardPeriod:              return 0x2F;
                case kHIDUsage_KeyboardSlash:               return 0x2c;
                case kHIDUsage_KeyboardCapsLock:            return 0x39;

                // F keys
                case kHIDUsage_KeyboardF1:  return 0x7a;
                case kHIDUsage_KeyboardF2:  return 0x78;
                case kHIDUsage_KeyboardF3:  return 0x63;
                case kHIDUsage_KeyboardF4:  return 0x76;
                case kHIDUsage_KeyboardF5:  return 0x60;
                case kHIDUsage_KeyboardF6:  return 0x61;
                case kHIDUsage_KeyboardF7:  return 0x62;
                case kHIDUsage_KeyboardF8:  return 0x64;
                case kHIDUsage_KeyboardF9:  return 0x65;
                case kHIDUsage_KeyboardF10: return 0x6d;
                case kHIDUsage_KeyboardF11: return 0x67;
                case kHIDUsage_KeyboardF12: return 0x6f;
                case kHIDUsage_KeyboardF13: return 0x69;
                case kHIDUsage_KeyboardF14: return 0x6b;
                case kHIDUsage_KeyboardF15: return 0x71;
                case kHIDUsage_KeyboardF16:
                case kHIDUsage_KeyboardF17:
                case kHIDUsage_KeyboardF18:
                case kHIDUsage_KeyboardF19:
                case kHIDUsage_KeyboardF20:
                case kHIDUsage_KeyboardF21:
                case kHIDUsage_KeyboardF22:
                case kHIDUsage_KeyboardF23:
                case kHIDUsage_KeyboardF24: {
                    return 0xff;
                }

                // System Keys
                case kHIDUsage_KeyboardPrintScreen:     return 0xff;
                case kHIDUsage_KeyboardScrollLock:      return 0xff;
                case kHIDUsage_KeyboardPause:           return 0xff;
                case kHIDUsage_KeyboardInsert:          return 0x72;
                case kHIDUsage_KeyboardHome:            return 0x73;
                case kHIDUsage_KeyboardPageUp:          return 0x74;
                case kHIDUsage_KeyboardDeleteForward:   return 0x75;
                case kHIDUsage_KeyboardEnd:             return 0x77;
                case kHIDUsage_KeyboardPageDown:        return 0x79;

                // Arrow Keys
                case kHIDUsage_KeyboardRightArrow:      return 0x7c;
                case kHIDUsage_KeyboardLeftArrow:       return 0x7b;
                case kHIDUsage_KeyboardDownArrow:       return 0x7d;
                case kHIDUsage_KeyboardUpArrow:         return 0x7e;

                // NumPad
                case kHIDUsage_KeypadNumLock:           return 0x47;
                case kHIDUsage_KeypadSlash:             return 0x4b;
                case kHIDUsage_KeypadAsterisk:          return 0x43;
                case kHIDUsage_KeypadHyphen:            return 0x4e;
                case kHIDUsage_KeypadPlus:              return 0x45;
                case kHIDUsage_KeypadEnter:             return 0x4c;
                case kHIDUsage_Keypad1:                 return 0x53;
                case kHIDUsage_Keypad2:                 return 0x54;
                case kHIDUsage_Keypad3:                 return 0x55;
                case kHIDUsage_Keypad4:                 return 0x56;
                case kHIDUsage_Keypad5:                 return 0x57;
                case kHIDUsage_Keypad6:                 return 0x58;
                case kHIDUsage_Keypad7:                 return 0x59;
                case kHIDUsage_Keypad8:                 return 0x5b;
                case kHIDUsage_Keypad9:                 return 0x5c;
                case kHIDUsage_Keypad0:                 return 0x52;
                case kHIDUsage_KeypadPeriod:            return 0x41;
                case kHIDUsage_KeypadEqualSign:         return 0x51;
                case kHIDUsage_KeypadComma:             return 0xff;
                case kHIDUsage_KeypadEqualSignAS400:    return 0xff;

                // Extra Keys
                case kHIDUsage_KeyboardApplication:     return 0x6e;
                case kHIDUsage_KeyboardMenu:            return 0x7F;
                case kHIDUsage_KeyboardSelect:          return 0x4c;
                case kHIDUsage_KeyboardNonUSBackslash:  return 0xff;
                case kHIDUsage_KeyboardPower:
                case kHIDUsage_KeyboardExecute:
                case kHIDUsage_KeyboardStop:
                case kHIDUsage_KeyboardAgain:
                case kHIDUsage_KeyboardUndo:
                case kHIDUsage_KeyboardCut:
                case kHIDUsage_KeyboardCopy:
                case kHIDUsage_KeyboardPaste:
                case kHIDUsage_KeyboardFind:
                case kHIDUsage_KeyboardInternational1:
                case kHIDUsage_KeyboardInternational2:
                case kHIDUsage_KeyboardInternational3:
                case kHIDUsage_KeyboardInternational4:
                case kHIDUsage_KeyboardInternational5:
                case kHIDUsage_KeyboardInternational6:
                case kHIDUsage_KeyboardInternational7:
                case kHIDUsage_KeyboardInternational8:
                case kHIDUsage_KeyboardInternational9:
                case kHIDUsage_KeyboardLANG1:
                case kHIDUsage_KeyboardLANG2:
                case kHIDUsage_KeyboardLANG3:
                case kHIDUsage_KeyboardLANG4:
                case kHIDUsage_KeyboardLANG5:
                case kHIDUsage_KeyboardLANG6:
                case kHIDUsage_KeyboardLANG7:
                case kHIDUsage_KeyboardLANG8:
                case kHIDUsage_KeyboardLANG9:
                case kHIDUsage_KeyboardAlternateErase:
                case kHIDUsage_KeyboardSysReqOrAttention:
                case kHIDUsage_KeyboardCancel:
                case kHIDUsage_KeyboardClear:
                case kHIDUsage_KeyboardPrior:
                case kHIDUsage_KeyboardReturn:
                case kHIDUsage_KeyboardSeparator:
                case kHIDUsage_KeyboardOut:
                case kHIDUsage_KeyboardOper:
                case kHIDUsage_KeyboardClearOrAgain:
                case kHIDUsage_KeyboardCrSelOrProps:
                case kHIDUsage_KeyboardExSel:
                case kHIDUsage_KeyboardHelp: {
                    return 0xff;
                }

                // Volume
                case kHIDUsage_KeyboardMute:        return 0xff;
                case kHIDUsage_KeyboardVolumeUp:    return 0xff;
                case kHIDUsage_KeyboardVolumeDown:  return 0xff;

                // Locking
                case kHIDUsage_KeyboardLockingCapsLock:     return 0xff;
                case kHIDUsage_KeyboardLockingNumLock:      return 0xff;
                case kHIDUsage_KeyboardLockingScrollLock:   return 0xff;

                // CTRL
                case kHIDUsage_KeyboardLeftControl:     return 0x3b;
                case kHIDUsage_KeyboardLeftShift:       return 0x38;
                case kHIDUsage_KeyboardLeftAlt:         return 0x3a;
                case kHIDUsage_KeyboardLeftGUI:         return 0x37;
                case kHIDUsage_KeyboardRightControl:    return 0x3e;
                case kHIDUsage_KeyboardRightShift:      return 0x3c;
                case kHIDUsage_KeyboardRightAlt:        return 0x3d;
                case kHIDUsage_KeyboardRightGUI:        return 0x36;

                // Reserved
                case kHIDUsage_Keyboard_Reserved:
                default: {
                    return 0xff;
                }
            }
        }

        Keyboard::Key HIDInputManager::localizedKeys(UniChar ch) {
            switch (ch) {
                case 'a':
                case 'A': {
                    return NordicArts::NordicOS::Keyboard::A;
                }

                case 'b':
                case 'B': {
                    return NordicArts::NordicOS::Keyboard::B;
                }

                case 'c':
                case 'C': {
                    return NordicArts::NordicOS::Keyboard::C;
                }

                case 'd':
                case 'D': {
                    return NordicArts::NordicOS::Keyboard::D;
                }

                case 'e':
                case 'E': {
                    return NordicArts::NordicOS::Keyboard::E;
                }

                case 'f':
                case 'F': {
                    return NordicArts::NordicOS::Keyboard::F;
                }

                case 'g':
                case 'G': {
                    return NordicArts::NordicOS::Keyboard::G;
                }

                case 'h':
                case 'H': {
                    return NordicArts::NordicOS::Keyboard::H;
                }

                case 'i':
                case 'I': {
                    return NordicArts::NordicOS::Keyboard::I;
                }

                case 'j':
                case 'J': {
                    return NordicArts::NordicOS::Keyboard::J;
                }

                case 'k':
                case 'K': {
                    return NordicArts::NordicOS::Keyboard::K;
                }

                case 'l':
                case 'L': {
                    return NordicArts::NordicOS::Keyboard::L;
                }

                case 'm':
                case 'M': {
                    return NordicArts::NordicOS::Keyboard::M;
                }

                case 'n':
                case 'N': {
                    return NordicArts::NordicOS::Keyboard::N;
                }

                case 'o':
                case 'O': {
                    return NordicArts::NordicOS::Keyboard::O;
                }

                case 'p':
                case 'P': {
                    return NordicArts::NordicOS::Keyboard::P;
                }

                case 'q':
                case 'Q': {
                    return NordicArts::NordicOS::Keyboard::Q;
                }

                case 'r':
                case 'R': {
                    return NordicArts::NordicOS::Keyboard::R;
                }

                case 's':
                case 'S': {
                    return NordicArts::NordicOS::Keyboard::S;
                }

                case 't':
                case 'T': {
                    return NordicArts::NordicOS::Keyboard::T;
                }

                case 'u':
                case 'U': {
                    return NordicArts::NordicOS::Keyboard::U;
                }

                case 'v':
                case 'V': {
                    return NordicArts::NordicOS::Keyboard::V;
                }

                case 'w':
                case 'W': {
                    return NordicArts::NordicOS::Keyboard::W;
                }

                case 'x':
                case 'X': {
                    return NordicArts::NordicOS::Keyboard::X;
                }

                case 'y':
                case 'Y': {
                    return NordicArts::NordicOS::Keyboard::Y;
                }

                case 'z':
                case 'Z': {
                    return NordicArts::NordicOS::Keyboard::Z;
                }

                default: return NordicArts::NordicOS::Keyboard::Unknown;
            }
        }

        Keyboard::Key HIDInputManager::nonLocalizedKeys(UniChar virtualKeyCode) {
            switch (virtualKeyCode) {
                // Letters
                case 0x00: return NordicArts::NordicOS::Keyboard::A;
                case 0x0b: return NordicArts::NordicOS::Keyboard::B;
                case 0x08: return NordicArts::NordicOS::Keyboard::C;
                case 0x02: return NordicArts::NordicOS::Keyboard::D;
                case 0x0e: return NordicArts::NordicOS::Keyboard::E;
                case 0x03: return NordicArts::NordicOS::Keyboard::F;
                case 0x05: return NordicArts::NordicOS::Keyboard::G;
                case 0x04: return NordicArts::NordicOS::Keyboard::H;
                case 0x22: return NordicArts::NordicOS::Keyboard::I;
                case 0x26: return NordicArts::NordicOS::Keyboard::J;
                case 0x28: return NordicArts::NordicOS::Keyboard::K;
                case 0x25: return NordicArts::NordicOS::Keyboard::L;
                case 0x2e: return NordicArts::NordicOS::Keyboard::M;
                case 0x2d: return NordicArts::NordicOS::Keyboard::N;
                case 0x1f: return NordicArts::NordicOS::Keyboard::O;
                case 0x23: return NordicArts::NordicOS::Keyboard::P;
                case 0x0c: return NordicArts::NordicOS::Keyboard::Q;
                case 0x0f: return NordicArts::NordicOS::Keyboard::R;
                case 0x01: return NordicArts::NordicOS::Keyboard::S;
                case 0x11: return NordicArts::NordicOS::Keyboard::T;
                case 0x20: return NordicArts::NordicOS::Keyboard::U;
                case 0x09: return NordicArts::NordicOS::Keyboard::V;
                case 0x0d: return NordicArts::NordicOS::Keyboard::W;
                case 0x07: return NordicArts::NordicOS::Keyboard::X;
                case 0x10: return NordicArts::NordicOS::Keyboard::Y;
                case 0x06: return NordicArts::NordicOS::Keyboard::Z;

                // Numbers
                case 0x1d: return NordicArts::NordicOS::Keyboard::Num0;
                case 0x12: return NordicArts::NordicOS::Keyboard::Num1;
                case 0x13: return NordicArts::NordicOS::Keyboard::Num2;
                case 0x14: return NordicArts::NordicOS::Keyboard::Num3;
                case 0x15: return NordicArts::NordicOS::Keyboard::Num4;
                case 0x17: return NordicArts::NordicOS::Keyboard::Num5;
                case 0x16: return NordicArts::NordicOS::Keyboard::Num6;
                case 0x1a: return NordicArts::NordicOS::Keyboard::Num7;
                case 0x1c: return NordicArts::NordicOS::Keyboard::Num8;
                case 0x19: return NordicArts::NordicOS::Keyboard::Num9;

                // Controls
                case 0x35: return NordicArts::NordicOS::Keyboard::Escape;
                case 0x3b: return NordicArts::NordicOS::Keyboard::LControl;
                case 0x38: return NordicArts::NordicOS::Keyboard::LShift;
                case 0x3a: return NordicArts::NordicOS::Keyboard::LAlt;
                case 0x37: return NordicArts::NordicOS::Keyboard::LSystem;
                case 0x3e: return NordicArts::NordicOS::Keyboard::RControl;
                case 0x3c: return NordicArts::NordicOS::Keyboard::RShift;
                case 0x3d: return NordicArts::NordicOS::Keyboard::RAlt;
                case 0x36: return NordicArts::NordicOS::Keyboard::RSystem;
                
                case 0x7f:
                case NSMenuFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Menu;
                }

                // Syntax
                case 0x21: return NordicArts::NordicOS::Keyboard::LBracket;
                case 0x1e: return NordicArts::NordicOS::Keyboard::RBracket;
                case 0x29: return NordicArts::NordicOS::Keyboard::SemiColon;
                case 0x2b: return NordicArts::NordicOS::Keyboard::Comma;
                case 0x41:
                case 0x2f: {
                    return NordicArts::NordicOS::Keyboard::Period;
                }
                case 0x27: return NordicArts::NordicOS::Keyboard::Quote;
                case 0x2c: return NordicArts::NordicOS::Keyboard::Slash;
                case 0x2a: return NordicArts::NordicOS::Keyboard::BackSlash;
                
                case 0x0a: return NordicArts::NordicOS::Keyboard::Tilde;
                
                // System
                case 0x51:
                case 0x18: {
                    return NordicArts::NordicOS::Keyboard::Equal;
                }
                case 0x32: return NordicArts::NordicOS::Keyboard::Dash;
                case 0x31: return NordicArts::NordicOS::Keyboard::Space;
                case 0x4c:
                case 0x24: {
                    return NordicArts::NordicOS::Keyboard::Return;
                }
                case 0x33: return NordicArts::NordicOS::Keyboard::BackSpace;
                case 0x30: return NordicArts::NordicOS::Keyboard::Tab;
                case 0x74:
                case NSPageUpFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::PageUp;
                }
                case 0x79:
                case NSPageDownFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::PageDown;
                }
                case 0x77:
                case NSEndFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::End;
                }
                case 0x73:
                case NSHomeFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Home;
                }
                case 0x72:
                case NSInsertFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Insert;
                }
                case 0x75:
                case NSDeleteFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Delete;
                }

                // Maths
                case 0x45: return NordicArts::NordicOS::Keyboard::Add;
                case 0x4e: return NordicArts::NordicOS::Keyboard::Subtract;
                case 0x43: return NordicArts::NordicOS::Keyboard::Multiply;
                case 0x4b: return NordicArts::NordicOS::Keyboard::Divide;

                // Arrows
                case 0x7b:
                case NSLeftArrowFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Left;
                }
                case 0x7c:
                case NSRightArrowFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Right;
                }
                case 0x7e:
                case NSUpArrowFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Up;
                }
                case 0x7d:
                case NSDownArrowFunctionKey: {
                    return NordicArts::NordicOS::Keyboard::Down;
                }

                // NumPad
                case 0x52: return NordicArts::NordicOS::Keyboard::NumPad0;
                case 0x53: return NordicArts::NordicOS::Keyboard::NumPad1;
                case 0x54: return NordicArts::NordicOS::Keyboard::NumPad2;
                case 0x55: return NordicArts::NordicOS::Keyboard::NumPad3;
                case 0x56: return NordicArts::NordicOS::Keyboard::NumPad4;
                case 0x57: return NordicArts::NordicOS::Keyboard::NumPad5;
                case 0x58: return NordicArts::NordicOS::Keyboard::NumPad6;
                case 0x59: return NordicArts::NordicOS::Keyboard::NumPad7;
                case 0x5b: return NordicArts::NordicOS::Keyboard::NumPad8;
                case 0x5c: return NordicArts::NordicOS::Keyboard::NumPad9;

                // F Keys
                case 0x7a:
                case NSF1FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F1;
                }
                case 0x78:
                case NSF2FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F2;
                }
                case 0x63:
                case NSF3FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F3;
                }
                case 0x76:
                case NSF4FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F4;
                }
                case 0x60:
                case NSF5FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F5;
                }
                case 0x61:
                case NSF6FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F6;
                }
                case 0x62:
                case NSF7FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F7;
                }
                case 0x64:
                case NSF8FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F8;
                }
                case 0x65:
                case NSF9FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F9;
                }
                case 0x6d:
                case NSF10FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F10;
                }
                case 0x67:
                case NSF11FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F11;
                }
                case 0x6f:
                case NSF12FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F12;
                }
                case 0x69:
                case NSF13FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F13;
                }
                case 0x6b:
                case NSF14FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F14;
                }
                case 0x71:
                case NSF15FunctionKey: {
                    return NordicArts::NordicOS::Keyboard::F15;
                }

                case NSPauseFunctionKey: return NordicArts::NordicOS::Keyboard::Pause;

                default: return NordicArts::NordicOS::Keyboard::Unknown;
            }
        }
    };
};
