#include "../include/utils.hpp"
#include <cmath>
#include <algorithm>
#include <ostream>
#include <random>

std::mt19937& globalRandomEngine() {
    static std::random_device rd;          // Created once at first call
    static std::mt19937 engine(rd());      // Created once at first call, seeded with rd()
    return engine;                         // Returns reference to the SAME engine every time
}

bool circlesIntersect(const Vec2& c1, float r1, const Vec2& c2, float r2) {
    float dx = c2.x - c1.x;
    float dy = c2.y - c1.y;
    float rSum = r1 + r2;

    return (dx * dx + dy * dy) <= (rSum * rSum);
}

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const float other) const {
    return Vec2(x * other, y * other);
}

Vec2 Vec2::operator/(const float other) const {
    return Vec2(x / other, y / other);
}

Vec2 Vec2::operator*(const Vec2& other) const {
    return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator/(const Vec2& other) const {
    return Vec2(x / other.x, y / other.y);
}

void Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
}

void Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
}

void Vec2::operator*=(float other) {
    x *= other;
    y *= other;
}

void Vec2::operator/=(float other) {
    x /= other;
    y /= other;
}

void Vec2::operator*=(const Vec2& other) {
    x *= other.x;
    y *= other.y;
}

void Vec2::operator/=(const Vec2& other) {
    x /= other.x;
    y /= other.y;
}

float Vec2::length() const {
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::normalized() const {
    float len = length();

    return len == 0 ? Vec2() : Vec2(x / len, y / len);
}

Vec2 Vec2::clamped(const Vec2& lo, const Vec2& hi) const {
    return Vec2(
            std::clamp(x, lo.x, hi.x),
            std::clamp(y, lo.y, hi.y)
            );
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

