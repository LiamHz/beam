#include "shapes/sphere.h"

bool Sphere::Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info) {
    vec3 oc = r->origin() - position;
    float a = glm::dot(r->direction(), r->direction());
    float b = glm::dot(oc, r->direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;

    nIntersections++;

    if (discriminant > 0) {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if (temp > 0) {
            hit_info.position = r->point_at_parameter(temp);
            hit_info.normal = (hit_info.position - position) / radius;
            return true;
        }
        // Check the other sign of the sqrt
        temp = (-b + sqrt(b*b-a*c))/a;
        if (temp > 0) {
            hit_info.position = r->point_at_parameter(temp);
            hit_info.normal = (hit_info.position - position) / radius;
            return true;
        }
    }
    return false;
}

// TODO Review how this works
Bounds Sphere::GetBounds() {
    // FIX Bounds are too small without being scaled
    float q = 1.2;
    return Bounds(vec3(-radius*q, -radius*q, zMin) + position,
                  vec3( radius*q,  radius*q, zMax) + position);
}
