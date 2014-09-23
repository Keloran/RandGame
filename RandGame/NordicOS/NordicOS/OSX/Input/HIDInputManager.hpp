#ifndef NordicArts_NordicOS_HIDInputManager_H
#define NordicArts_NordicOS_HIDInputManager_H

#include "../../Window/Keyboard/Keyboard.hpp"
#include "../../Window/Mouse/Mouse.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include "../../OS.hpp"
#include <Carbon/Carbon.h>
#include <IOKit/hid/IOHIDDevice.h>
#include <IOKit/hid/IOHIDManager.h>
#include <vector>

namespace NordicArts {
    namespace NordicOS {
        typedef std::vector<IOHIDElementRef> IOHIDElements;

        class HIDInputManager : NonCopyable {
        // Variables
        public:
        protected:
        private:
            bool                m_bIsValid;
        
            CFDataRef           m_layoutData;
            
            UCKeyboardLayout    *m_layout;
            
            IOHIDManagerRef     m_manager;

            IOHIDElements       m_keys[Keyboard::KeyCount];
            IOHIDElements       m_buttons[Mouse::ButtonCount];

        // Methods
        public:
            static HIDInputManager &getInstance();

            bool isKeyPressed(Keyboard::Key key);
            bool isMouseButtonPressed(Mouse::Button button);

            static long getLocationID(IOHIDDeviceRef device);
        
            static CFDictionaryRef copyDevicesMask(UINT32 iPage, UINT32 iUsage);
            
            static Keyboard::Key localizedKeys(UniChar ch);
            static Keyboard::Key nonLocalizedKeys(UniChar virtualKeycode);

        protected:
        private:
            HIDInputManager();
            ~HIDInputManager();

            void initalizeKeyboard();
            void initalizeMouse();
            void loadKeyboard(IOHIDDeviceRef keyboard);
            void loadMouse(IOHIDDeviceRef mouse);
            void loadKey(IOHIDElementRef key);
            void loadButton(IOHIDElementRef button);
            void freeUp();

            CFSetRef copyDevices(UINT32 iPage, UINT32 iUsage);

            bool isPressed(IOHIDElements &elements);

            static UINT8 usageToVirtualCode(UINT32 usage);

        };
    };
};

#endif 
