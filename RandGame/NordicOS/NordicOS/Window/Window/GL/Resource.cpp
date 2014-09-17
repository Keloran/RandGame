#include "./Resource.hpp"
#include "./Context.hpp"
#include "../../../Threading/Mutex/Mutex.hpp"
#include "../../../Threading/Lock/Lock.hpp"

namespace NordicArts {
    namespace NordicOS {
        unsigned int iCount = 0;
        
        Mutex oMutex;

        GLResource::GLResource() {
            {
                Lock oLock(oMutex);
                
                if (iCount == 0) {
                    GLContext::globalInit();
                }
                iCount++;
            }

            GLContext::ensureContext();
        }

        GLResource::~GLResource() {
            Lock oLock(oMutex);

            iCount--;
            if (iCount == 0) {
                GLContext::globalCleanup();
            }
        }

        void GLResource::ensureGLContext() {
            GLContext::ensureContext();
        }
    };
};
