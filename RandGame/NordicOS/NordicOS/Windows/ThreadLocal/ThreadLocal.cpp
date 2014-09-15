#include "./ThreadLocal.hpp"

namespace NordicArts { 
    namespace NordicOS {
        ThreadLocalImp::ThreadLocalImp() {
            m_index = TlsAlloc();
        }

        ThreadLocalImp::~ThreadLocalImp() {
            TlsFree(m_index);
        }

        void ThreadLocalImp::setValue(void *pValue) {
            TlsSetValue(m_index, pValue);
        }
        
        void *ThreadLocalImp::getValue() const {
            return TlsGetValue(m_index);
        }
    };
};
