#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "core/scene.h"
#include "core/shape.h"
#include "shapes/sphere.h"

void ParseSphere(std::ifstream &file, std::vector<std::shared_ptr<Shape> > &shapes);

std::vector<std::shared_ptr<Shape> > Scene::ParseShapes() {
    std::vector<std::shared_ptr<Shape> > shapes;

    std::ifstream file(file_name, std::ifstream::in);
    std::string word;
    while (file >> word) {
        if (word == "Sphere") {
            ParseSphere(file, shapes);
        }

        std::cout << word << std::endl;
    }

    return shapes;
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
