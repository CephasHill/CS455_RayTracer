//
// Created by peter on 2/26/2026.
//

#ifndef CS455_RAYTRACER_PLANE_H
#define CS455_RAYTRACER_PLANE_H

#pragma once
#include "Vec3.h"
#include "Ray.h"

class Plane {
public:
    Vec3 normal;
    double distance{};

    Plane() = default;

    Plane(const Vec3& normal, const double distance) : normal(normal.normalize()), distance(distance) {}

    [[nodiscard]] double hit(const Ray& r) const {
        const double vd = normal.dot(r.dir);

        if (vd == 0.0) return -1.0;

        const double v0 = -(normal.dot(r.orig) + distance);

        const double t = v0 / vd;

        return t > 0.0 ? t : -1.0;
    }
};


#endif //CS455_RAYTRACER_PLANE_H