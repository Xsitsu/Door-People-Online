#ifndef VECTOR2_HPP_INCLUDE
#define VECTOR2_HPP_INCLUDE

#include "GameCore_dll-export.h"

namespace Game
{

struct DLL_EXPORT Vector2
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
    Vector2 operator-() const;

    double Cross(const Vector2 &other) const;
};

}

#endif // VECTOR2_HPP_INCLUDE
