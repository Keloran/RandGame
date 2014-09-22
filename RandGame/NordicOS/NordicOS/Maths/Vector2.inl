//
//  Vector2.ink.h
//  NordicOS
//
//  Created by Max Hooton on 22/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Maths_Vector2_INL
#define NordicArts_NordicOS_Maths_Vector2_INL

template<typename T>
inline Vector2<T>::Vector2 : x(), y(0) {}

template<typename T>
inline Vector2<T>::Vector2(T inX, T inY) : x(inX), y(inY) {}

template<typename T>
template<typename U>
inline Vector2<T>::Vector2(const Vector2<U> &oVector) : x(static_cast<T>(oVector.x)), y(static_cast<T>(oVector.y)) {}

template<typename T>
inline Vector2<T> operator -(const Vector2<T> &oRight) {
    return Vector2<T>(-oRight.x -oRight.y);
}

template<typename T>
inline Vector2<T> &operator +=(Vector2<T> &oLeft, const Vector2<T> &oRight) {
    oLeft.x     += oRight.x;
    oLeft.y     += oRight.y;
    
    return oLeft;
}

template<typename T>
inline Vector2<T> &operator -=(Vector2<T> &oLeft, const Vector2<T> &oRight) {
    oLeft.x -= oRight.x;
    oLeft.y -= oRight.y;
    
    return oLeft;
}

template<typename T>
inline Vector2<T> operator +(const Vector2<T> &oLeft, const Vector2<T> &oRight) {
    return Vector2<T>((oLeft.x + oRight.x), (oLeft.y + oRight.y));
}

template<typename T>
inline Vector2<T> operator -(const Vector2<T> &oLeft, const Vector2<T> &oRight) {
    return Vector2<T>((oLeft.x - oRight.x), (oLeft.y - oRight.y));
}

template<typename T>
inline Vector2<T> operator *(const Vector2<T> &oLeft, T right) {
    return Vector2<T>((oLeft .x * right), (oLeft.y * right));
}

template<typename T>
inline Vector2<T> operator *(T left, const Vector2<T> &oRight) {
    return Vector2<T>((oRight.x * left), (oRight.y * left));
}

template<typename T>
inline Vector2<T> &operator *=(Vector2<T> &oLeft, T right) {
    oLeft.x *= right;
    oLeft.y *= right;
    
    return oLeft;
}

template<typename T>
inline Vector2<T> operator /(const Vector2<T> &oLeft, T right) {
    return Vector2<T>((oLeft.x / right), (oLeft.y / right));
}

template<typename T>
inline Vector2<T> &operator /=(Vector2<T> &oLeft, T right) {
    oLeft.x /= right;
    oLeft.y /= right;
    
    return oLeft;
}

template<typename T>
inline bool operator ==(const Vector2<T> &oLeft, const Vector2<T> &oRight) {
    return ((oLeft.x == oRight.x) && (oLeft.y == oRight.y));
}

template<typename T>
inline bool operator !=(const Vector2<T> &oLeft, const Vector2<T> &oRight) {
    return ((oLeft.x != oRight.x) && (oLeft.y != oRight.y));
}

#endif
