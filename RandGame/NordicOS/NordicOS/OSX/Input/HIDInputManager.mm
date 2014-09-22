#include "./HIDInputManager.hpp"
#include "../../ExceptinHandler/Errors.hpp"
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
            return isMouseButtonPressed(m_buttons[button]);
        }

        long HIDInputManager::getLocationID(IOHIDDevice device) {
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
            
            CFNumberRef value = CFNumberCreate(kCFAlloctorDefault, kCFNumberIntType, &iPage);
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
            
                    freeIp();
        
                    return;
            }

            initaliseKeyboard();
            if (!m_bIsValid) {
                return;
            }

            initaliseMouse();
            if (!m_bIsValid) {
                return;
            }
        }

        void HIDInputManager::~HIDInputManager() {
            freeUp();
        }

        void HIDInputManager::initaliseKeyboard() {
            CFSetRef keyboards = copyDevices(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
            if (keyboards == NULL) {
                freeUp();
                
                return;
            }

            CFIndex keyboardCount = CFSetGetCount(keyboards);

            CFTypeRef devicesArray[keyboardCount];
            CFSetGetValues(keyboards, devicesArray);

            for (CFIndex i = 0; i < keyboardCount; ++i) {
                IOHIDDeviceRef keyboard = (IOHIDDeviceRef)deviceArray[i];
                loadKeyboard(keyboard);
            }
        
            CFRelease(keyboards);
        }

        void HIDInputManager::initaliseMouse() {
            CFSetRef mice = copyDevices(kHIDPage_GenericDesktop, kHIDUsage_GD_Mouse);
            if (mice == NULL) {
                freeUp();

                return;
            }

            CFIndex mouseCount = CFSetGetCount(mice);

            CFTypeRef devicesArray[mouseCount];
            CFSetGetValues(mice, devicesArray);
    
            for (CFIndex i = 0; i < mouseCount; ++i) {
                IOHIDDeviceref mouse = (IOHIDDeviceref)deviceArary[i];
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

                if (IOHIDEElementGetUsagePage(aKey) != kHIDPage_KeyboardOrKeypad) {
                    continue;
                }

                loadKey(aKey);
            }

            CFRelease(keys);
        }

        
        }
    };
};
