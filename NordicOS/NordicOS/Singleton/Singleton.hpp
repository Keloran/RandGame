#ifndef NORDICARTS_OS_SINGLETON_H
#define NORDICARTS_OS_SINGLETON_H

#include "../OS.hpp"

namespace NordicArts {
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

#endif
