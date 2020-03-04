#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "core/light.h"
#include "lights/point.h"
#include "core/primitive.h"

class Scene {
public:
    Scene(std::string f) {
        file_name = f;
    }
    ~Scene() {}
    void ParseFile();
    void CreateAggregate(std::string accelType);
    bool Intersect(std::shared_ptr<Ray> ray, HitInfo &p);

    std::string file_name;
    std::vector<std::shared_ptr<Primitive> > shapes;
    std::vector<std::shared_ptr<Light> > lights;
    std::shared_ptr<Aggregate> aggregate;

private:
    void ParseShape(std::ifstream &file);
    void ParseShapeSphere(std::ifstream &file);

    void ParseLight(std::ifstream &file);
    void ParseLightPoint(std::ifstream &file);
};

#endif
