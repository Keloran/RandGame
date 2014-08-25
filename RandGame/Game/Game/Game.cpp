#include "./Game.hpp"

namespace NordicArts {
    namespace GameNS {
        Game::Game() {}
        Game::Game(NordicOS::Logger *pLogger) : m_pLogger(pLogger) {}

        Game::~Game() {
            m_pLogger = nullptr;
        }

        void Game::Startup() {
            m_pLogger->log("Startup");

            // Do the setup routine
            Setup oSetup;
            Setup *pSetup = &oSetup;
            
            pSetup->setOpenGL(m_vOpenGL);
            pSetup->setGameName(m_cGameName);
            pSetup->doSetup();

            glm::vec2 vResolution   = pSetup->getResolution();
            glm::vec2 vOpenGL       = pSetup->getOpenGL();
            int iRefreshRate        = pSetup->getRefreshRate();

            ValkyrieNS::Window::Window pWindow(vResolution.x, vResolution.y, pSetup->getGameName());

            // VSync
            if (pSetup->isVSync()) {
                pWindow.setFramerateLimit(iRefreshRate);
            } else {
                pWindow.setFramerateLimit(999);
            }

            // Base OpenGL
            if (vOpenGL.x == 0) {
                pWindow.setOpenGL(3, 3);
            } else {
                pWindow.setOpenGL(vOpenGL.x, vOpenGL.y);
            }

            pWindow.debugStuff();
        }

        void Game::RenderMainMenu() {
            m_pLogger->log("Main Menu");
        }

        void Game::RenderGame(GameState eGS) {
            while(eGS != GS_QUIT) {
                m_pLogger->log("Render Game");
            }
        }

        void Game::UpdateGame(GameState eGS) {
            while (eGS != GS_QUIT) {
                m_pLogger->log("Update");
            }
        }

        void Game::RenderPauseMenu() {
            m_pLogger->log("Pause Menu");
        }

        void Game::ShutDown() {
            m_pLogger->log("ShutDown");
        }

        void Game::ProcessInputs() {
            m_pLogger->log("Inputs");
        }

        void Game::VideoPageFlip() {
            m_pLogger->log("Video Page Flip");
        }

        bool Game::RenderIntroCutScenes() {
            m_pLogger->log("Intro Cut Scenes");

            return true;
        }
        
        // settings
        void Game::setGameName(std::string cGameName) {
            m_cGameName = cGameName;
        }
        void Game::setOpenGL(int iMajor, int iMinor) {
            glm::uvec2 vOpenGL;
            vOpenGL.x = iMajor;
            vOpenGL.y = iMinor;
            
            m_vOpenGL = vOpenGL;
        }
        

        // Build Number
        const char *getBuildNumber() {
            std::ostringstream output;
            output << GAME_BUILDNUMBER;
            return output.str().c_str();
        }
    };
};
