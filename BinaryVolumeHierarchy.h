#ifndef RAYTRACER_BINARYVOLUMEHIERARCHY_H
#define RAYTRACER_BINARYVOLUMEHIERARCHY_H


#include "BoundedVolume.h"
#include <vector>

struct BVHNode{
    BoundedVolume* bv;
    bool is_leaf;
};

class BinaryVolumeHierarchy: public BoundedVolume {
public:
    BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    Intersection rayIntersect(const Ray& ray) const override;
    BoundingBox getBounds() const override;
    std::ostream& print(std::ostream& sink) const override;
    IntersectionProperties intersectProperties(const Ray& ray) const override;
    ~BinaryVolumeHierarchy() override;

private:
    BVHNode left;
    BVHNode right;
    BoundingBox bounds;
    std::vector<BoundedVolume*>::iterator partition(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e);
    unsigned int longestAxis() const;
};


#endif //RAYTRACER_BINARYVOLUMEHIERARCHY_H
