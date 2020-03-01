#ifndef INTEGRATORS_WHITTED_H
#define INTEGRATORS_WHITTED_H

#include "core/integrator.h"

class Whitted : public SamplerIntegrator {
public:
    Whitted(std::shared_ptr<Camera> _camera,
            std::shared_ptr<Sampler> _sampler,
            int _width, int _height, int _maxDepth)
        : SamplerIntegrator(_camera, _sampler, _width, _height) {
            maxDepth = _maxDepth;
            sampler = _sampler;
        }
    vec3 Li(std::shared_ptr<Ray> ray, std::shared_ptr<Sampler> sampler, Scene &scene);

    int maxDepth;
    std::shared_ptr<Sampler> sampler;
};

#endif
