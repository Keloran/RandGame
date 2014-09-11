#ifndef NordicArts_Game_H
#define NordicArts_Game_H

#include "./Includes.hpp"
#include "./Setup/Setup.hpp"
#include "./buildNumber.hpp"

// NordicOS
#include <NordicOS/OS.hpp>
#include <NordicOS/Logger/Logger.hpp>
#include <NordicOS/Time/Time.hpp>

// Valkyrie
#include <Valkyrie/Valkyrie.hpp>
#include <Valkyrie/Window/Window.hpp>
#include <Valkyrie/Color/Color.hpp>

namespace NordicArts {
    namespace GameNS {
        class GameState;
        
        class Game {
        // Variables
        public:
            std::stack<GameState*>  m_sStates;
        
            ValkyrieNS::Window      m_oWindow;
            
            NordicOS::Logger        *m_pLogger = nullptr;
            
        protected:
        private:
            
        // Methods
        public:
            void pushState(GameState *pState);
            void popState();
            void changeState(GameState *pState);
            
            GameState *peekState();
            
            void gameLoop();
            
            Game();
            Game(NordicOS::Logger *pLogger);
            ~Game();
            
        protected:
        private:
            void doWindow();
        };

        const char *getBuildNumber();
    };
};

#endif
