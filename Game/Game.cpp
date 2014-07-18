#include "../includes.h"
#include "./Game.h"

namespace NordicArts {
    Game::Game() {}
     
    void Game::Startup() {
        std::cout << "Startup" << std::endl;
    }

    void Game::RenderMainMenu() {
        std::cout << "Main Menu" << std::endl;    
    }

    void Game::RenderGame(GameState eGS) {
        while(eGS != GS_QUIT) {
            std::cout << "Render Game" << std::endl;
            sleep(1);
        }
    }   

    void Game::UpdateGame(GameState eGS) {
        while (eGS != GS_QUIT) {
            std::cout << "Update" << std::endl;
            sleep(3);
        }
    }

    void Game::RenderPauseMenu() {
        std::cout << "Pause Menu" << std::endl;
    }

    void Game::ShutDown() {
        std::cout << "ShutDown" << std::endl;
    }

    void Game::ProcessInputs() {
        std::cout << "Inputs" << std::endl;
    }

    void Game::VideoPageFlip() {
        std::cout << "Video Page Flip" << std::endl;
    }    

    bool Game::RenderIntroCutScenes() {
        std::cout << "Intro Cut Scnes" << std::endl;

        return true;
    }
};
