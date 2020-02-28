#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>

#include "core/shape.h"
#include "structs/hitinfo.h"

class Scene {
public:
    Scene(std::string f) { file_name = f; }
    ~Scene() {}
    void ParseShapes();
    bool Intersect(const Ray &r, HitInfo &hit_info);

    std::string file_name;

    std::vector<std::shared_ptr<Shape> > shapes;
};

#endif
