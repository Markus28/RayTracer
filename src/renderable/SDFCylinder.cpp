#include "SDFCylinder.h"
#include <cmath>


SDFCylinder::SDFCylinder(Vector3D center, Vector3D axis, double length, double radius, Material mat):
center(center), axis(axis/axis.norm()), length(length), radius(radius), mat(mat){
    bounds = BoundingBox({center[0]-length-radius, center[0]+length+radius},
            {center[1]-length-radius, center[1]+length+radius},
            {center[2]-length-radius, center[2]+length+radius}); //TODO: Make bounds tighter
}

double SDFCylinder::distance_bound(const Vector3D &pos) const {
    Vector3D vec = pos-center;
    double coord_along_axis = axis*vec;
    double distance_from_mantle = std::sqrt(std::pow(vec.norm(),2) - std::pow(coord_along_axis,2))-radius;

    if(std::abs(coord_along_axis)<=length)      //In this case we are somewhere in the middle of the cylinder
        return distance_from_mantle;

    // Otherwise the closest point is either on an edge or a cap
    return std::max(std::abs(coord_along_axis)-length, distance_from_mantle);
}

IntersectionProperties SDFCylinder::properties_at(const Vector3D& pos) const{
    Vector3D vec = pos-center;
    double coord_along_axis = axis*vec;
    double distance_from_mantle = std::sqrt(std::pow(vec.norm(),2) - std::pow(coord_along_axis,2))-radius;

    if(std::abs(coord_along_axis)<=length) {      //In this case we are somewhere in the middle of the cylinder
        Vector3D point_on_axis = center+axis*coord_along_axis;
        Vector3D normal = pos-point_on_axis;
        normal/=normal.norm();
        return {normal, mat};
    }

    // Otherwise the closest point is either on an edge or a cap
    if(coord_along_axis>0)
        return {axis, mat};
    return {axis*(-1.0), mat};
}