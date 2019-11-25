#ifndef RAYTRACER_BINARYVOLUMEHIERARCHY_H
#define RAYTRACER_BINARYVOLUMEHIERARCHY_H


#include "BoundedVolume.h"
#include <vector>

struct BVHConstructionNode{
    union ConstructionChildren{
        std::pair<BVHConstructionNode*, BVHConstructionNode*> children_nodes;
        BoundedVolume* leaf;
    };
    ConstructionChildren children;
    unsigned int total_children;
    BoundingBox my_box;
    ~BVHConstructionNode(){
        if(total_children!=0){
            delete children.children_nodes.first;
            delete children.children_nodes.second;
        }
    }
};

struct BVHLinearNode{
    union LinearSecondChild{
        BoundedVolume* primitive;
        unsigned int second_child_offset;
    };

    LinearSecondChild child;
    BoundingBox my_box;
    bool contains_leaf;

    ~BVHLinearNode()=default;
};

/**
 * @brief Acceleration structure for ensemble of bounded volumes
 */
class BinaryVolumeHierarchy: public BoundedVolume {
public:
    BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    Intersection ray_intersect(const Ray &ray) const override;
    BoundingBox get_bounds() const override;
    std::ostream& print(std::ostream& sink) const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    ~BinaryVolumeHierarchy() override;

private:
    BVHLinearNode* nodes = nullptr;
    BVHConstructionNode* build_tree(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    unsigned int flatten_tree(BVHConstructionNode* root, BVHLinearNode* nodes);
    std::vector<BoundedVolume*>::iterator partition(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
};

#endif //RAYTRACER_BINARYVOLUMEHIERARCHY_H