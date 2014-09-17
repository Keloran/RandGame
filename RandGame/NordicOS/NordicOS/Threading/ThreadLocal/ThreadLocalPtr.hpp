#ifndef NordicArts_NordicOS_ThreadLocalPtr_H
#define NordicArts_NordicOS_ThreadLocalPtr_H

#include "./ThreadLocal.hpp"

namespace NordicArts {
    namespace NordicOS {
        template<typename T>
        class ThreadLocalPtr : private ThreadLocal {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            T &operator *() const;
            
            T *operator ->() const;

            operator T*() const;

            ThreadLocalPtr<T> &operator =(T *pValue);
            ThreadLocalPtr<T> &operator =(const ThreadLocalPtr<T> &oRight);

        protected:
        private:

        };
    };
};

#include "./ThreadLocalPtr.inl"

#endif
