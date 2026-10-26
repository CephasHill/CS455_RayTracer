//
// Created by peter on 2/26/2026.
//

#ifndef CS455_RAYTRACER_POLYGON_H
#define CS455_RAYTRACER_POLYGON_H
#include <vector>

#include "Object3D.h"
#include "Plane.h"
#include "Ray.h"
#include "Vec3.h"

class Polygon : public Object3D {
    static Vec3 calculateNormal(const std::vector<Vec3>& verts) {
        const Vec3 edge1 = verts[1] - verts[0];
        const Vec3 edge2 = verts[2] - verts[0];
        return edge1.cross(edge2).normalize();
    }

    static int calculateDominantAxis(const Vec3& n) {
        const double ax = std::abs(n.x);
        const double ay = std::abs(n.y);
        const double az = std::abs(n.z);

        if (ax >= ay && ax >= az) return 0;
        if (ay >= az) return 1;
        return 2;
    }
public:
    std::vector<Vec3> vertices;
    Vec3 normal;
    int dominantAxis;
    Plane const polygonPlane;

    Polygon(const std::vector<Vec3>& vertices, const Material& m)
        : Object3D(m),
          vertices(vertices),
          normal(calculateNormal(vertices)),
          dominantAxis(calculateDominantAxis(normal)),
          polygonPlane(normal,-normal.dot(vertices.front())) {}

    [[nodiscard]] double hit(const Ray& r) const override {
        if (const double t = polygonPlane.hit(r); t > 0) {
            Vec3 hitPt3D = r.at(t);
            std::pair<double, double> hitPt =
                dominantAxis == 0 ? std::pair(hitPt3D.y, hitPt3D.z)
                : dominantAxis == 1 ? std::pair(hitPt3D.x, hitPt3D.z)
                : std::pair(hitPt3D.x, hitPt3D.y);

            auto projectAndTranslate = [&](const Vec3& v) {
                std::pair<double, double> proj =
                    dominantAxis == 0 ? std::pair(v.y, v.z)
                    : dominantAxis == 1 ? std::pair(v.x, v.z)
                    : std::pair(v.x, v.y);
                return std::pair(proj.first - hitPt.first, proj.second - hitPt.second);
            };

            int numCrossings = 0;

            auto currentTransVertex = projectAndTranslate(vertices[0]);
            int signHolder = currentTransVertex.second < 0 ? -1 : 1;

            for (size_t i = 0; i < vertices.size(); ++i) {
                const auto nextTransVertex = projectAndTranslate(vertices[(i + 1) % vertices.size()]);
                const int nextSignHolder = nextTransVertex.second < 0 ? -1 : 1;

                if (signHolder != nextSignHolder) {
                    if (currentTransVertex.first > 0 && nextTransVertex.first > 0) {
                        numCrossings++;
                    } else if (currentTransVertex.first > 0 || nextTransVertex.first > 0) {
                        const auto cross = currentTransVertex.first - currentTransVertex.second * (nextTransVertex.first - currentTransVertex.first) /
                                     (nextTransVertex.second - currentTransVertex.second);
                        if (cross > 0) {
                            numCrossings++;
                        }
                    }
                }

                signHolder = nextSignHolder;
                currentTransVertex = nextTransVertex;
            }

            return numCrossings % 2 == 0 ? -1.0 : t;
        }
        return -1.0;
    }

    [[nodiscard]] Vec3 getNormal(const Vec3& hitPoint) const override {
        return normal;
    }
};

#endif //CS455_RAYTRACER_POLYGON_H