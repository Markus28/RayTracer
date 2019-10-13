#ifndef RAYTRACER_BINARYVOLUMEHIERARCHY_H
#define RAYTRACER_BINARYVOLUMEHIERARCHY_H


#include "BoundedVolume.h"
#include <vector>

struct BVHNode;

/**
 * @brief Acceleration structure for ensemble of bounded volumes
 */
class BinaryVolumeHierarchy: public BoundedVolume {
public:
    BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    BinaryVolumeHierarchy(const BinaryVolumeHierarchy& other);
    BinaryVolumeHierarchy& operator=(BinaryVolumeHierarchy other);
    Intersection ray_intersect(const Ray &ray) const override;
    BoundingBox get_bounds() const override;
    std::ostream& print(std::ostream& sink) const override;
    IntersectionProperties intersect_properties(const Ray &ray) const override;
    ~BinaryVolumeHierarchy() override;

private:
    BVHNode* left;
    BVHNode* right;
    BoundingBox bounds;
    std::vector<BoundedVolume*>::iterator partition(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    unsigned int longestAxis() const;
};

struct BVHNode{
    BoundedVolume* bv;
    bool is_leaf;

    BVHNode* copy() const
    {
        if(is_leaf)
        {
            return new BVHNode{bv, is_leaf};
        }

        return new BVHNode{new BinaryVolumeHierarchy(*dynamic_cast<BinaryVolumeHierarchy*>(bv)), is_leaf};
    }

    ~BVHNode()
    {
        if(!is_leaf)
        {
            delete bv;
        }
    }
};


#endif //RAYTRACER_BINARYVOLUMEHIERARCHY_H
