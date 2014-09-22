//
//  Vector.inl
//  NordicOS
//
//  Created by Max Hooton on 22/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Maths_Vector3_INL
#define NordicArts_NordicOS_Maths_Vector3_INL

template<typename T>
inline Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template<typename T>
inline Vector3<T>::Vector3(T inX, T inY, T inZ) : x(inX), y(inY), z(inZ) {}

template<typename T>
template<typename U>
inline Vector3<T>::Vector3(const Vector3<U> &oVector) : x(static_cast<T>(oVector.x)), y(static_cast<T>(oVector.y)), z(static_cast<T>(oVector.z)) {}

template<typename T>
inline Vector3<T> operator -(const Vector3<T> &oLeft) {
    return Vector3<T>(-oLeft.x, -oLeft.y, -oLeft.z);
}

template<typename T>
inline Vector3<T> &operator +=(Vector3<T> &oLeft, const Vector3<T> &oRight) {
    oLeft.x += oRight.x;
    oLeft.y += oRight.y;
    oLeft.z += oRight.z;
    
    return oLeft;
}

template<typename T>
inline Vector3<T> &operator -=(Vector3<T> &oLeft, const Vector3<T> &oRight) {
    oLeft.x -= oRight.x;
    oLeft.y -= oRight.y;
    oLeft.z -= oRight.z;
    
    return oLeft;
}

template<typename T>
inline Vector3<T> operator +(const Vector3<T> &oLeft, const Vector3<T> &oRight) {
    return Vector3((oLeft.x + oRight.x), (oLeft.y + oRight.y), (oLeft.z + oRight.z));
}

template<typename T>
inline Vector3<T> operator -(const Vector3<T> &oLeft, const Vector3<T> &oRight) {
    return Vector3<T>((oLeft.x - oRight.x), (oLeft.y - oRight.y), (oLeft.z - oRight.z));
}

template<typename T>
inline Vector<T> operator *(const Vector3<T> &oLeft, T right) {
    return Vector3<T>((oLeft.x * right), (oLeft.y * right), (oLeft.z * right));
}

template<typename T>
inline Vector3<T> operator *(T left, const Vector3<T> &oRight) {
    return Vector3<T>((oRight.x * left), (oRight.y * left), (oRight.z * left));
}

template<typename T>
inline Vector3<T> &operator *=(Vector3<T> &oLeft, T right) {
    oLeft.x *= right;
    oLeft.y *= right;
    oLeft.z *= right;
    
    return oLeft;
}

template<typename T>
inline Vector3<T> operator /(const Vector3<T> &oLeft, T Right) {
    return Vector3<T>((oLeft.x / right), (oLeft.y / right), (oLeft.z / right));
}

template<typename T>
inline Vector3<T> &operator /=(Vector3<T> &oLeft, T right) {
    oLeft.x /= right;
    oLeft.y /= right;
    oLeft.z /= right;
    
    return oLeft;
}

template<typename T>
inline bool operator ==(const Vector3<T> &oLeft, const Vector3<T> &oRight) {
    return ((oLeft.x == oRight.x) && (oLeft.y == oRight.y) && (oLeft.z == oRight.z));
}

template<typename T>
inline bool operator !=(const Vector3<T> &oLeft, const Vector3<T> &oRight) {
    return ((oLeft.x != oRight.x) && (oLeft.y != oRight.y) && (oLeft.z != oRight.z));
}

#endif
