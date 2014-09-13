#include "./Main.hpp"

namespace NordicArts {
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
        try {
            NordicOS::Logger::Logger oLogger("RandGame.log");
            NordicOS::Logger::Logger *pLogger = &oLogger;

            GameNS::Game::Game oGame(pLogger);
            GameNS::Game::Game* pGame = &oGame;
            
            pGame->gameLoop();
        } catch (std::exception &ex) {
            throw NordicOS::ExceptionHandler::ExceptionHandler(ex.what());
        } catch (NordicOS::ExceptionHandler::ExceptionHandler &ex) {
            std::cout << "Exception: " << ex.getMessage() << std::endl;
        } catch ( ... ) {
            handleException(std::current_exception());
        }
        
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
