#ifndef NordicArts_NordicOS_Singleton_H
#define NordicArts_NordicOS_Singleton_H

#include "../OS.hpp"

namespace NordicArts {
	namespace NordicOS {
		class Singleton {
			// Variables
			public:
				enum SingletonType {
					TYPE_LOGGER = 0,
					TYPE_SETTINGS,
					TYPE_ENGINE,
					TYPE_SHADER_MANAGER,
				};

			protected:
			private:
				SingletonType m_eType;

			// Methods
			public:
				virtual ~Singleton();

			protected:
				explicit Singleton(SingletonType eType);

			private:

		};
	};
};

#endif
