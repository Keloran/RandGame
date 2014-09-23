#ifndef NordicArts_NordicOS_Window_Mouse_H
#define NordicArts_NordicOS_Window_Mouse_H

#include "../../Maths/Vector2.hpp"

namespace NordicArts {
    namespace NordicOS {
        class Window;

        class Mouse {
        // Variables
        public:
            enum Button {
                Left,
                Right,
                Middle,
                XButton1,
                XButton2,

                ButtonCount
            };

        protected:
        private:    

        // Methods
        public:
            static bool isButtonPressed(Button eButton);

            static Vector2i getPosition();
            static Vector2i getPosition(const Window &oWindow);
            
            static void setPosition(const Vector2i &vPosition);
            static void setPosition(const Vector2i &vPosition, const Window &oWindow);

        protected:
        private:

        };
    };
};

#endif
