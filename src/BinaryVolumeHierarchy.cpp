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

    if(left->bv!=nullptr && right->bv!=nullptr)
    {
        return std::min(left->bv->rayIntersect(ray), right->bv->rayIntersect(ray));
        /*
        Interval A = (left->bv->getBounds()).intersectionInterval(ray);
        Interval B = (right->bv->getBounds()).intersectionInterval(ray);
        double a = A.getMin();
        double b = B.getMin();

        if(a<b){
            Intersection first = left->bv->rayIntersect(ray);
            if(first.getDistance()<b && first.doesIntersect()){
                return first;
            }

            return std::min(first, right->bv->rayIntersect(ray));
        }

        Intersection first = right->bv->rayIntersect(ray);
        if(first.getDistance()<a && first.doesIntersect()){
            return first;
        }

        return std::min(first, left->bv->rayIntersect(ray));
         */
    }

    /*
     * We only have to check the following case. If we reach this code, left.bv or right.bv is null.
     * Because of the way the object was initialized, right.bv has to be null. Thus, we only have to check
     * whether left.bv is nullptr.
    */


    if(left->bv!=nullptr)
    {
        return left->bv->rayIntersect(ray);
    }

    return {};
}

BinaryVolumeHierarchy::~BinaryVolumeHierarchy() {
    delete left;
    delete right;
}

std::ostream& BinaryVolumeHierarchy::print(std::ostream &sink) const {
    if(left->bv!= nullptr) {
        sink << left->bv->getBounds() << std::endl;
    }
    if(right->bv!=nullptr) {
        sink << right->bv->getBounds() << std::endl << std::endl;
    }
    return sink;
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
            left = new BVHNode{nullptr, true};
            right = new BVHNode{nullptr, true};
            break;

        case 1:
            left = new BVHNode{*b, true};
            right = new BVHNode{nullptr, true};
            break;

        case 2:
            left = new BVHNode{*b, true};
            right = new BVHNode{*(b + 1), true};
            break;

        default:
            auto division = partition(b, e);
            assert(std::distance(b, division)>=0&&std::distance(division, e)>=0);
            left = new BVHNode{new BinaryVolumeHierarchy(b, division), false};
            right = new BVHNode{new BinaryVolumeHierarchy(division, e), false};
    }
}


IntersectionProperties BinaryVolumeHierarchy::intersectProperties(const Ray& ray) const
{
    assert(false);                                      //DO NOT CALL THIS METHOD! NOT EFFICIENT!
    Intersection intersection = rayIntersect(ray);
    return intersection.getObject()->intersectProperties(ray);
}


BinaryVolumeHierarchy::BinaryVolumeHierarchy(const BinaryVolumeHierarchy& other) {
    this->left = other.left->copy();
    this->right = other.right->copy();
}

BinaryVolumeHierarchy& BinaryVolumeHierarchy::operator=(BinaryVolumeHierarchy other) {
        std::swap(other.left, this->left);
        std::swap(other.left, this->left);
        return *this;
}                           //other contains garbage and is destroyed here...