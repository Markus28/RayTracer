#include "CSG.h"


CSGComponent *CSGUnion::deep_copy() const {
    return new CSGUnion(first->deep_copy(), second->deep_copy());
}

CSGComponent *CSGIntersection::deep_copy() const {
    return new CSGIntersection(first->deep_copy(), second->deep_copy());
}

CSGComponent *CSGDifference::deep_copy() const {
    return new CSGDifference(first->deep_copy(), second->deep_copy());
}

CSGComponent *CSGLeaf::deep_copy() const {
    return new CSGLeaf(obj);
}


double CSGUnion::distance_bound(const Vector3D &pos) const {
    return std::min(first->distance_bound(pos), second->distance_bound(pos));
}

IntersectionProperties CSGUnion::properties_at(const Vector3D &pos) const {
    if(first->distance_bound(pos)<second->distance_bound(pos))
        return first->properties_at(pos);

    return second->properties_at(pos);
}

double CSGIntersection::distance_bound(const Vector3D &pos) const {
    return std::max(first->distance_bound(pos), second->distance_bound(pos));
}

IntersectionProperties CSGIntersection::properties_at(const Vector3D &pos) const {
    if(first->distance_bound(pos)>second->distance_bound(pos))
        return first->properties_at(pos);

    return second->properties_at(pos);
}

double CSGDifference::distance_bound(const Vector3D &pos) const {
    return std::max(first->distance_bound(pos), -second->distance_bound(pos));
}

IntersectionProperties CSGDifference::properties_at(const Vector3D &pos) const {
    if(first->distance_bound(pos)>-second->distance_bound(pos))
        return first->properties_at(pos);

    IntersectionProperties properties = second->properties_at(pos);
    properties.normal = properties.normal*-1;
    return properties;
}



BoundingBox CSGUnion::get_bounds() const {
    return bounds;
}

BoundingBox CSGIntersection::get_bounds() const {
    return bounds;
}

BoundingBox CSGDifference::get_bounds() const {
    return first->get_bounds();
}

BoundingBox CSGLeaf::get_bounds() const {
    return obj->get_bounds();
}



CSG::CSG(): SDFObject(){
    root = nullptr;
}

CSG::CSG(const CSG& other) {
    if(other.root!=nullptr)
        root = other.root->deep_copy();
    else
        root = nullptr;
}

CSG& CSG::operator=(const CSG& other){
    delete root;

    if(other.root!=nullptr)
        root = other.root->deep_copy();

    else
        root = nullptr;

    return *this;
}

CSG::CSG(SDFObject* obj): SDFObject(){
    root = new CSGLeaf(obj);
}

double CSG::distance_bound(const Vector3D &pos) const {
    return root->distance_bound(pos);
}

BoundingBox CSG::get_bounds() const {
    return root->get_bounds();
}



void CSG::unionize(SDFObject *a) {
    if(root==nullptr){
        root = new CSGLeaf(a);
        return;
    }

    root = new CSGUnion(new CSGLeaf(a), root);
}

void CSG::intersect(SDFObject *a) {
    if(root==nullptr){
        throw "Cannot intersect with empty CSG";
    }

    root = new CSGIntersection(new CSGLeaf(a), root);
}

void CSG::subtract(SDFObject *a) {
    if(root==nullptr){
        throw "Cannot subtract from empty CSG";
    }

    root = new CSGDifference(root, new CSGLeaf(a));
}

void CSG::unionize(const CSG& a) {
    if(root==nullptr){
        if(a.root!=nullptr)
            root = a.root->deep_copy();
        return;
    }

    if(a.root==nullptr)
        return;

    root = new CSGUnion(a.root->deep_copy(), root);
}

void CSG::intersect(const CSG& a) {
    if(root==nullptr || a.root==nullptr){
        delete root;
        root = nullptr;
        return;
    }

    root = new CSGIntersection(a.root->deep_copy(), root);
}

void CSG::subtract(const CSG& a) {
    if(root==nullptr)
        throw "Cannot subtract from empty CSG";

    if(a.root==nullptr)
        return;

    root = new CSGDifference(root, a.root->deep_copy());    //TODO: Should be other way around?
}


CSG::~CSG(){
    delete root;
}