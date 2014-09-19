#include "./Keyboard.hpp"
#include "../InputImp.hpp"

namespace NordicArts {
	namespace NordicOS {
		bool Keyboard::isKeyPressed(Key key) {
			return InputImp::isKeyPressed(key);
		}

		void Keyboard::setVirtualKeyboardVisible(bool bVisible) {
			return InputImpL::setVirtualKeyboardVisible(bVisible);
		}
	};
};