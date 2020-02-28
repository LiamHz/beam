#ifndef SAMPLERS_RANDOM_H
#define SAMPLERS_RANDOM_H

#include <vector>
#include <memory>
#include <cstdlib>

#include "core/sampler.h"

class RandomSampler : public Sampler {
public:
    RandomSampler(int _nSamples) : Sampler() {
        nSamples = _nSamples;
    }

    std::vector<std::shared_ptr<Ray> > GetSamples(std::shared_ptr<Camera> camera, int x, int y) {
        std::vector<std::shared_ptr<Ray> > rays;
        for (int i = 0; i < nSamples; i++) {
            float u = float(x + rand()/float(RAND_MAX)) / float(camera->width);
            float v = float(y + rand()/float(RAND_MAX)) / float(camera->height);

            rays.push_back(camera->get_ray(u, v));
        }
        return rays;
    }

    int nSamples;
};

#endif
