#ifndef SHAPE_H
#define SHAPE_H

#include "core/geometry.h"
#include "structs/hitinfo.h"

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}
    virtual bool Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info) = 0;
};

#endif
