#ifndef LIGHTS_POINT_H
#define LIGHTS_POINT_H

#include "core/light.h"

class PointLight : public Light {
public:
    PointLight(vec3 _position, vec3 _color) : Light(_position, _color) {}
    vec3 SampleLi(const HitInfo &p, vec3 &wi) {
        // Cast shadow ray
        wi = glm::normalize(position - p.position);

        // TODO distance always evaluates to inf
        float distance = glm::distance(position, p.position);

        // Return attenuated light
        // return color / (distance*distance);
        return color;
    };
};

#endif
