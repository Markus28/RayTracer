#include "Triangle.h"
#include "Utilities.h"
#include "Intersection.h"
#include <cassert>
#include <algorithm>

Triangle::Triangle(Vector3D p1, Vector3D p2, Vector3D p3, Material mat):material(mat){
    interpolate_normal = false;
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

/**
 * @brief Checks whether the point p lies in this triangle
 * @see https://en.wikipedia.org/wiki/Barycentric_coordinate_system
 * @param p Point in 3D-Space
 * @return Whether p lies in this triangle
 */
bool Triangle::inTriangle(Vector3D p) const {
    //assert(onPlane(p, utility::EPSILON));           //TODO: Why is this assert being triggered?

    double alpha, beta, gamma;
    alpha = (p2-p).cross(p3-p).norm();
    beta = (p3-p).cross(p1-p).norm();
    gamma = (p2-p).cross(p1-p).norm();

    return utility::equals_about(alpha+beta+gamma, area2, utility::EPSILON);
}

Intersection Triangle::ray_intersect(const Ray &ray) const {
    Intersection hit = {this, (d- ray.read_base()*normal)/(normal* ray.read_direction())};

    if(!hit.does_intersect())
    {
        return hit;
    }

    Vector3D p = ray.read_base()+ ray.read_direction()* hit.get_distance();

    if(inTriangle(p))
    {
        return hit;
    }

    return {};
}

BoundingBox Triangle::get_bounds() const {
    return bounds;
}

std::ostream& Triangle::print(std::ostream& sink) const{
    return sink<< "Simple Plane...";
}

IntersectionProperties Triangle::intersect_properties(const Ray &ray) const
{
    return {normal, material};
}

void Triangle::enable_interpolation() {
    interpolate_normal = true;
}

void Triangle::disable_interpolation() {
    interpolate_normal = false;
}