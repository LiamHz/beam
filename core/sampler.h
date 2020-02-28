#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>

#include "core/camera.h"
#include "core/geometry.h"

class Sampler {
public:
    Sampler () {}
    Sampler(int _nSamples) {
        nSamples = _nSamples;
    }
    virtual ~Sampler() {}
    virtual std::vector<std::shared_ptr<Ray> > GetSamples(std::shared_ptr<Camera> camera, int x, int y) = 0;

    int nSamples;
};

#endif
