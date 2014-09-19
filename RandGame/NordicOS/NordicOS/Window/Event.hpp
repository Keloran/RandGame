#ifndef NordicArts_NordicOS_Window_Event_H
#define NordicArts_NordicOS_Window_Event_H

#include "./Keyboard/Keyboard.hpp"
#include "./Mouse/Mouse.hpp"
#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {
        class Event {
        // Variables
        public:
            struct SizeEvent {
                unsigned int iWidth;
                unsigned int iHeight;
            };

            struct KeyEvent {
                Keyboard::Key   code;
                bool            bAlt;
                bool            bControl;
                bool            bShift;
                bool            bSystem;
            };

            struct TextEvent {
                UINT32 unicode;
            };

            struct MouseMoveEvent {
                int iX;
                int iY;
            };

            struct MouseButtonEvent {
                Mouse::Button button;
                int iX;
                int iY;
            };

            struct MouseWheelEvent {
                int iDelta;
                int iX;
                int iY;
            };

            enum EventType {
                Closed,
                Resized,
                LostFocus,
                GainedFocus,
                TextEntered,
                KeyPressed,
                KeyReleased,
                MouseWheelMoved,
                MouseButtonPressed,
                MouseButtonReleased,
                MouseMoved,
                MouseEntered,
                MouseLeft,
                
                Count
            };
            EventType type;

            union {
                SizeEvent           size;
                KeyEvent            key;
                TextEvent           text;
                MouseMoveEvent      mouseMove;
                MouseButtonEvent    mouseButton;
                MouseWheelEvent     mouseWheel;
            };

        protected:
        private:


        // Methods
        public:
        protected:
        private:

        };
    };
};

#endif
