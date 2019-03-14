#include "BinaryVolumeHierarchy.h"
#include "Utilities.h"
#include "Intersection.h"
#include <algorithm>
#include <cassert>


BoundingBox BinaryVolumeHierarchy::getBounds() const {
    return bounds;
}

Intersection BinaryVolumeHierarchy::rayIntersect(const Ray& ray) const {
    if(!bounds.isIntersected(ray))
    {
        return {};
    }

    if(left.bv!=nullptr && right.bv!=nullptr)
    {
        return std::min(left.bv->rayIntersect(ray), right.bv->rayIntersect(ray));
    }

    /*
     * We only have to check the following case. If we reach this code, left.bv or right.bv is null.
     * Because of the way the object was initialized, right.bv has to be null. Thus, we only have to check
     * whether left.bv is nullptr.
    */


    if(left.bv!=nullptr)
    {
        return left.bv->rayIntersect(ray);
    }

    return {};
}

BinaryVolumeHierarchy::~BinaryVolumeHierarchy() {
    if(!left.is_leaf)
    {
        delete left.bv;
    }

    if(!right.is_leaf)
    {
        delete right.bv;
    }
}

std::ostream& BinaryVolumeHierarchy::print(std::ostream &sink) const {
    return sink<< "Binary Volume Hierarchy";
}

unsigned int BinaryVolumeHierarchy::longestAxis() const{
    if(bounds[0].length()>bounds[1].length() && bounds[0].length()>bounds[2].length())
    {
        return 0;
    }

    if(bounds[1].length()>bounds[2].length())
    {
        return 1;
    }

    return 2;
}

std::vector<BoundedVolume*>::iterator BinaryVolumeHierarchy::partition(std::vector<BoundedVolume *>::iterator b, std::vector<BoundedVolume *>::iterator e) {
    unsigned int longest_index = longestAxis();

    std::function<bool(BoundedVolume*, BoundedVolume*)> lambda = [longest_index](BoundedVolume* a, BoundedVolume* b)->bool
    {
        return (*a).getBounds().getCenter()[longest_index]<(*b).getBounds().getCenter()[longest_index];
    };

    return utility::split_middle(b, e, lambda);
}

BinaryVolumeHierarchy::BinaryVolumeHierarchy(std::vector<BoundedVolume*>::iterator b, std::vector<BoundedVolume*>::iterator e)
{
    bounds = utility::sumBoundingBoxes(b, e);

    switch(std::distance(b,e))
    {
        case 0:
            left = BVHNode{nullptr, true};
            right = BVHNode{nullptr, true};
            break;

        case 1:
            left = BVHNode{*b, true};
            right = BVHNode{nullptr, true};
            break;

        case 2:
            left = BVHNode{*b, true};
            right = BVHNode{*(b + 1), true};
            break;

        default:
            auto division = partition(b, e);
            assert(std::distance(b, division)>=0&&std::distance(division, e)>=0);
            left = {new BinaryVolumeHierarchy(b, division), false};
            right = {new BinaryVolumeHierarchy(division, e), false};
    }
}


IntersectionProperties BinaryVolumeHierarchy::intersectProperties(const Ray& ray) const
{
    assert(false);                                      //DO NOT CALL THIS METHOD! IT IS NOT EFFICIENT!
    Intersection intersection = rayIntersect(ray);
    return intersection.getObject()->intersectProperties(ray);
}