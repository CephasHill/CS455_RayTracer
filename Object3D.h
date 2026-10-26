//
// Created by peter on 3/3/2026.
//

#ifndef CS455_RAYTRACER_OBJECT3D_H
#define CS455_RAYTRACER_OBJECT3D_H
#include "Material.h"
#include "Ray.h"


class Object3D {
public:
    Material mat;

    Object3D(const Material& m) : mat(m) {}

    virtual ~Object3D() = default;

    [[nodiscard]] virtual double hit (const Ray& r) const = 0;
    [[nodiscard]] virtual Vec3 getNormal(const Vec3& hitPoint) const = 0;
};


#endif //CS455_RAYTRACER_OBJECT3D_H