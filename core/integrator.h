#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <memory>

#include "core/sampler.h"
#include "core/camera.h"
#include "core/scene.h"

class Integrator {
public:
    Integrator() {}
    virtual ~Integrator() {}
    virtual void Render(Scene &scene) = 0;
};

class SamplerIntegrator : Integrator {
public:
    SamplerIntegrator(std::shared_ptr<Camera> _camera,
                      std::shared_ptr<Sampler> _sampler,
                      int _width, int _height)
                    : Integrator() {
                        camera = _camera;
                        sampler = _sampler;
                        width = _width;
                        height = _height;
                    }

    void Render(Scene &scene);

    int width, height;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sampler> sampler;
};

#endif
