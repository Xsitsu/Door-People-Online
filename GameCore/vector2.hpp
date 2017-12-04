#ifndef VECTOR2_HPP_INCLUDE
#define VECTOR2_HPP_INCLUDE

#include "main.h"

namespace Game
{

#ifdef _WIN32
struct DLL_EXPORT Vector2
#else
struct Vector2
#endif // _WIN32
{
    double x;
    double y;

    Vector2();
    Vector2(double x, double y);
    Vector2(const Vector2& rhs);
    Vector2& operator=(const Vector2& rhs);

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator*=(const double num);
    Vector2& operator/=(const double num);

    bool operator==(const Vector2& rhs) const;
    bool operator!=(const Vector2& rhs) const;
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(const double num) const;
    Vector2 operator/(const double num) const;
};

}

#endif // VECTOR2_HPP_INCLUDE
