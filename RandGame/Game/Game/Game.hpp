#ifndef NordicArts_Game_H
#define NordicArts_Game_H

#include "./Includes.hpp"
#include "./Setup/Setup.hpp"
#include "./buildNumber.hpp"

// NordicOS
#include <NordicOS/OS.hpp>
#include <NordicOS/Logger/Logger.hpp>

// Valkyrie
#include <Valkyrie/Valkyrie.hpp>
#include <Valkyrie/Window/Window.hpp>

namespace NordicArts {
    namespace GameNS {
        // Game State
        enum GameState {
            GS_INTRO,
            GS_MENU,
            GS_PAUSED_MENU,
            GS_GAME,
            GS_QUIT,
            GS_NUM_STATES,
        };

        // Class
        class Game {
        // Variables
        public:
        protected:
        private:
            NordicOS::Logger    *m_pLogger  = nullptr;
            
            std::string          m_cGameName;
            glm::uvec2           m_vOpenGL;

        // Methods
        public:
            Game();
            Game(NordicOS::Logger *pLogger);

            virtual ~Game();
            
            void Startup();
            bool RenderIntroCutScenes();
            void RenderMainMenu();
            void RenderGame(GameState eGS);
            void UpdateGame(GameState eGS);
            void RenderPauseMenu();
            void ShutDown();
            void ProcessInputs();
            void VideoPageFlip();
            
            void setOpenGL(int iMajor, int iMinor);
            void setGameName(std::string cGameName);

        protected:
        private:
        };

        const char *getBuildNumber();
    };
};

#endif
