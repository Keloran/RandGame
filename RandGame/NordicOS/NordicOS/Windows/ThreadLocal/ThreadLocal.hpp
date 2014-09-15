#ifndef NordicArts_NordicOS_ThreadLocalImp_H
#define NordicArts_NordicOS_ThreadLocalImp_H

#include "../../NonCopyable/NonCopyable.hpp"
#include <windows.h>

namespace NordicArts {
    namespace NordicOS {
        class ThreadLocalImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            DWORD m_index;

        // Methods
        public:
            ThreadLocalImp();
            ~ThreadLocalImp();
        
            void setValue(void *pValue);
            
            void *getValue() const;

        protected:
        private:

        };
    };
};

#endif
