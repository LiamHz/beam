#ifndef SHAPES_SPHERE_H
#define SHAPES_SPHERE_H

#include <memory>

#include "core/shape.h"
#include "core/geometry.h"
#include "structs/hitinfo.h"

class Sphere : public Shape {
public:
    Sphere(vec3 _position, float _radius)
      : Shape(_position),
        radius(_radius),
        zMin(std::clamp(std::min(zMin, zMax), -radius, radius)),
        zMax(std::clamp(std::max(zMin, zMax), -radius, radius))
    {}
    bool Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info);
    Bounds GetBounds();

    vec3 center;
    float radius;
    float zMin, zMax;
};

#endif
