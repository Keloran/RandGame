#include "./Mouse.hpp"
#include "../InputImp.hpp"
#include "../Window.hpp"

namespace NordicArts {
    namespace NordicOS {
        bool Mouse::isButtonPressed(Button eButton) {
            return InputImp::isMouseButtonPressed(eButton);
        }

        Vector2i Mouse::getPosition() {
            return InputImp::getMousePosition();
        }
        Vector2i Mouse::getPosition(const Window &oWindow) {
            return InputImp::getMousePosition(oWindow);
        }

        void Mouse::setPosition(const Vector2i &vPosition) {
            InputImp::setMousePosition(vPosition);
        }
        void Mouse::setPosition(const Vector2i &vPosition, const Window &oWindow) {
            InputImp::setMousePosition(vPosition, oWindow);
        }
    };
};
