#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "core/scene.h"
#include "core/shape.h"
#include "shapes/sphere.h"
#include "structs/hitinfo.h"

void ParseSphere(std::ifstream &file, std::vector<std::shared_ptr<Shape> > &shapes);

bool Scene::Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info) {
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i]->Intersect(r, hit_info))
            return true;
    }
    return false;
}

void Scene::ParseFile() {
    std::ifstream file(file_name, std::ifstream::in);
    std::string word;
    while (file >> word) {
        if(word == "Shape") {
            ParseShape(file);
        } else if(word == "Light") {
            ParseLight(file);
        }
    }
}

void Scene::ParseLight(std::ifstream &file) {
    std::string word;
    file >> word;

    if (word == "Point") {
        ParseLightPoint(file);
    }
}

void Scene::ParseLightPoint(std::ifstream &file) {
    std::string word;
    vec3 position;
    vec3 color;

    file >> word;
    position.x = std::stof(word);
    file >> word;
    position.y = std::stof(word);
    file >> word;
    position.z = std::stof(word);

    file >> word;
    color.r = std::stof(word);
    file >> word;
    color.g = std::stof(word);
    file >> word;
    color.b = std::stof(word);

    PointLight l(position, color);
    lights.push_back(std::make_shared<PointLight> (l));
}

void Scene::ParseShape(std::ifstream &file) {
    std::string word;
    file >> word;

    if (word == "Sphere") {
        ParseShapeSphere(file);
    }
}

void Scene::ParseShapeSphere(std::ifstream &file) {
    std::string word;
    vec3 position;

    file >> word;
    position.x = std::stof(word);
    file >> word;
    position.y = std::stof(word);
    file >> word;
    position.z = std::stof(word);
    file >> word;
    float radius = std::stof(word);

    Sphere s(position, radius);
    shapes.push_back(std::make_shared<Sphere> (s));
}
