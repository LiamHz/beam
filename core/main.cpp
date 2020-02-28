#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
using glm::vec3;

#include "core/geometry.h"
#include "core/camera.h"
#include "core/shape.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/integrator.h"

#include "shapes/sphere.h"
#include "structs/hitinfo.h"
#include "samplers/random.h"

// Implement object color in scene parser
// TODO Implement point lights
// TODO Add BRDF class
// TODO Implement Blinn-Phong BRDF
// TODO Fix fisheye distortion for large camera FOV

int main() {
    int width = 600;
    int height = 400;
    float gamma = 2;

    Camera c(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 20, width, height, gamma);
    std::shared_ptr<Camera> camera = std::make_shared<Camera> (c);

    int nSamples = 10;
    RandomSampler s(nSamples);
    std::shared_ptr<RandomSampler> randomSampler = std::make_shared<RandomSampler> (s);

    Scene scene("scenes/default.scene");
    scene.ParseShapes();

    SamplerIntegrator sampler_integrator(camera, randomSampler, width, height);

    sampler_integrator.Render(scene);
}
