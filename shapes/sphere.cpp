#include <memory>

#include "shapes/sphere.h"
#include "core/geometry.h"
#include "structs/hitinfo.h"

bool Sphere::Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info) {
    vec3 oc = r->origin() - center;
    float a = glm::dot(r->direction(), r->direction());
    float b = glm::dot(oc, r->direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(b*b-a*c))/a;
        // TODO review how normal calculation works for spheres
        if (temp > 0) {
            hit_info.position = r->point_at_parameter(temp);
            hit_info.normal = (hit_info.position - center) / radius;
            return true;
        }
        // Check the other sign of the sqrt
        temp = (-b + sqrt(b*b-a*c))/a;
        if (temp > 0) {
            hit_info.position = r->point_at_parameter(temp);
            hit_info.normal = (hit_info.position - center) / radius;
            return true;
        }
    }
    return false;
}
