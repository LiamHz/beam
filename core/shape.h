#ifndef SHAPE_H
#define SHAPE_H

#include "geometry.h"

using glm::vec3;

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}
    virtual bool Intersect(const Ray &r) = 0;
};

#endif
