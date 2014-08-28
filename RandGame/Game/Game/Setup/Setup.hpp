#ifndef NordicArts_Game_Setup_H
#define NordicArts_Game_Setup_H

#include "../Includes.hpp"

#include <NordicOS/sqlite/sqlite3.h>

#include <Valkyrie/Settings/Settings.hpp>

namespace NordicArts {
    namespace GameNS {
    	class Setup {
        // Variables
        public:
        protected:
        private:
            ValkyrieNS::GameSettings m_sGameSettings;

        // Methods
        public:
            Setup();
            virtual ~Setup();

            bool doSetup();
            bool isVSync() const;

            glm::vec2 getResolution() const;
            glm::vec2 getOpenGL() const;

            std::string getGameName();

            int getRefreshRate() const;
            
            void setOpenGL(glm::uvec2 vOpenGL);
            void setGameName(std::string cGameName);

        protected:
        private:
            bool checkForDatabase();

            void createDatabase();
        };
	};
};

#endif
