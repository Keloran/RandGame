#ifndef NordicArts_NordicOS_ThreadLocalPtr_INL
#define NordicArts_NordicOS_ThreadLocalPtr_INL

namespace NordicArts {
    namespace NordicOS {
        template<typename T>
        ThreadLocalPtr<T>::ThreadLocalPtr(T *pValue) : ThreadLocal(true) {}

        template<typename T>
        T &ThreadLocalPtr<T>::operator *() const {
            return *static_cast<T>(getValue());
        }

        template<typename T>
        T *ThreadLocalPtr<T>::operator ->() const {
            return static_cast<T*>(getValue());
        }

        template<typename T>
        ThreadLocalPtr<T>::operator T*() const {
            return static_cast<T*>(getValue());
        }

        template<typename T>
        ThreadLocalPtr<T> &ThreadLocalPtr<T>::operator =(T *pValue) {
            setValue(pValue);

            return *this;
        }

        template<typename T>
        ThreadLocalPtr<T> &ThreadLocalPtr<T>::operator =(const ThreadLocalPtr<T> &oRight) {
            setValue(oRight.getValue());
            
            return *this;
        }
    };
};

#endif

