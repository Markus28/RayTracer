#include "Triangle.h"
#include "Utilities.h"
#include "Intersection.h"
#include <cassert>
#include <algorithm>

Triangle::Triangle(Vector3D p1, Vector3D p2, Vector3D p3, Material mat):material(mat){
    this->normal = (p2-p1).cross(p2-p3)/(p2-p1).cross(p2-p3).norm();
    d = normal*p1;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->area2 = (p2-p1).cross(p3-p1).norm();
    bounds = BoundingBox({utility::min(p1[0], p2[0], p3[0])-2*utility::EPSILON, utility::max(p1[0], p2[0], p3[0])+2*utility::EPSILON},
                         {utility::min(p1[1], p2[1], p3[1])-2*utility::EPSILON, utility::max(p1[1], p2[1], p3[1])+2*utility::EPSILON},
                         {utility::min(p1[2], p2[2], p3[2])-2*utility::EPSILON, utility::max(p1[2], p2[2], p3[2])+2*utility::EPSILON});
}

bool Triangle::inTriangle(Vector3D p) const {
    //assert(onPlane(p, utility::EPSILON));           //TODO: Why is this assert being triggered?

    double alpha, beta, gamma;
    alpha = (p2-p).cross(p3-p).norm();
    beta = (p3-p).cross(p1-p).norm();
    gamma = (p2-p).cross(p1-p).norm();

    if(utility::equals_about(alpha+beta+gamma, area2, utility::EPSILON))
    {
        return true;
    }

    return false;
}

Intersection Triangle::rayIntersect(const Ray &ray) const {
    Intersection hit = {this, (d-ray.readBase()*normal)/(normal*ray.readDirection())};

    if(!hit.doesIntersect())
    {
        return hit;
    }

    Vector3D p = ray.readBase()+ray.readDirection()*hit.getDistance();

    if(inTriangle(p))
    {
        return hit;
    }

    return {};
}

BoundingBox Triangle::getBounds() const {
    return bounds;
}

std::ostream& Triangle::print(std::ostream& sink) const{
    return sink<< "Simple Plane...";
}

IntersectionProperties Triangle::intersectProperties(const Ray& ray) const
{
    return {normal, material};
}