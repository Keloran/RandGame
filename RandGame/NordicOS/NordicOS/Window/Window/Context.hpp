#ifndef NordicArts_NordicOS_Window_Context_H
#define NordicArts_NordicOS_Window_Context_H

#include "./GL/Resource.hpp"
#include "./ContextSettings.hpp"
#include "../NonCopyable/NonCopyable.hpp"

namespace NordicArts {
    namespace NordicOS {
        class GLContext;
        
        class Context : GLResource, NonCopyable {
        // Variables
        public:
        protected:
        private:
            GLContext *m_context;

        // Methods
        public:
            Context();
            Context(const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight);
            ~Context();

            bool setActive(bool bActive);

        protected:
        private:

        };
    };
};

#endif
