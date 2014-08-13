#include "./Main.hpp"

namespace NordicArts {

    // Threading
    void ThreadUpdateGame(Game *pGame, GameState eGS) {
        pGame->UpdateGame(eGS);
    }
    void ThreadRenderGame(Game *pGame, GameState eGS) {
        pGame->RenderGame(eGS);
    }

    // Handle Unknown Exceptions
    void handleException(std::exception_ptr ptrException) {
        try {
            if (ptrException) {
                std::rethrow_exception(ptrException);
            }
        } catch (const std::exception &ex) {
            std::cout << "Caught Exception: " << ex.what() << std::endl;
        }
    }

    int main() {
        std::exception_ptr ptrException;

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
                        std::thread update (ThreadUpdateGame, pGame, eGameState);
                        std::thread render (ThreadRenderGame, pGame, eGameState);

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

            Time::Time oTime;
            Time::Time *pTime = &oTime;
            std::string cString = "Stuff: ";
            cString.append(getString(pTime->getNanoSeconds()));
            pLogger->log(cString.c_str());

            Species::Species oSpecies;
            Species::Species *pSpecies = &oSpecies;
            std::vector<TreeSpecies> vTrees = pSpecies->getSpecies();
            srand(pTime->getNanoSeconds());
            int iRand = 0;
            for (int i = 0; i < it; i++) {
                iRand = ((rand() % vTrees.size()) + 1);

                switch (iRand) {
                    case 0: {
                        Tree::Tree oTree(vTrees[iRand], 0, 0);
                    }
                    break;
                }
            }

            pGame->ShutDown();
        } catch (std::exception &ex) {
            throw ExceptionHandler::ExceptionHandler(ex.what());
        } catch ( ... ) {
            ptrException = std::current_exception();
        }

        handleException(ptrException);

        return EXIT_SUCCESS;
    }
};

int main() {
    return NordicArts::main();
}
