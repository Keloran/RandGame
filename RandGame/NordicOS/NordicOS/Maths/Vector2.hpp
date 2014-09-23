//
//  Vector2.hpp
//  NordicOS
//
//  Created by Max Hooton on 22/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicOS_NordicOS_Maths_Vector2_H
#define NordicOS_NordicOS_Maths_Vector2_H

namespace NordicArts {
    namespace NordicOS {
        template<typename T>
        class Vector2 {
        // Variables
        public:
            T x;
            T y;
            
        protected:
        private:
            
        // Methods
        public:
            Vector2();
            Vector2(T x, T y);
            
            template<typename U>
            explicit Vector2(const Vector2<U> &oVector);
        protected:
        private:
            
        };
        
        template<typename T>
        Vector2<T> operator -(const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> &operator +=(Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> &operator -=(Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> operator +(const Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> operator -(const Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> operator *(const Vector2<T> &oLeft, T right);
        
        template<typename T>
        Vector2<T> operator *(T left, const Vector2<T> &oRight);
        
        template<typename T>
        Vector2<T> &operator *=(Vector2<T> &oLeft, T right);
        
        template<typename T>
        Vector2<T> operator /(const Vector2<T> &oLeft, T right);
        
        template<typename T>
        Vector2<T> &operator /=(Vector2<T> &oLeft, T right);
        
        template<typename T>
        bool operator ==(const Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        template<typename T>
        bool operator !=(const Vector2<T> &oLeft, const Vector2<T> &oRight);
        
        #include "./Vector2.inl"
        
        typedef Vector2<int>            Vector2i;
        typedef Vector2<unsigned int>   Vector2u;
        typedef Vector2<float>          Vector2f;
    };
};


#endif
