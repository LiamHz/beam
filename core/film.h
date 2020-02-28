#ifndef FILM_H
#define FILM_H

#include <vector>
#include <iostream>
#include <fstream>

#include "geometry.h"
using glm::vec3;

#define PI 3.1415926535

class Film {
public:
    Film() {}
    Film(int _filmWidth, int _filmHeight) {
        filmWidth = _filmWidth;
        filmHeight = _filmHeight;
        framebuffer.resize(filmWidth * filmHeight);
    }

    void AddSample(vec3 sample, int x, int y) {
        framebuffer[x + y*filmWidth] = sample;
    }

    // TODO Look into SDL for image display / real time display
    void WriteImage() {
        std::cout << "Writing image to file" << std::endl;
        std::ofstream ofs;
        ofs.open("./out.ppm");
        ofs << "P3\n" << filmWidth << " " << filmHeight << "\n255\n";
        for (int i = 0; i < framebuffer.size(); i++) {
            int r = int(255.99*framebuffer[i].r);
            int g = int(255.99*framebuffer[i].g);
            int b = int(255.99*framebuffer[i].b);
            ofs << r << " " << g << " " << b << "\n";
        }
        ofs.close();
    }

    int filmWidth, filmHeight;
    std::vector<vec3> framebuffer;
};

#endif

