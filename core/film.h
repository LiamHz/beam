#ifndef FILM_H
#define FILM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "geometry.h"
using glm::vec3;

#define PI 3.1415926535

class Film {
public:
    Film() {}
    Film(int _filmWidth, int _filmHeight, float _gamma) {
        gamma = _gamma;
        filmWidth = _filmWidth;
        filmHeight = _filmHeight;
        framebuffer.resize(filmWidth * filmHeight);
    }

    void AddSample(vec3 sample, int x, int y) {
        framebuffer[x + y*filmWidth] = sample;
    }

    vec3 GammaCorrect(vec3 pixel, float gamma) {
        return vec3(std::pow(pixel.r, 1.0/gamma),
                    std::pow(pixel.g, 1.0/gamma),
                    std::pow(pixel.b, 1.0/gamma));
    }

    // TODO Look into SDL for image display / real time display
    void WriteImage() {
        std::cout << "Writing image to file" << std::endl;
        vec3 pixel;
        std::ofstream ofs;
        ofs.open("./out.ppm");
        ofs << "P3\n" << filmWidth << " " << filmHeight << "\n255\n";
        for (int i = 0; i < framebuffer.size(); i++) {
            pixel = GammaCorrect(framebuffer[i], gamma);
            int r = int(255.99*pixel.r);
            int g = int(255.99*pixel.g);
            int b = int(255.99*pixel.b);
            ofs << r << " " << g << " " << b << "\n";
        }
        ofs.close();
    }

    float gamma;
    int filmWidth, filmHeight;
    std::vector<vec3> framebuffer;
};

#endif

