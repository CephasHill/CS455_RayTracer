//
// Created by peter on 2/21/2026.
//

#ifndef CS455_RAYTRACER_VEC3_H
#define CS455_RAYTRACER_VEC3_H

#pragma once
#include <cmath>

class Vec3 {
public:
    double x, y, z;

    Vec3(): x(0), y(0), z(0) {}
    Vec3(const double x, const double y, const double z): x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3 operator+(const double s) const {
        return {x + s, y + s, z + s};
    }

    Vec3 operator-(const Vec3 &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vec3 operator-(const double s) const {
        return {x - s, y - s, z - s};
    }


    Vec3 operator*(const Vec3 &v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vec3 operator/(const Vec3 &v) const {
        return {x / v.x, y / v.y, z / v.z};
    }

    friend Vec3 operator-(const double s, const Vec3 &v) {
        return {s - v.x, s - v.y, s - v.z};
    }

    Vec3 operator*(double s) const {
        return {x * s, y * s, z * s};
    }

    friend Vec3 operator*(double s, const Vec3 &v) {
        return v * s;
    }

    Vec3 operator/(double s) const {
        return {x / s, y / s, z / s};
    }

    friend Vec3 operator/(const double s, const Vec3 &v) {
        return {s / v.x, s / v.y, s / v.z};
    }

    Vec3 operator-() const {
        return {-x, -y, -z};
    }

    [[nodiscard]] Vec3 abs() const {
        return {std::abs(x), std::abs(y), std::abs(z)};
    }

    [[nodiscard]] double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]] Vec3 normalize() const {
        double l = length();
        return {x / l, y / l, z / l};
    }

    [[nodiscard]] double dot(const Vec3 &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    [[nodiscard]] Vec3 cross(const Vec3 &v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
};


#endif //CS455_RAYTRACER_VEC3_H