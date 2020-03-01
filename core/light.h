#ifndef LIGHT_H
#define LIGHT_H

#include "core/geometry.h"
#include "structs/hitinfo.h"

class Light {
public:
    Light(vec3 _position, vec3 _color) {
        position = _position;
        color = _color;
    }
    virtual ~Light() {}
    virtual vec3 SampleLi(const HitInfo &p, vec3 &wi) = 0;

    vec3 position;
    vec3 color;
};

#endif
