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

bool Scene::Intersect(const Ray &r, HitInfo &hit_info) {
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i]->Intersect(r, hit_info))
            return true;
    }
    return false;
}

void Scene::ParseShapes() {
    std::ifstream file(file_name, std::ifstream::in);
    std::string word;
    while (file >> word) {
        if (word == "Sphere") {
            ParseSphere(file, shapes);
        }

        std::cout << word << std::endl;
    }
}

void ParseSphere(std::ifstream &file, std::vector<std::shared_ptr<Shape> > &shapes) {
    std::string word;

    file >> word;
    int posX = std::stoi(word);
    file >> word;
    int posY = std::stoi(word);
    file >> word;
    int posZ = std::stoi(word);
    file >> word;
    float radius = std::stof(word);

    Sphere s(vec3(posX, posY, posZ), radius);
    shapes.push_back(std::make_shared<Sphere> (s));
}
