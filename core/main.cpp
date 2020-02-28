#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"

#include "geometry.h"
#include "camera.h"
#include "shape.h"
#include "scene.h"

#include "shapes/sphere.h"

using glm::vec3;

vec3 get_color(const Ray &r, std::vector<std::shared_ptr<Shape> > &scene, float &u, float &v) {
    for (int i = 0; i < scene.size(); i++) {
        if(scene[i] -> Intersect(r)) {
            return vec3(1, 0, 0);
        }
    }
    return vec3(0.1, u, v);
}

int main() {
    int canvas_width = 352;
    int canvas_height = 240;

    std::vector<vec3> framebuffer;
    std::vector<std::shared_ptr<Shape> > scene;
    Camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90, canvas_width / float(canvas_height));
    vec3 color(0, 0, 0);

    Scene scene_shapes("scenes/default.scene");
    scene = scene_shapes.ParseShapes();

    // Send a ray through every pixel
    for (int i = 0; i < canvas_height; i++) {
        fprintf(stderr,"\rRendering (%dx%d) %5.2f%%", canvas_width, canvas_height, double(100.0*((i*canvas_width)/(canvas_height*canvas_width))));
        for (int j = 0; j < canvas_width; j++) {
            float u = j / float(canvas_width);
            float v = i / float(canvas_height);
            Ray r = cam.get_ray(u, v);
            // TODO Rewrite to class based
            color = get_color(r, scene, u, v);
            // TODO Implement gama correction before adding to framebuffer
            framebuffer.push_back(color);
        }
    }
    std::cout << std::endl;

    // Write image to file
    // TODO Look into SDL for image display / real time display
    std::cout << "Writing image to file" << std::endl;
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P3\n" << canvas_width << " " << canvas_height << "\n255\n";
    for (int i = 0; i < framebuffer.size(); i++) {
        int r = int(255.99*framebuffer[i].r);
        int g = int(255.99*framebuffer[i].g);
        int b = int(255.99*framebuffer[i].b);
        ofs << r << " " << g << " " << b << "\n";
    }
    ofs.close();
}
