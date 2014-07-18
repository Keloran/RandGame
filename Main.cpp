#include "./includes.h"
#include "./Main.h"

using namespace NordicArts;

void UpdateGame(Game *pGame, GameState eGS) {
    pGame->UpdateGame(eGS);
}
void RenderGame(Game *pGame, GameState eGS) {
    pGame->RenderGame(eGS);
}

int main() {
    GameState eGameState = GS_INTRO;
        
    Game::Game oGame;
    Game::Game* pGame = &oGame;    

    pGame->Startup();

    while(eGameState != GS_QUIT) {
        pGame->ProcessInputs();        

        switch(eGameState) {
            case GS_INTRO: {
                bool bFinished = pGame->RenderIntroCutScenes();
                if (bFinished) {
                    //eGameState = GS_MENU;
                    eGameState = GS_GAME;
                }
            } break;

            case GS_PAUSED_MENU: {
                pGame->RenderPauseMenu();
                pGame->RenderGame(eGameState);
            } break;
            
            case GS_GAME: {
                std::thread update (UpdateGame, pGame, eGameState);
                std::thread render (RenderGame, pGame, eGameState);

                update.join();
                render.join();
            } break;
    
            case GS_MENU: {
                pGame->RenderMainMenu();
            } break;

            case GS_QUIT:
            case GS_NUM_STATES:
            default: {
            } break;
        }
        
        pGame->VideoPageFlip();
        sleep(5);
    }

    pGame->ShutDown();
    return EXIT_SUCCESS;
}
