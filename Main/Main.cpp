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

                        std::thread render(ThreadRenderGame, pGame, eGameState);
                        render.join(); 
                    } break;
                    
                    case GS_GAME: {
                        std::thread update(ThreadUpdateGame, pGame, eGameState);
                        std::thread render(ThreadRenderGame, pGame, eGameState);

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

            pGame->ShutDown();
        } catch (std::exception &ex) {
            throw ExceptionHandler::ExceptionHandler(ex.what());
        } catch ( ... ) {
            ptrException = std::current_exception();
        }

        handleException(ptrException);

        std::cout << "RandGame: " << RANDGAME_BUILDNUMBER << std::endl;
        std::cout << "NordicOS: " << NordicOS::getBuildNumber() << std::endl;
        std::cout << "Game: " << GameNS::getBuildNumber() << std::endl;
        std::cout << "Valkyrie: " << ValkyrieNS::getBuildNumber() << std::endl;

        return EXIT_SUCCESS;
    }
};

int main() {
    return NordicArts::main();
}
