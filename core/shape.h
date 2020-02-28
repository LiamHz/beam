#ifndef SHAPE_H
#define SHAPE_H

#include "core/geometry.h"
#include "structs/hitinfo.h"

using glm::vec3;

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}
    virtual bool Intersect(const Ray &r, HitInfo &hit_info) = 0;
};

#endif
