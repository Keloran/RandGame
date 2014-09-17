#ifndef NordicArts_NordicOS_Window_GL_Context_H
#define NordicArts_NordicOS_Window_GL_Context_H

#include "../ContextSettings.hpp"
#include "../../../NonCopyable/NonCopyable.hpp"

namespace NordicArts {
    namespace NordicOS {
        class WindowImp;

        class GLContext : NonCopyable {
        // Variables
        public:
        protected:
            ContextSettings     m_Settings;

        private:

        // Methods
        public:
            static void globalInit();
            static void globalCleanup();
            static void ensureContext();

            static GLContext *create();
            static GLContext *create(const ContextSettings &oSettings, const WindowImp *pOwner, unsigned int iBitsPerPixel);
            static GLContext *create(const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight);

            virtual ~GLContext();

            const ContextSettings &getSettings() const;

            bool setActive(bool bActive);

            virtual void display() = 0;
            virtual void setVerticalSyncEnabled(bool bEnabled) = 0;

        protected:
            GLContext();

            virtual bool makeCurrent() = 0;

            static int evaluteFormat(unsigned int iBitsPerPixel, const ContextSettings &oSettings, int iColorBits, int iDepthBits, int iStencilBits, int iAntiAliasing);

        private:
            void initalize();
        };
    };
};

#endif
