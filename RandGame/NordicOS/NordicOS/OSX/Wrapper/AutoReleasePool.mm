#include "../../ExceptionHandler/Errors.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include "../../Threading/ThreadLocal/ThreadLocalPtr.hpp"

#import "./AutoReleasePool.hpp"
#import <Foundation/Foundation.h>

namespace NordicArts {
    namespace NordicOS {
        class PoolWrapper : NonCopyable {
        // Variables
        public:
        protected:
        private:
            int                  m_iCount;
            //NSAutoreleasePool   *m_pPool;

        // Methods
        public:
            PoolWrapper();
            ~PoolWrapper();

            void retain();
            void release();
            void drain();

        protected:
        private:

        };

        //PoolWrapper::PoolWrapper() : m_iCount(0), m_pPool(0) {
        //}
        PoolWrapper::PoolWrapper() : m_iCount(0) {
        }

        PoolWrapper::~PoolWrapper() {
        }

        void PoolWrapper::retain() {
            ++m_iCount;

            //if (m_pPool == 0) {
            //    m_pPool = [[NSAutoreleasePool alloc] init];
            //}
        }

        void PoolWrapper::release() {
            --m_iCount;

            if (m_iCount == 0) {
                drain();
            }
        }

        void PoolWrapper::drain() {
            //[m_pPool drain];
            //m_pPool = 0;
    
            //if (m_iCount != 0) {
            //    m_pPool = [[NSAutoreleasePool alloc] init];
            //}
        }

        ThreadLocalPtr<PoolWrapper> localPool;
    };
};

void retainPool(void) {
    if (NordicArts::NordicOS::localPool == NULL) {
        NordicArts::NordicOS::localPool = new NordicArts::NordicOS::PoolWrapper();
    }

    NordicArts::NordicOS::localPool->retain();
}

void releasePool(void) {
    if (NordicArts::NordicOS::localPool != NULL) {
        NordicArts::NordicOS::localPool->release();
    }
}

void drainPool(void) {
    if (NordicArts::NordicOS::localPool != NULL) {
        NordicArts::NordicOS::localPool->drain();
    }
}
