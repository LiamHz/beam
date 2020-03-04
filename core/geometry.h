#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <limits>
#include <memory>
#include <iostream>
#include <algorithm>
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
using glm::vec3;
using glm::vec2;

extern int nIntersections;

inline float gamma(int n) {
    float epsilon = std::numeric_limits<float>::epsilon() * 0.5;
    return (n * epsilon) / (1 - n * epsilon);
}

class Ray {
public:
    Ray() {}
    Ray(const vec3 &_o, const vec3 &_d, float _t = 0.0) {
        o = _o;
        d = _d;
        t = _t;
        tMax = std::numeric_limits<float>::max();
    }

    vec3 origin() const     { return o; }
    vec3 direction() const  { return d; }
    float time() const      { return t; }
    vec3 point_at_parameter(float t) const { return o + t*d; }

    vec3 o, d;
    float t;
    float tMax;
};

class Bounds {
public:
    Bounds() {
        auto minNum = std::numeric_limits<float>::lowest();
        auto maxNum = std::numeric_limits<float>::max();
        pMin = vec3(maxNum, maxNum, maxNum);
        pMax = vec3(minNum, minNum, minNum);
    }
    Bounds(const vec3 &p1, const vec3 &p2)
        : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
          pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}
    ~Bounds() {}

    bool Intersect(std::shared_ptr<Ray> ray, const vec3 &invDir, const int dirIsNeg[3]);

    const vec3 Diagonal() { return pMax - pMin; }

    // TODO Review how this works
    int MaximumExtent() {
        vec3 d = Diagonal();
        if (d.x > d.y && d.x > d.z)
            return 0;
        else if (d.y > d.z)
            return 1;
        else
            return 2;
    }

    vec3 operator[](int i) {
        return (i == 0) ? pMin : pMax;
    }

    vec3 pMin, pMax;
};

// Bounds operators
vec3 Min(const vec3 &p1, const vec3 &p2);
vec3 Max(const vec3 &p1, const vec3 &p2);
Bounds Union(const Bounds &b1, const Bounds &b2);
Bounds Union(const Bounds &b, const vec3 &p);

#endif
