#include "./Main.hpp"

// Threading
void ThreadUpdateGame(NordicArts::Game *pGame, NordicArts::GameState eGS) {
    pGame->UpdateGame(eGS);
}
void ThreadRenderGame(NordicArts::Game *pGame, NordicArts::GameState eGS) {
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
        NordicArts::Logger::Logger oLogger("RandGame.log");
        NordicArts::Logger::Logger *pLogger = &oLogger;

        NordicArts::GameState eGameState = NordicArts::GS_INTRO;
            
        NordicArts::Game::Game oGame(pLogger);
        NordicArts::Game::Game* pGame = &oGame;    

        pGame->Startup();

        while(eGameState != NordicArts::GS_QUIT) {
            pGame->ProcessInputs();        

            switch(eGameState) {
                case NordicArts::GS_INTRO: {
                    bool bFinished = pGame->RenderIntroCutScenes();
                    if (bFinished) {
                        //eGameState = GS_MENU;
                        eGameState = NordicArts::GS_QUIT;
                    }
                } break;

                case NordicArts::GS_PAUSED_MENU: {
                    pGame->RenderPauseMenu();
                    pGame->RenderGame(eGameState);
                } break;
                
                case NordicArts::GS_GAME: {
                    std::thread update (ThreadUpdateGame, pGame, eGameState);
                    std::thread render (ThreadRenderGame, pGame, eGameState);

                    update.join();
                    render.join();
                } break;
        
                case NordicArts::GS_MENU: {
                    pGame->RenderMainMenu();
                } break;

                case NordicArts::GS_QUIT:
                case NordicArts::GS_NUM_STATES:
                default: {
                } break;
            }
            
            pGame->VideoPageFlip();
        }

        NordicArts::Markov::Markov oMarkov(pLogger);
        NordicArts::Markov::Markov *pMarkov = &oMarkov;

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
        NordicArts::Names::Names oNames(pLogger);
        NordicArts::Names::Names *pNames = &oNames;
        for (int i = 0; i < 15; i++) {
            pNames->generateName();
        }
        
        pLogger->log("---- Simplex 2D ---- ");
        int it = 2;
        NordicArts::Simplex::Simplex oSimplex;
        NordicArts::Simplex::Simplex *pSimplex = &oSimplex;
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
            pLogger->log(NordicArts::randString().c_str());
        }

        NordicArts::TimeNA::TimeNA oTime;
        NordicArts::TimeNA::TimeNA *pTime = &oTime;
        std::string cString = "Stuff: ";
        cString.append(NordicArts::getString(pTime->getNanoSeconds()));
        pLogger->log(cString.c_str());

        NordicArts::Species::Species oSpecies;
        NordicArts::Species::Species *pSpecies = &oSpecies;
        std::vector<NordicArts::TreeSpecies> vTrees = pSpecies->getSpecies();
        srand(pTime->getNanoSeconds());
        int iRand = 0;
        for (int i = 0; i < it; i++) {
            iRand = ((rand() % vTrees.size()) + 1);

            switch (iRand) {
                case 0: {
                    NordicArts::Tree::Tree oTree(vTrees[iRand], 0, 0);
                }
                break;
            }
        }

        pGame->ShutDown();
    } catch (std::exception &ex) {
        throw NordicArts::ExceptionHandler::ExceptionHandler(ex.what());
    } catch ( ... ) {
        ptrException = std::current_exception();
    }

    handleException(ptrException);

    return EXIT_SUCCESS;
}
