#include "./Context.hpp"
#include "./GL/Context.hpp"

namespace NordicArts {
    namespace NordicOS {
        Context::Context() {
            m_context = GLContext::create();

            setActive(true);
        }

        Context::~Context() {
            delete m_context;
        }

        bool Context::setActive(bool bActive) {
            return m_context->setActive(bActive);
        }

        Context::Context(const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight) {
            m_context = GLContext::create(oSettings, iWidth, iHeight);

            setActive(true);
        }
    };
};
