#ifndef NordicArts_NordicOS_OSX_OpenGL_Context_H
#define NordicArts_NordicOS_OSX_OpenGL_Context_H

#include "../../Window/Window/GL/Context.hpp"

#ifdef __OBJC__
    @class NSOpenGLContext;
    typedef NSOpenGLContext *NSOpenGLContextRef;

    @class NSOpenGLView;
    typedef NSOpenGLView *NSOpenGLViewRef;

    @class NSWindow;
    typedef NSWindow *NSWindowRef;
#else
    typedef void *NSOpenGLContextRef;
    typedef void *NSOpenGLViewRef;
    typedef void *NSWindowRef;
#endif

namespace NordicArts {
    namespace NordicOS {
        class NAContext : public GLContext {
        // Variables
        public:
        protected:
        private:
            NSOpenGLContextRef  m_context;
            NSOpenGLViewRef     m_view;
            NSWindowRef         m_window;

        // Methods
        public:
            NAContext(NAContext *pShared);
            NAContext(NAContext *pShared, const ContextSettings &oSettings, const WindowImp *pOwner, unsigned int iBitsPerPixel);
            NAContext(NAContext *pShared, const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight);
        
            ~NAContext();

            virtual void display();
            virtual void setVerticalSyncEnabled(bool bEnabled);

        protected:
            virtual bool makeCurrent();

        private:
            void createContext(NAContext *pShared, unsigned int iBitsPerPixel, const ContextSettings &oSettings);

        };
    };
};

#endif
