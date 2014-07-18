#ifndef NORDICARTS_RANDGAME_GAME_H
#define NORDICARTS_RANDGAME_GAME_H

#include "../includes.h"

namespace NordicArts {
    class Game {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            Game();
            void Startup();
            bool RenderIntroCutScenes();
            void RenderMainMenu();
            void RenderGame();
            void UpdateGame();
            void RenderPauseMenu();
            void ShutDown();            
            void ProcessInputs();
            void VideoPageFlip();

        protected:
        private:
    };
};

#endif
