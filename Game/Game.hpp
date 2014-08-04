#ifndef NORDICARTS_RANDGAME_GAME_H
#define NORDICARTS_RANDGAME_GAME_H

#include "../includes.hpp"
#include "../Tools/OS/OS.hpp"

namespace NordicArts {
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
            Logger *m_pLogger = nullptr;

        // Methods
        public:
            Game();
            Game(Logger *pLogger);

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
};

#endif
