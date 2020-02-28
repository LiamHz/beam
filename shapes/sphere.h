#ifndef SHAPES_SPHERE_H
#define SHAPES_SPHERE_H

#include "core/shape.h"
#include "core/geometry.h"

using glm::vec3;

class Sphere : public Shape {
public:
    Sphere(vec3 _center, float _radius) : Shape() {
        center = _center;
        radius = _radius;
    }
    bool Intersect(const Ray &r);

    vec3 center;
    float radius;
};

#endif
