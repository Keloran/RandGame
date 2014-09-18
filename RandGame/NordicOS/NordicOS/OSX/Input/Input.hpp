#ifndef NordicArts_NordicOS_OSX_InputImp_H
#define NordicArts_NordicOS_OSX_InputImp_H

#include "../../Window/Keyboard/Keyboard.hpp"
#include "../../Window/Mouse/Mouse.hpp"

namespace NordicArts {
    namespace NordicOS {
        class InputImp {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            static bool isKeyPressed(Keyboard::Key key);
            static bool isMouseButtonPressed(Mouse::Button button);

            static void setVirtualKeyboardVisible(bool bVisible);
            static void setMousePositon(const glm::vec2 &vPosition);

            static glm::vec2 getMousePositon();
            static glm::vec2 getMousePotion(const Window &oWindiw);

        protected:
        private:

        };
    };
};

#endif
