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

#include "shapes/sphere.h"
#include "structs/hitinfo.h"

// TODO Add gamma correction to framebuffer
// Implement object color in scene parser
// TODO Implement point lights
// TODO Add BRDF class
// TODO Implement Blinn-Phong BRDF
// TODO Implement MSAA
// TODO Fix fisheye distortion for large camera FOV

int main() {
    int canvas_width = 600;
    int canvas_height = 400;

    std::vector<vec3> framebuffer;
    Film film(canvas_width, canvas_height);
    Camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 20, canvas_width / float(canvas_height));

    Scene scene("scenes/default.scene");
    scene.ParseShapes();

    HitInfo hit_info;
    bool hit;

    // Send a ray through every pixel
    for (int i = 0; i < canvas_height; i++) {
        fprintf(stderr,"\rRendering (%dx%d) %5.2f%%", canvas_width, canvas_height, double(100.0*((i*canvas_width)/(canvas_height*canvas_width))));
        for (int j = 0; j < canvas_width; j++) {
            float u = j / float(canvas_width);
            float v = i / float(canvas_height);
            Ray r = cam.get_ray(u, v);
            hit = scene.Intersect(r, hit_info);

            if (hit)
                film.AddSample(vec3(1, 0, 0) * vec3(hit_info.normal.z), j, i);
            else
                film.AddSample(vec3(0, u, v), j, i);
        }
    }
    std::cout << std::endl;

    // Write image to file
    // TODO Look into SDL for image display / real time display
    film.WriteImage();
}
