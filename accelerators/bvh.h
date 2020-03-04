#ifndef ACCELERATORS_BVH_H
#define ACCELERATORS_BVH_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "core/geometry.h"
#include "core/primitive.h"

struct BVHBuildNode;
struct LinearBVHNode;
struct BVHPrimitiveInfo;

class BVHAccel : public Aggregate {
public:
    BVHAccel(std::vector<std::shared_ptr<Primitive>> &p);
    ~BVHAccel() {}
    Bounds GetBounds();
    bool Intersect(std::shared_ptr<Ray> ray, HitInfo &p);

    std::shared_ptr<BVHBuildNode> recursiveBuild(
        std::vector<BVHPrimitiveInfo> &primitiveInfo,
        int start, int end, int &totalNodes,
        std::vector<std::shared_ptr<Primitive>> &orderedPrims
    );

    int flattenBVHTree(std::shared_ptr<BVHBuildNode> node, int *offset);

private:
    std::vector<std::shared_ptr<Primitive>> primitives;
    LinearBVHNode *nodes = nullptr;
};

#endif
