#include "./includes.hpp"
#include "./Main.hpp"
#include <Markov/Markov.hpp>
#include <Names/Names.hpp>
#include <OS/Noise/Simplex.hpp>

using namespace NordicArts;

void UpdateGame(Game *pGame, GameState eGS) {
    pGame->UpdateGame(eGS);
}
void RenderGame(Game *pGame, GameState eGS) {
    pGame->RenderGame(eGS);
}

int main() {
    try {
        Logger::Logger oLogger("RandGame.log");
        Logger::Logger *pLogger = &oLogger;

        GameState eGameState = GS_INTRO;
            
        Game::Game oGame(pLogger);
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

        Markov::Markov oMarkov(pLogger);
        Markov::Markov *pMarkov = &oMarkov;

        pLogger->log("---- .05f ----");
        pMarkov->setVariance(.05f);
        for (int i = 0; i < 15; i++) {
            pMarkov->generateWord();
        }

        pLogger->log("---- .101f ---- ");
        pMarkov->setVariance(.101f);
        for (int i = 0; i < 15; i++) {
            pMarkov->generateWord();
        }
        pLogger->log("---- Names ---- ");
        Names::Names oNames(pLogger);
        Names::Names *pNames = &oNames;
        for (int i = 0; i < 15; i++) {
            pNames->generateName();
        }
        
        pLogger->log("---- Simplex 2D ---- ");
        int it = 2;
        Simplex::Simplex oSimplex;
        Simplex::Simplex *pSimplex = &oSimplex;
        for (int i = 0; i < it; i++) {
            for (int j = 0; j < it; j++) {
                pLogger->log(pSimplex->octaveNoise2d(3, 0.5, 1, i, j));
            }
        }
        pLogger->log("---- Simplex 3D ---- ");
        for (int i = 0; i < it; i++) {
            for (int j = 0; j < it; j++) {
                for (int k = 0; k < it; k++) {
                    pLogger->log(pSimplex->octaveNoise3d(3, 0.5, 1, i, j, k));
                }
            }
        }
        pLogger->log("---- Simplex 4D ---- ");
        for (int i = 0; i < it; i++) {
            for (int j = 0; j < it; j++) {
                for (int k = 0; k < it; k++) {
                    for (int l = 0; l < it; l++) {
                        pLogger->log(pSimplex->octaveNoise4d(3, 0.5, 1, i, j, k, l));
                    }
                }
            }
        }

        pLogger->log("---- Rand String ---- ");
        for (int i = 0; i < it; i++) {
            pLogger->log(randString().c_str());
        }

        std::chrono::high_resolution_clock::time_point timePoint    = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds timeDuration                       = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        int timeCount                                               = timeDuration.count();
        std::string cString = "Stuff: ";
        cString.append(getString(timeCount));
        pLogger->log(cString.c_str());

        pGame->ShutDown();
    } catch (std::exception &ex) {
        throw ExceptionHandler(ex.what());
    }
    return EXIT_SUCCESS;
}
