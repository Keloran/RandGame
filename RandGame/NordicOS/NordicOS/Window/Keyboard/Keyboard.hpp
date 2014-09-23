#ifndef NordicArts_NordicOS_Window_Keyboard_H
#define NordicArts_NordicOS_Window_Keyboard_H

namespace NordicArts {
	namespace NordicOS {
		class Keyboard {
		// Variables
		public:
			enum Key {
				Unknown = -1,

				A = 0,
				B, C, D, E, F, G, H,
				I, J, K, L, M, N, O,
				P, Q, R, S, T, U, V,
				W, X, Y, Z,

				Num0, Num1, Num2, Num3,
				Num4, Num5, Num6, Num7,
				Num8, Num9,

				Escape, LControl, LShift,
				LAlt, LSystem, RControl,
				RShift, RAlt, RSystem,
				Menu, LBracket, RBracket,
				SemiColon, Comma, Period,
				Quote, Slash, BackSlash,
				Tilde, Equal, Dash, Space,
				Return, BackSpace, Tab,
				PageUp, PageDown, End,
				Home, Insert, Delete,
				Add, Subtract, Multiply,
				Divide, Left, Right,
				Up, Down,

				NumPad0, NumPad1, NumPad2,
				NumPad3, NumPad4, NumPad5,
				NumPad6, NumPad7, NumPad8,
				NumPad9,

				F1, F2, F3, F4, F5, F6,
				F7, F8, F9, F10, F11,
				F12, F13, F14, F15,

				Pause,

				KeyCount
			};

		protected:
		private:

		// Methods
		public:
			static bool isKeyPressed(Key key);

			static void setVirtualKeyboardVisible(bool bVisible);

		protected:
		private:

		};
	};
};

#endif
