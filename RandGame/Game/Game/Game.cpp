#include "./Game.hpp"
#include "./GameState/GameState.hpp"

namespace NordicArts {
    namespace GameNS {
        void Game::pushState(GameState *pState) {
            this->m_sStates.push(pState);
        }
        
        void Game::popState() {
            if (!this->m_sStates.empty()) {
                delete this->m_sStates.top();
                this->m_sStates.pop();
            }
            
            return;
        }
        
        void Game::changeState(GameState *pState) {
            if (!this->m_sStates.empty()) {
                popState();
            }
            
            pushState(pState);
            
            
            return;
        }
        
        GameState *Game::peekState() {
            if (this->m_sStates.empty()) {
                return nullptr;
            }

            return this->m_sStates.top();
        }
        
        void Game::gameLoop() {
            NordicOS::Clock oClock;
            
            while (this->m_oWindow.isOpen()) {
                int iElapsed = oClock.restart();
                
                // Not in a state
                if (peekState() == nullptr) {
                    continue;
                }
                
                peekState()->handleInput();
                peekState()->update(iElapsed);
                
                this->m_oWindow.clear(ValkyrieNS::Color::Black);
                
                peekState()->draw(iElapsed);
                
                this->m_oWindow.display();
            }
        }
        
        Game::Game() {
            doWindow();
        }
        
        Game::Game(NordicOS::Logger *pLogger) {
            m_pLogger = pLogger;
            
            doWindow();
        }
        
        void Game::doWindow() {
            ValkyrieNS::Window oWindow;
            m_oWindow = oWindow;
            
            this->m_oWindow.setDimensions(800, 600);
            this->m_oWindow.setTitle("City Builder");
            this->m_oWindow.createWindow();
            this->m_oWindow.setFramerateLimit(60);
        }
        
        Game::~Game() {
            while(!this->m_sStates.empty()) {
                popState();
            }
        }

        // Build Number
        const char *getBuildNumber() {
            std::ostringstream output;
            output << GAME_BUILDNUMBER;
            return output.str().c_str();
        }
    };
};
