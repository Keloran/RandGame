//
//  Vector3.hpp
//  NordicOS
//
//  Created by Max Hooton on 22/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Maths_Vector3_H
#define NordicArts_NordicOS_Maths_Vector3_H

namespace NordicArts {
    namespace NordicOS {
        template<typename T>
        class Vector3 {
        // Variables
        public:
            T x;
            T y;
            T z;
            
        protected:
        private:
            
        // Methods
        public:
            Vector3();
            Vector3(T x, T y, T z);
            
            template<typename U>
            explicit Vector3(const Vector3<U> &oVector);
            
        protected:
        private:
            
        };
        
        template<typename T>
        Vector3<T> operator -(const Vector3<T> &oLeft);
        
        template<typename T>
        Vector3<T> &operator +=(const Vector3<T> &oLeft, const Vector3<T> &oRight);
        
        template<typename T>
        Vector3<T> &operator -=(const Vector3<T> &oLeft, const Vector3<T> &oRight);
        
        template<typename T>
        Vector3<T> operator +(const Vector3<T> &oLeft, const Vector3<T> &oRight);
        
        template<typename T>
        Vector3<T> operator -(const Vector3<T> &oLeft, const Vector3<T> &oRight);
        
        template<typename T>
        Vector3<T> operator *(const Vector3<T> &oLeft, T right);
        
        template<typename T>
        Vector3<T> operator *(T left, const Vector3 &oRight);
        
        template<typename T>
        Vector3<T> &operator *=(Vector3<T> &oLeft, T right);
        
        template<typename T>
        Vector3<T> operator /(const Vector3<T> &oLeft, T right);
        
        template<typename T>
        Vector3<T> &operator /=(Vector3<T> &oLeft, T right);
        
        template<typename T>
        bool operator ==(const Vector3<T> &oLeft, const Vector3<T> &oRight);
        
        template<typename T>
        bool operator !=(const Vector3<T> &oLeft, const Vector3<T> &oRight);.
        
        #include "./Vector3.inl"
        
        typedef Vector3<int>        Vector3i;
        typedef Vector3<float>      Vector3f;
    };
};


#endif
