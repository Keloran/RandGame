//
//  ThreadLocal.cpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./ThreadLocal.hpp"

#if defined(NordicOS_Windows)
    #include "../../Windows/ThreadLocal/ThreadLocal.hpp"
#else
    #include "../../nonWindows/ThreadLocal/ThreadLocal.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        ThreadLocal::ThreadLocal(void *pValue) {
            m_pImp = new ThreadLocalImp;
            setValue(pValue);
        }
        
        ThreadLocal::~ThreadLocal() {
            delete m_pImp;
        }
        
        void ThreadLocal::setValue(void *pValue) {
            m_pImp->setValue(pValue);
        }
        
        void *ThreadLocal::getValue() const {
            return m_pImp->getValue();
        }
    };
};