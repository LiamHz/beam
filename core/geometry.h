#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
using glm::vec3;

class Ray {
public:
    Ray() {}
    Ray(const vec3 &_o, const vec3 &_d, float _t = 0.0) {
        o = _o;
        d = _d;
        t = _t;
    }

    vec3 origin() const     { return o; }
    vec3 direction() const  { return d; }
    float time() const      { return t; }
    vec3 point_at_parameter(float t) const { return o + t*d; }

    vec3 o, d;
    float t;
};

#endif
