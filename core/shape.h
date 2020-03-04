#ifndef SHAPE_H
#define SHAPE_H

#include "core/geometry.h"
#include "structs/hitinfo.h"

class Shape {
public:
    Shape(vec3 _position) { position = _position; }
    virtual ~Shape() {}
    virtual bool Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info) = 0;
    virtual Bounds GetBounds() = 0;

    vec3 position;
};

#endif
