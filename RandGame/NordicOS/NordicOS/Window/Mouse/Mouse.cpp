#include "./Mouse.hpp"
#include "../InputImp.hpp"
#include "../Window.hpp"

namespace NordicArts {
    namespace NordicOS {
        bool Mouse::isButtonPressed(Button eButton) {
            return InputImp::isMouseButtonPressed(eButton);
        }

        glm::vec2 Mouse::getPosition() {
            return InputImp::getMousePosition();
        }
        glm::vec2 Mouse::getPositon(const Window &oWindow) {
            return InputImp::getMousePositon(oWindow);
        }

        void Mouse::setPosition(const glm::vec2 &vPosition) {
            InputImp::setMousePostion(vPosition);
        }
        void Mouse::setPosition(const glm::vec2 &vPosition, const Window &oWindow) {
            InputImp::setMousePositon(vPosition, oWindow);
        }
    };
};
