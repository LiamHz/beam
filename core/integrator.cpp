#include <iostream>

#include "core/integrator.h"
#include "core/scene.h"

void SamplerIntegrator::Render(Scene &scene) {
    // Send a ray through every pixel
    for (int y = 0; y < height; y++) {
        fprintf(stderr,"\rRendering (%dx%d) %5.2f%%", width, height, double(100.0*(((y+1)*width)/float(height*width))));
        for (int x = 0; x < width; x++) {
            vec3 color = vec3(0);

            // TODO Implement z-buffer

            // MSAA
            std::vector<std::shared_ptr<Ray> > sampleRays = sampler->GetSamples(camera, x, y);
            for (int i = 0; i < sampleRays.size(); i++) {
                color += Li(sampleRays[i], sampler, scene);
            }

            color /= sampleRays.size();
            camera->film->AddSample(color, x, y);
        }
    }
    std::cout << std::endl;

    camera->film->WriteImage();
}
