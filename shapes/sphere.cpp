#include "sphere.h"
#include "core/geometry.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
using glm::vec3;

bool Sphere::Intersect(const Ray &r) {
    vec3 oc = r.origin() - center;
    float a = glm::dot(r.direction(), r.direction());
    float b = glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;

    return discriminant > 0;
}
