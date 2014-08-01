#include "./includes.h"
#include "./Main.h"
#include "./Libs/Markov/Markov.h"
#include "./Libs/Names/Names.h"
#include "./Libs/Simplex/Simplex.h"

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
                    eGameState = GS_QUIT;
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

    Markov::Markov oMarkov;
    Markov::Markov *pMarkov = &oMarkov;
    std::cout << "---- .05f ---- " << std::endl;
    pMarkov->setVariance(.05f);
    for (int i = 0; i < 15; i++) {
        pMarkov->generateWord();
    }
    std::cout << "---- .101f ---- " << std::endl;
    pMarkov->setVariance(.101f);
    for (int i = 0; i < 15; i++) {
        pMarkov->generateWord();
    }
    std::cout << "---- Names ---- " << std::endl;
    Names::Names oNames;
    Names::Names *pNames = &oNames;
    for (int i = 0; i < 15; i++) {
        pNames->generateName();
    }
    
    std::cout << "---- Simplex 2D ---- " << std::endl;
    int it = 2;
    Simplex::Simplex oSimplex;
    Simplex::Simplex *pSimplex = &oSimplex;
    for (int i = 0; i < it; i++) {
        for (int j = 0; j < it; j++) {
            std::cout << pSimplex->octaveNoise2d(3, 0.5, 1, i, j) << std::endl;
        }
    }
    std::cout << "---- Simplex 3D ---- " << std::endl;
    for (int i = 0; i < it; i++) {
        for (int j = 0; j < it; j++) {
            for (int k = 0; k < it; k++) {
                std::cout << pSimplex->octaveNoise3d(3, 0.5, 1, i, j, k) << std::endl;
            }
        }
    }
    std::cout << "---- Simplex 4D ---- " << std::endl;
    for (int i = 0; i < it; i++) {
        for (int j = 0; j < it; j++) {
            for (int k = 0; k < it; k++) {
                for (int l = 0; l < it; l++) {
                    std::cout << pSimplex->octaveNoise4d(3, 0.5, 1, i, j, k, l) << std::endl;
                }
            }
        }
    }

    std::cout << "---- Rand String ---- " << std::endl;
    for (int i = 0; i < it; i++) {
        std::cout << randString().c_str() << std::endl;
    }

    std::chrono::high_resolution_clock::time_point timePoint    = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds timeDuration                       = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
    int timeCount                                               = timeDuration.count();
    std::cout << "Stuff: " << timeDuration.count() << std::endl;

    pGame->ShutDown();
    return EXIT_SUCCESS;
}
