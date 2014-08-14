#ifndef NORDICARTS_GAME_FOREST_H
#define NORDICARTS_GAME_FOREST_H

#include "../Includes.hpp"

#include <NordicOS/OS.hpp>
#include <NordicOS/Noise/Simplex.hpp>

namespace NordicArts {
	class Forest {
		// Variables
		public:
		protected:
		private:
			int m_iX;
			int m_iY;
			int m_iGridX;
			int m_iGridY;

			int m_iMaxSize;

		// Methods
		public:
			Forest(int iX, int iY, int iMaxSize);

			void setGridSize(int iGridSize);

		protected:
		private:

	};
};

#endif