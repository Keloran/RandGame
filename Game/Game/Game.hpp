#ifndef NORDICARTS_RANDGAME_GAME_H
#define NORDICARTS_RANDGAME_GAME_H

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
                NordicOS::Logger              *m_pLogger  = nullptr;

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

            protected:
            private:
        };

        const char *getBuildNumber();
    };
};

#endif
