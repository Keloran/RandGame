#include "./Main.hpp"

namespace NordicArts {
    // Handle Unknown Exceptions
    void handleException(std::exception_ptr ptrException) {
        try {
            if (ptrException) {
                std::rethrow_exception(ptrException);
            }
        } catch (const std::exception &ex) {
            printIt(ex.what());
        }
    }

    int main() {
        try {
            NordicOS::Logger::Logger oLogger("RandGame.log");
            NordicOS::Logger::Logger *pLogger = &oLogger;

            GameNS::Game::Game oGame(pLogger);
            GameNS::Game::Game* pGame = &oGame;

            pGame->pushState(new GameStateStart(pGame));            
            pGame->gameLoop();
        } catch (std::exception &ex) {
            throw NordicOS::ExceptionHandler::ExceptionHandler(ex.what());
        } catch (NordicOS::ExceptionHandler::ExceptionHandler &ex) {
            printIt(ex.getMessage());
        } catch ( ... ) {
            handleException(std::current_exception());
        }
    
        printIt(RANDGAME_BUILDNUMBER);
        printIt(NordicOS::getBuildNumber());
        printIt(GameNS::getBuildNumber());
        printIt(ValkyrieNS::getBuildNumber());

        return EXIT_SUCCESS;
    }
};

int main() {
    return NordicArts::main();
}
