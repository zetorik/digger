#pragma once

#include <ostream>
#include <random>

std::mt19937& globalRandomEngine();

class Vec2 {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);

        Vec2 operator+(const Vec2& other) const;
        
        Vec2 operator-() const;

        Vec2 operator-(const Vec2& other) const; 

        Vec2 operator*(const float other) const;

        Vec2 operator/(const float other) const;

        Vec2 operator*(const Vec2& other) const;

        Vec2 operator/(const Vec2& other) const;

        void operator+=(const Vec2& other);

        void operator-=(const Vec2& other);

        void operator*=(float other);

        void operator*=(const Vec2& other);

        void operator/=(float other);

        void operator/=(const Vec2& other);

        float length() const;

        Vec2 normalized() const;

        Vec2 clamped(const Vec2& lo, const Vec2& hi) const;
};

std::ostream& operator<<(std::ostream& os, const Vec2& v);

bool circlesIntersect(const Vec2& c1, float r1, const Vec2& c2, float r2);
