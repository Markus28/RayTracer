#include "SimplePlane.h"
#include "Utilities.h"
#include "Intersection.h"
#include "IntersectionProperties.h"

SimplePlane::SimplePlane(const Vector3D& pt, const Vector3D& norm, const Material& mat) : normal(norm/norm.norm()), material(mat){
    d = normal*pt;
}

std::ostream& SimplePlane::print(std::ostream& sink) const{
    return sink<< "Simple Plane...";
}

bool SimplePlane::onPlane(const Vector3D& pt, const double& epsilon) const {
    return utility::equals_about(normal*pt - d, 0, epsilon);
}

Intersection SimplePlane::rayIntersect(const Ray& ray) const {
    return {this, (d-ray.readBase()*normal)/(normal*ray.readDirection())};
}

IntersectionProperties SimplePlane::intersectProperties(const Ray& ray) const
{
    return {normal, material};
}