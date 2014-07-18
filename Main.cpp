#include "./includes.h"
#include "./Main.h"

using namespace NordicArts;

int main() {
    GameState gGameState = GS_INTRO;
        
    Game::Game oGame;
    Game::Game* pGame = &oGame;    

    pGame->Startup();

    while(gGameState != GS_QUIT) {
        pGame->ProcessInputs();        

        switch(gGameState) {
            case GS_INTRO: {
                bool bFinished = pGame->RenderIntroCutScenes();
                if (bFinished) {
                    gGameState = GS_MENU;
                }
            }
                break;

            case GS_PAUSED_MENU:
                pGame->RenderPauseMenu();
                pGame->RenderGame();
                break;
            
            case GS_GAME:  
                pGame->UpdateGame();
                pGame->RenderGame();
                break;
    
            case GS_MENU:
                pGame->RenderMainMenu();
                break;

            case GS_NUM_GAME_STATES:
            case GS_QUIT:
                break;
        }
        
        pGame->VideoPageFlip();
    }

    pGame->ShutDown();
    return EXIT_SUCCESS;
}
