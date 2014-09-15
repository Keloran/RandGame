//
//  Thread.inl
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Thread_INL
#define NordicArts_NordicOS_Thread_INL

struct ThreadFunc {
    virtual ~ThreadFunc() {}
            
    virtual void run() = 0;
};
        
template <typename T>
struct ThreadFunctor : ThreadFunc {
    ThreadFunctor(T functor) : m_functor(functor) {}
            
    virtual void run() {
        m_functor();
    }
            
    T m_functor;
};
        
template <typename F, typename A>
struct ThreadFunctorWithArg : ThreadFunc {
    ThreadFunctorWithArg(F function, A arg) : m_function(function), m_arg(arg) {}
            
    virtual void run() {
        m_function(m_arg);
    }
            
    F m_function;
    A m_arg;
};

template <typename C>
struct ThreadMemberFunc : ThreadFunc {
    ThreadMemberFunc(void(C::*function)(), C *object) : m_function(function), m_object(object) {}
            
    virtual void run() {
        (m_object->*m_function)();
    }
                
    void(C::*m_function)();
            
     C *m_object;
};
        
template <typename F>
Thread::Thread(F functor) : m_pImp(NULL), m_pEntryPoint(new ThreadFunctor<F>(functor)) {}

template <typename F, typename A>
Thread::Thread(F function, A argument) : m_pImp(NULL), m_pEntryPoint(new ThreadFunctorWithArg<F, A>(function, argument)) {}
        
template <typename C>
Thread::Thread(void(C::*function)(), C *object) : m_pImp(NULL), m_pEntryPoint(new ThreadMemberFunc<C>(function, object)) {}

#endif
