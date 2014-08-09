#ifndef NORDICARTS_GAME_SETUP_H
#define NORDICARTS_GAME_SETUP_H

#include "../Includes.hpp"
#include <NordicOS/sqlite/sqlite3.h>

namespace NordicArts {
	class Setup {
		// Variables
		public:
		protected:
		private:

		// Methods
		public:
			Setup();
			virtual ~Setup();

			bool doSetup();

		protected:
		private:
			bool checkForDatabase();

			void createDatabase();

	};	
};

#endif