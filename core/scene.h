#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>

#include "core/shape.h"
#include "core/light.h"
#include "structs/hitinfo.h"

#include "lights/point.h"

class Scene {
public:
    Scene(std::string f) {
        file_name = f;
    }
    ~Scene() {}
    void ParseFile();
    bool Intersect(std::shared_ptr<Ray> r, HitInfo &hit_info);

    std::string file_name;
    std::vector<std::shared_ptr<Shape> > shapes;
    std::vector<std::shared_ptr<Light> > lights;

private:
    void ParseShape(std::ifstream &file);
    void ParseShapeSphere(std::ifstream &file);

    void ParseLight(std::ifstream &file);
    void ParseLightPoint(std::ifstream &file);
};

#endif
