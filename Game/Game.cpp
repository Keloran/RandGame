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

    void Game::RenderGame() {
        std::cout << "Game" << std::endl;
    }   

    void Game::UpdateGame() {
        std::cout << "Update" << std::endl;
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
