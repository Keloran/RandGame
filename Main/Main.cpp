#include "./Main.hpp"

namespace NordicArts {
    // Threading
    void ThreadUpdateGame(GameNS::Game *pGame, GameNS::GameState eGS) {
        pGame->UpdateGame(eGS);
    }
    void ThreadRenderGame(GameNS::Game *pGame, GameNS::GameState eGS) {
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
            NordicOS::Logger::Logger oLogger("RandGame.log");
            NordicOS::Logger::Logger *pLogger = &oLogger;

            GameNS::GameState eGameState = GameNS::GS_INTRO;

            GameNS::Game::Game oGame(pLogger);
            GameNS::Game::Game* pGame = &oGame;

            pGame->Startup();

            while(eGameState != GameNS::GS_QUIT) {
                pGame->ProcessInputs();

                switch(eGameState) {
                    case GameNS::GS_INTRO: {
                        bool bFinished = pGame->RenderIntroCutScenes();
                        if (bFinished) {
                            //eGameState = GS_MENU;
                            eGameState = GameNS::GS_QUIT;
                        }
                    } break;

                    case GameNS::GS_PAUSED_MENU: {
                        pGame->RenderPauseMenu();

                        std::thread render(ThreadRenderGame, pGame, eGameState);
                        render.join();
                    } break;

                    case GameNS::GS_GAME: {
                        std::thread update(ThreadUpdateGame, pGame, eGameState);
                        std::thread render(ThreadRenderGame, pGame, eGameState);

                        update.join();
                        render.join();
                    } break;

                    case GameNS::GS_MENU: {
                        pGame->RenderMainMenu();
                    } break;

                    case GameNS::GS_QUIT:
                    case GameNS::GS_NUM_STATES:
                    default: {
                    } break;
                }

                pGame->VideoPageFlip();
            }

            pGame->ShutDown();
        } catch (std::exception &ex) {
            throw NordicOS::ExceptionHandler::ExceptionHandler(ex.what());
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
