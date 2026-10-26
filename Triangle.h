//
// Created by peter on 3/3/2026.
//

#ifndef CS455_RAYTRACER_TRIANGLE_H
#define CS455_RAYTRACER_TRIANGLE_H

#include <vector>

#include "Object3D.h"
#include "Plane.h"


class Triangle : public Object3D {
    static Vec3 calculateNormal(const std::vector<Vec3>& verts) {
        const Vec3 edge1 = verts[1] - verts[0];
        const Vec3 edge2 = verts[2] - verts[0];
        return edge1.cross(edge2).normalize();
    }
public:
    std::vector<Vec3> vertices;
    Vec3 normal;
    Plane const polygonPlane;

    Triangle(const std::vector<Vec3>& vertices, const Material& m)
        : Object3D(m),
          vertices(vertices),
          normal(calculateNormal(vertices)),
          polygonPlane(normal,-normal.dot(vertices.front())) {}

    [[nodiscard]] double hit(const Ray& r) const override {
        if (const double t = polygonPlane.hit(r); t > 0) {
            const Vec3 hitPt = r.at(t);
            // Take the cross product of the edge with the vector to the intersection point
            const Vec3 edge0 = vertices[1] - vertices[0];
            const Vec3 edge1 = vertices[2] - vertices[1];
            const Vec3 edge2 = vertices[0] - vertices[2];

            const Vec3 C0 = hitPt - vertices[0];
            const Vec3 C1 = hitPt - vertices[1];
            const Vec3 C2 = hitPt - vertices[2];

            if (normal.dot(edge0.cross(C0)) > 0 &&
                normal.dot(edge1.cross(C1)) > 0 &&
                normal.dot(edge2.cross(C2)) > 0) return t;
        }
        return -1.0;
    }

    [[nodiscard]] Vec3 getNormal(const Vec3& hitPoint) const override {
        return normal;
    }
};


#endif //CS455_RAYTRACER_TRIANGLE_H