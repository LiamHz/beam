#ifndef CAMERA_H
#define CAMERA_H

#include "core/geometry.h"
#include "core/film.h"

#define PI 3.1415926535

class Camera {
public:
    Camera() {}
    // TODO Review how this works
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, int _width, int _height, float gamma) {
        width = _width;
        height = _height;

        float aspect = width / float(height);
        float theta = vfov * PI/180;
        float half_height = glm::tan(theta/2);
        float half_width = aspect * half_height;

        // Location and orientation
        origin = lookfrom;
        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(glm::cross(vup, w));
        v = glm::cross(w, u);

        // Dimensions
        lower_left_corner = origin - half_width*u - half_height*v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;

        Film f(width, height, gamma);
        film = std::make_shared<Film> (f);
    }

    // TODO Review how this works
    std::shared_ptr<Ray> get_ray(float s, float t) {
        Ray r(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        return std::make_shared<Ray> (r);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    int width, height;
    std::shared_ptr<Film> film;
};

#endif
