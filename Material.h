//
// Created by peter on 2/21/2026.
//

#ifndef CS455_RAYTRACER_MATERIAL_H
#define CS455_RAYTRACER_MATERIAL_H

#include "Vec3.h"


struct Material {
    double k_d, k_s, k_a;
    Vec3 o_d, o_s;
    double k_gls, refl;

    Material() : k_d(0.8), k_s(0.2), k_a(0.1), o_d(1,1,1), o_s(1,1,1), k_gls(32), refl(0.0) {}

    Material(const double k_d, const double k_s, const double k_a, const Vec3 &o_d, const Vec3 &o_s, const double k_gls, const double refl)
        : k_d(k_d), k_s(k_s), k_a(k_a), o_d(o_d), o_s(o_s), k_gls(k_gls), refl(refl) {}
};


#endif //CS455_RAYTRACER_MATERIAL_H