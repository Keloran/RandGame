#include "./Game.hpp"

namespace NordicArts {
    Game::Game() {}
    Game::Game(Logger *pLogger) : m_pLogger(pLogger) {}

    Game::~Game() {
        m_pLogger = nullptr;
    }
     
    void Game::Startup() {
        m_pLogger->log("Startup");

        // Do the setup routine
        Setup oSetup;
        Setup *pSetup = &oSetup;
        pSetup->doSetup();

        glm::vec2 vResolution = pSetup->getResolution();

        m_Window.create(sf::VideoMode(vResolution.x, vResolution.y), pSetup->getGameName());
        
        if (pSetup->isVSync()) {
            m_Window.setFramerateLimit(60);
        }
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
};
