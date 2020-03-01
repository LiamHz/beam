#include "integrators/whitted.h"

vec3 Whitted::Li(std::shared_ptr<Ray> ray, std::shared_ptr<Sampler> sampler, Scene &scene) {
    vec3 color(0);
    HitInfo hit_info;

    if (scene.Intersect(ray, hit_info))
        color = vec3(1, 0, 0) * vec3(hit_info.normal.z);
    else {
        // Background color
        color = vec3(0, 0.2, 0.3);
    }

    return color;
}
