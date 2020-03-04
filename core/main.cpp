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
#include "integrators/whitted.h"

// Global performance trackers
int nIntersections = 0;

int main() {
    // Config
    int width = 600;
    int height = 400;
    float gamma = 1.8;
    int nSamples = 1;
    std::string accelType = "bvh";

    Camera c(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 20, width, height, gamma);
    std::shared_ptr<Camera> camera = std::make_shared<Camera> (c);

    RandomSampler s(nSamples);
    std::shared_ptr<RandomSampler> randomSampler = std::make_shared<RandomSampler> (s);

    Scene scene("scenes/default.scene");
    scene.ParseFile();
    scene.CreateAggregate(accelType);

    Whitted whitted_integrator(camera, randomSampler, width, height, 3);
    whitted_integrator.Render(scene);

    // Performance logging
    std::cout << "nIntersections: " << nIntersections << std::endl;
}
