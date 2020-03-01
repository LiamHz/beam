#ifndef SHAPES_SPHERE_H
#define SHAPES_SPHERE_H

#include "core/shape.h"
#include "core/geometry.h"
#include "structs/hitinfo.h"

class Sphere : public Shape {
public:
    Sphere(vec3 _center, float _radius) : Shape() {
        center = _center;
        radius = _radius;
    }
    bool Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info);

    vec3 center;
    float radius;
};

#endif
