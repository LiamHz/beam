#ifndef HIT_INFO_H
#define HIT_INFO_H

// TODO Implement BSDF class
class BSDF;
// TODO Implement BSSRDF class
class BSSRDF;

struct HitInfo {
    vec3 position;
    vec3 normal;
    BSDF *bsdf = nullptr;
    BSSRDF *bssrdf = nullptr;
};

#endif
