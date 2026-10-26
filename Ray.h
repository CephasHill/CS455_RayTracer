//
// Created by peter on 2/21/2026.
//

#ifndef CS455_RAYTRACER_RAY_H
#define CS455_RAYTRACER_RAY_H

#pragma once
#include "Vec3.h"

class Ray {
public:
    Vec3 orig;
    Vec3 dir;

    Ray() = default;

    Ray(const Vec3 &orig, const Vec3 &dir) : orig(orig), dir(dir) {}

    [[nodiscard]] Vec3 at(const double t) const {
        return orig + dir * t;
    }
};


#endif //CS455_RAYTRACER_RAY_H