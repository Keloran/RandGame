#include "./Context.hpp"
#include "../../../Threading/ThreadLocal/ThreadLocalPtr.hpp"
#include "../../../Threading/Mutex/Mutex.hpp"
#include "../../../Threading/Lock/Lock.hpp"
#include "../../../OpenGL/OpenGL.hpp"
#include "../.././OS.hpp"

#include <set>
#include <cstdlib>
#include <cassert>
#include "./Ext/Ext.hpp"

#if defined(NordicOS_Windows)
    #include "../../../Windows/OpenGL/Context.hpp"
#elif defined(NordicOS_Linux)
    #include "../../../Linux/OpenGL/Context.hpp"
#elif defined(NordicOS_OSX)
    #include "../../../OSX/OpenGL/Context.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        ThreadLocalPtr<GLContext> currentContext(NULL);
        
        ContextType *sharedContext = NULL;

        ThreadLocalPtr<GLContext> internalContext(NULL);
        std::set<GLContext*> internalContexts;
        Mutex internalContextsMutex;

        bool hasInternalContext() {
            if (!internalContext) {
                return false;
            }

            Lock lock(internalContextsMutex);
        
            return (internalContexts.find(internalContext) != internalContexts.end());
        }

        GLContext* getInternalContext() {
            if (!hasInternalContext()) {
                internalContext = GLContext::create();
                Lock lock(internalContextsMutex);
                inernalContexts.insert(internalContext);
            }

            return internalContext;
        }

        void GLContext::globalInit() {
            sharedContext = new ContextType(NULL);
            sharedContext->initalize();
            sharedContext->setActive(false);
        }

        void GLContext::globalCleanup() {
            delete sharedContext;
            sharedContext = NULL;

            Lock lock(internalContextsMutex);
            for (std::set<GLContext*>::iterator it = internalContexts.begin(); it != internalContexts.end(); ++it) {
                delete *it;
            }

            internalContexts.clear();
        }

        void GLContext::ensureContext() {
            if (!currentContext) {
                getInternalContext()->setActive(true);
            }
        }

        GLContext *GLContext::create() {
            GLContext *context = new ContextType(sharedContext);
            context->initalize();

            return context;
        }

        GLContext *GLContext::create(const ContextSettings &oSettings, const WindowImp *pOwner, unsigned int iBitsPerPixel) {
            ensureContext();

            GLContext *context = new ContextType(sharedContext, oSettings, pOwner, iBitsPerPixel);
            context->initalize();

            return context;
        }

        GLContext *GLContext::create(const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight) {
            ensureContext();

            GLContext *context = new ContextType(sharedContext, oSettings, iWidth, iHeight);
            context->initalize();
            
            return context;
        }

        GLContext::~GLContext() {
            if (sharedContext) {
                setActive(false);
            }
        }

        const ContextSettings &GLContext::getSettings() const {
            return m_oSettings;
        }

        bool GLContext::setActive(bool bActive) {
            if (bActive) {
                if (this != currentContext) {
                    if (makeCurrent()) {
                        currentContext = this;

                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return true;
                }
            } else {
                if (this == currentContext) {
                    return getInternalContext()->setActive(true);
                } else {
                    return true;
                }
            }
        }

        GLContext::GLContext() {
        }

        int GLContext::evaluateFormat(unsigned int iBitsPerPixel, const ContextSettings &oSettings, int iColorBits, int iDepthBits, int iStencilBits, int iAntiAliasing) {
            return (
                std::abs(static_cast<int>(iBitsPerPixel - iColorBits)) +
                std::abs(static_cast<int>(oSettings.iDepthBits - iDepthBits)) +
                std::abs(static_cast<int>(oSettings.iStencilBits - iStencilBits)) +
                std::abs(static_cast<int>(oSettings.iAntiAliasing - iAntiAliasing))
            );
        }

        void GLContext::initalize() {
            setActive(true);

            const GLubyte *version = glGetString(GL_
    };
};
