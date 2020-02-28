#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>

#include "core/shape.h"

class Scene {
public:
    Scene(std::string f) { file_name = f; }
    ~Scene() {}
    std::vector<std::shared_ptr<Shape> > ParseShapes();

    std::string file_name;
};

#endif
