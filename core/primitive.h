#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>

#include "core/shape.h"
#include "core/geometry.h"
#include "structs/hitinfo.h"

// TODO Create material class
class Material {
public:
    Material() {}
    ~Material() {}
};

class Primitive {
public:
    ~Primitive() {}

    virtual Bounds GetBounds() = 0;
    virtual bool Intersect(std::shared_ptr<Ray> ray, HitInfo &p) = 0;
    virtual std::shared_ptr<Material> GetMaterial() = 0;
    virtual void ComputeScatteringFunction(HitInfo &p) = 0;
};

class GeometricPrimitive : public Primitive {
public:
    GeometricPrimitive(std::shared_ptr<Shape> _shape,
                       std::shared_ptr<Material> _material)
                       : shape(_shape), material(_material) {}

    Bounds GetBounds() {
        return shape->GetBounds();
    }
    bool Intersect(std::shared_ptr<Ray> ray, HitInfo &p) {
        return shape->Intersect(ray, p);
    }
    std::shared_ptr<Material> GetMaterial() {
        return material;
    }
    // TODO Implement
    void ComputeScatteringFunction(HitInfo &p) { return; };
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
};

class Aggregate : public Primitive {
public:
    virtual Bounds GetBounds() = 0;
    virtual bool Intersect(std::shared_ptr<Ray> ray, HitInfo &p) = 0;
    std::shared_ptr<Material> GetMaterial() { return nullptr; }
    void ComputeScatteringFunction(HitInfo &p) { return; };
};

#endif
