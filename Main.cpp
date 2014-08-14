#include "./Main.hpp"

namespace NordicArts {

    // Threading
    void threadUpdateGame(Game *pGame, GameState eGS) {
        pGame->UpdateGame(eGS);
    }
    void threadRenderGame(Game *pGame, GameState eGS) {
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

    void messageCallback(const asSMessageInfo *pMsg, void *pParam) {
        const char *cType = "ERR: ";
        if (pMsg->type == asMSGTYPE_WARNING) {
            cType = "WARN: ";
        } else if (pMsg->type == asMSGTYPE_INFORMATION) {
            cType = "INFO: ";
        }

        printf("%s (%d, %d) : %s : %s\n", pMsg->section, pMsg->row, pMsg->col, cType, pMsg->message);
    }

    int main() {
        // Exception Pointer
        std::exception_ptr ptrException;

        try {
            // Create the Logger Pointer
            Logger::Logger oLogger("RandGame.log");
            Logger::Logger *pLogger = &oLogger;

             // AngelScript
            asIScriptEngine *pEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
            int iR = pEngine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);
            assert(iR >= 0);

            // Set the inital GameState
            GameState eGameState = GS_INTRO;
                
            // Create the Game Pointer
            Game::Game oGame(pLogger, pEngine);
            Game::Game* pGame = &oGame;    

            pGame->Startup();

            // GameLoop
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

                        std::thread render(threadRenderGame, pGame, eGameState);
                        render.join(); 
                    } break;
                    
                    case GS_GAME: {
                        std::thread update(threadUpdateGame, pGame, eGameState);
                        std::thread render(threadRenderGame, pGame, eGameState);

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

        // Handle Exceptions {kinda}
        handleException(ptrException);

        return EXIT_SUCCESS;
    }
};

// Keep Main in NameSpace
int main() {
    return NordicArts::main();
}
