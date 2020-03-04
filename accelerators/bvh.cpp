#include "accelerators/bvh.h"

#include <chrono>
#include <thread>

struct BVHPrimitiveInfo {
    BVHPrimitiveInfo() {}
    BVHPrimitiveInfo(int _primitiveNumber, Bounds _bounds)
      : primitiveNumber(_primitiveNumber),
        bounds(_bounds),
        centroid(0.5f * bounds.pMin + 0.5f * bounds.pMax) {}

    int primitiveNumber;
    Bounds bounds;
    vec3 centroid;
};

struct BVHBuildNode {
    BVHBuildNode() {
        children.resize(2);
    }

    void InitLeaf(int first, int n, const Bounds _bounds) {
        firstPrimOffset = first;
        nPrimitives = n;
        bounds = _bounds;
        children[0] = nullptr;
        children[1] = nullptr;
    }

    void InitInterior(
        int axis,
        std::shared_ptr<BVHBuildNode> c0,
        std::shared_ptr<BVHBuildNode> c1
    ) {
        children[0] = c0;
        children[1] = c1;
        bounds = Union(c0->bounds, c1->bounds);
        splitAxis = axis;
        nPrimitives = 0;
    }

    Bounds bounds;
    std::vector<std::shared_ptr<BVHBuildNode>> children;
    int splitAxis, firstPrimOffset, nPrimitives;
};

struct LinearBVHNode {
    Bounds bounds;
    union {
        int primitivesOffset;   // Leaf
        int secondChildOffset;  // Interior
    };
    uint16_t nPrimitives;
    uint8_t axis;
    uint8_t pad[1];
};

Bounds BVHAccel::GetBounds() {
    return nodes ? nodes[0].bounds : Bounds();
}

std::shared_ptr<BVHBuildNode> BVHAccel::recursiveBuild(
        std::vector<BVHPrimitiveInfo> &primitiveInfo,
        int start, int end, int &totalNodes,
        std::vector<std::shared_ptr<Primitive>> &orderedPrims
    ) {

    BVHBuildNode n = BVHBuildNode();
    auto node = std::make_shared<BVHBuildNode> (n);
    totalNodes++;

    // Compute bounds of all primitives in BVH node
    Bounds bounds;
    for (int i = start; i < end; i++)
        bounds = Union(bounds, primitiveInfo[i].bounds);

    int nPrimitives = end - start;

    if (nPrimitives == 1) {
        // Create leaf
        int firstPrimOffset = orderedPrims.size();
        for (int i = start; i < end; i++) {
            int primNum = primitiveInfo[i].primitiveNumber;
            orderedPrims.push_back(primitives[primNum]);
        }
        node->InitLeaf(firstPrimOffset, nPrimitives, bounds);
        return node;
    } else {
        // Compute bound of primitive centroids, choose split dimension dim
        Bounds centroidBounds;
        for (int i = start; i < end; i++)
            centroidBounds = Union(centroidBounds, primitiveInfo[i].centroid);
        int dim = centroidBounds.MaximumExtent();

        // TODO Implement SAH (more performant paritioning algotihm)
        // Partition primitives into two sets and build children
        int mid = (start + end) / 2;
        if (centroidBounds.pMax[dim] == centroidBounds.pMin[dim]) {
            // Create leaf _BVHBuildNode_
            int firstPrimOffset = orderedPrims.size();
            for (int i = start; i < end; ++i) {
                int primNum = primitiveInfo[i].primitiveNumber;
                orderedPrims.push_back(primitives[primNum]);
            }
            node->InitLeaf(firstPrimOffset, nPrimitives, bounds);
            return node;
        } else {
            float pmid = (centroidBounds.pMin[dim] + centroidBounds.pMax[dim]) / 2;
            BVHPrimitiveInfo *midPtr = std::partition(
                &primitiveInfo[start],
                &primitiveInfo[end-1]+1,
                [dim, pmid](BVHPrimitiveInfo &pi) {
                    return pi.centroid[dim] < pmid;
                }
            );
            mid = midPtr - &primitiveInfo[0];

            node->InitInterior(
                dim,
                recursiveBuild(primitiveInfo, start, mid, totalNodes, orderedPrims),
                recursiveBuild(primitiveInfo, mid, end, totalNodes, orderedPrims)
            );
        }
    }

    return node;
}

