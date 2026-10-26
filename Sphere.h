//
// Created by peter on 2/21/2026.
//

#ifndef CS455_RAYTRACER_SPHERE_H
#define CS455_RAYTRACER_SPHERE_H

#include "Material.h"
#include "Vec3.h"
#include "Ray.h"
#include "Object3D.h"


class Sphere : public Object3D {
public:
    Vec3 center;
    double radius{};

    Sphere(const Vec3 &center, const double radius, const Material& mat)
        : Object3D(mat), center(center), radius(radius) {}

    [[nodiscard]] double hit(const Ray& r) const override {
        const Vec3 oc = r.orig - center;
        const double a = r.dir.dot(r.dir);
        const double b = 2.0 * (r.dir.dot(oc));
        const double c = (oc.dot(oc) - radius * radius);

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return -1;
        }
        double t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t > 0.0) {
            return t;
        }
        t = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t > 0.0) {
            return t;
        }
        return -1;
    }
    [[nodiscard]] Vec3 getNormal(const Vec3& hitPoint) const override {
        return (hitPoint - center).normalize();
    }
};


#endif //CS455_RAYTRACER_SPHERE_H