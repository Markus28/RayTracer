#include "SDFBox.h"
#include <algorithm>

SDFBox::SDFBox(Vector3D c, double d, double l, double h, Material mat): mat(mat) {
    depth = d/2;
    length = l/2;
    height = h/2;
    center = c;
    bounds = BoundingBox({c[0]-length, c[0]+length}, {c[1]-depth, c[1]+depth}, {c[2]-height, c[2]+height});
}

double SDFBox::distance_bound(const Vector3D &pos) const {  //TODO: tighter bounds
    Vector3D vec = pos-center;
    return std::max({std::abs(vec[0])-length, std::abs(vec[1])-depth, std::abs(vec[2])-height});
}

IntersectionProperties SDFBox::properties_at(const Vector3D& pos) const{
    Vector3D vec_signed = pos-center;
    Vector3D vec = vec_signed;
    vec[0] = std::abs(std::abs(vec[0])-length);
    vec[1] = std::abs(std::abs(vec[1])-depth);
    vec[2] = std::abs(std::abs(vec[2])-height);

    if(vec[0]< vec[1] && vec[0]<vec[2]){
        if(vec_signed[0]>0)
            return {Vector3D{1,0,0}, mat};
        return {Vector3D{-1,0,0}, mat};
    }

    if(vec[1]< vec[0] && vec[1]<vec[2]){
        if(vec_signed[1]>0)
            return {Vector3D{0,1,0}, mat};
        return {Vector3D{0,-1,0}, mat};
    }

    if(vec_signed[2]>0)
        return {Vector3D(0,0,1), mat};

    return {Vector3D(0,0,-1), mat};
}