// int BVHAccel::flattenBVHTree(BVHBuildNode *node, int *offset) {
int BVHAccel::flattenBVHTree(std::shared_ptr<BVHBuildNode> node, int *offset) {
    LinearBVHNode *linearNode = &nodes[*offset];

    linearNode->bounds = node->bounds;
    int myOffset = (*offset)++;

    if (node->nPrimitives > 0) {
        linearNode->primitivesOffset = node->firstPrimOffset;
        linearNode->nPrimitives = node->nPrimitives;
    } else {
        // Create interior flattened BVH node
        linearNode->axis = node->splitAxis;
        linearNode->nPrimitives = 0;
        flattenBVHTree(node->children[0], offset);
        linearNode->secondChildOffset = flattenBVHTree(node->children[1], offset);
    }
    return myOffset;
}

bool BVHAccel::Intersect(std::shared_ptr<Ray> ray, HitInfo &p) {
    bool hit = false;
    vec3 invDir(1/ray->direction().x, 1/ray->direction().y, 1/ray->direction().z);
    int dirIsNeg[3] = { invDir.x < 0, invDir.y < 0, invDir.z < 0 };

    // Follow ray through BVH nodes to find primitive intersections
    int toVisitOffset = 0;
    int currentNodeIndex = 0;
    int nodesToVisit[64];
    while (true) {
        LinearBVHNode *node = &nodes[currentNodeIndex];
        // Check ray against BVH node
        if (node->bounds.Intersect(ray, invDir, dirIsNeg)) {
            if (node->nPrimitives > 0) {
                // Intersect ray with primitives in leaf BVH node
                for (int i = 0; i < node->nPrimitives; i++)
                    if (primitives[node->primitivesOffset + i]->Intersect(ray, p))
                        hit = true;
                if (toVisitOffset == 0)
                    break;
                currentNodeIndex = nodesToVisit[--toVisitOffset];
            } else {
                // Put far BVH node on nodesToVisit stack, advance to near node
                if (dirIsNeg[node->axis]) {
                    nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
                    currentNodeIndex = node->secondChildOffset;
                } else {
                    nodesToVisit[toVisitOffset++] = node->secondChildOffset;
                    currentNodeIndex = currentNodeIndex + 1;
                }
            }
        } else {
            if (toVisitOffset == 0)
                break;
            currentNodeIndex = nodesToVisit[--toVisitOffset];
        }
    }

    return hit;
}

BVHAccel::BVHAccel(std::vector<std::shared_ptr<Primitive>> &p) : primitives(p) {
    if (primitives.size() == 0)
        return;

    // Initialize primitiveInfo array for primitives
    std::vector<BVHPrimitiveInfo> primitiveInfo(primitives.size());
    for (int i = 0; i < primitives.size(); i++)
       primitiveInfo[i] = { i, primitives[i]->GetBounds() };

    // Build BVH tree for primitives using primitiveInfo
    int totalNodes = 0;
    std::vector<std::shared_ptr<Primitive>> orderedPrims;
    orderedPrims.reserve(primitives.size());

    // Compute representation of depth-first traversal of BVH tree
    BVHBuildNode r;
    auto root = std::make_shared<BVHBuildNode> (r);
    root = recursiveBuild(primitiveInfo, 0, primitives.size(), totalNodes, orderedPrims);

    primitives.swap(orderedPrims);
    primitiveInfo.resize(0);

    std::cout << "totalNodes: " << totalNodes << std::endl;
    nodes = (struct LinearBVHNode*) malloc(sizeof(LinearBVHNode) * totalNodes);

    int offset = 0;
    flattenBVHTree(root, &offset);
}

