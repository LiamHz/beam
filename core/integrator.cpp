#include <iostream>

#include "core/integrator.h"
#include "core/scene.h"

void SamplerIntegrator::Render(Scene &scene) {
    bool hit;
    HitInfo hit_info;

    // Send a ray through every pixel
    for (int y = 0; y < height; y++) {
        fprintf(stderr,"\rRendering (%dx%d) %5.2f%%", width, height, double(100.0*(((y+1)*width)/float(height*width))));
        for (int x = 0; x < width; x++) {
            vec3 color = vec3(0);

            std::vector<std::shared_ptr<Ray> > sampleRays = sampler->GetSamples(camera, x, y);

            for (int i = 0; i < sampleRays.size(); i++) {
                hit = scene.Intersect(sampleRays[i], hit_info);
                if (hit)
                    color += vec3(1, 0, 0) * vec3(hit_info.normal.z);
                else {
                    // Background color
                    color += vec3(0, y/float(height), x/float(width));
                }
            }

            color /= sampleRays.size();
            camera->film->AddSample(color, x, y);
        }
    }
    std::cout << std::endl;

    // TODO Look into SDL for image display / real time display
    camera->film->WriteImage();
}
