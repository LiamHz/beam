#include "geometry.h"

// TODO Review how this works
bool Bounds::Intersect(std::shared_ptr<Ray> ray, const vec3 &invDir, const int dirIsNeg[3]) {
    nIntersections++;
    Bounds &bounds = *this;

    // Check for ray intersection against x and y slabs
    float tMin = (bounds[dirIsNeg[0]].x - ray->origin().x) * invDir.x; // Segfault here
    float tMax = (bounds[1 - dirIsNeg[0]].x - ray->origin().x) * invDir.x;
    float tyMin = (bounds[dirIsNeg[1]].y - ray->origin().y) * invDir.y;
    float tyMax = (bounds[1 - dirIsNeg[1]].y - ray->origin().y) * invDir.y;

    // Update tMax and tyMax to ensure robust bounds intersection
    tMax *= 1 + 2 * gamma(3);
    tyMax *= 1 + 2 * gamma(3);
    if (tMin > tyMax || tyMin > tMax) return false;
    if (tyMin > tMin) tMin = tyMin;
    if (tyMax < tMax) tMax = tyMax;

    // Check for ray intersection against z slab
    float tzMin = (bounds[dirIsNeg[2]].z - ray->origin().z) * invDir.z;
    float tzMax = (bounds[1 - dirIsNeg[2]].z - ray->origin().z) * invDir.z;

    // Update tzMax to ensure robust bounds intersection
    tzMax *= 1 + 2 * gamma(3);
    if (tMin > tzMax || tzMin > tMax) return false;
    if (tzMin > tMin) tMin = tzMin;
    if (tzMax < tMax) tMax = tzMax;
    return (tMin < ray->tMax) && (tMax > 0);
};

vec3 Min(const vec3 &p1, const vec3 &p2) {
    return vec3(std::min(p1.x, p2.x),
                std::min(p1.y, p2.y),
                std::min(p1.z, p2.z));
}

vec3 Max(const vec3 &p1, const vec3 &p2) {
    return vec3(std::max(p1.x, p2.x),
                std::max(p1.y, p2.y),
                std::max(p1.z, p2.z));
}

// TODO Review how this works
Bounds Union(const Bounds &b1, const Bounds &b2) {
    Bounds ret;
    ret.pMin = Min(b1.pMin, b2.pMin);
    ret.pMax = Max(b1.pMax, b2.pMax);
    return ret;
}

Bounds Union(const Bounds &b, const vec3 &p) {
    Bounds ret;
    ret.pMin = Min(b.pMin, p);
    ret.pMax = Max(b.pMax, p);
    return ret;
}
