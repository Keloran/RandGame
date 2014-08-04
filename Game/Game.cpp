#include "../includes.hpp"
#include "./Game.hpp"
#include "./Setup/Setup.hpp"

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
    }

    void Game::RenderMainMenu() {
        m_pLogger->log("Main Menu");
    }

    void Game::RenderGame(GameState eGS) {
        while(eGS != GS_QUIT) {
            m_pLogger->log("Render Game");
            sleep(1);
        }
    }   

    void Game::UpdateGame(GameState eGS) {
        while (eGS != GS_QUIT) {
            m_pLogger->log("Update");
            sleep(3);
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
