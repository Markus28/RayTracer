#include "SimpleSphere.h"
#include "../Utilities.h"
#include "../Intersection.h"

#include "../IntersectionProperties.h"
#include "../Ray.h"
#include <cassert>
#include <iostream>


SimpleSphere::SimpleSphere(Vector3D center, double radius, Material material): material(material)
{
    this->center = center;
    this->radius = radius;
    bounds = BoundingBox({center[0]-radius, center[0]+radius}, {center[1]-radius, center[1]+radius}, {center[2]-radius, center[2]+radius});
}

std::ostream& SimpleSphere::print(std::ostream& sink) const {
    return sink << "Simple Sphere, R: " <<radius;
}

Intersection SimpleSphere::ray_intersect(const Ray &ray) const {
    assert(utility::equals_about(ray.read_direction().norm(),1 ,utility::EPSILON));
    utility::QuadraticSolution sol;
    double p = (ray.read_base()-center).norm();
    sol = utility::solveQuadraticEquation(1, ray.read_direction()*(ray.read_base()-center)*2.0, p*p-radius*radius);

    if(!sol.exists || (sol.solution1<=0 && sol.solution2<=0))
    {
        return {};
    }

    if(sol.solution2<=0 || (sol.solution1<=sol.solution2 && sol.solution1>=0))
    {
        return {this, sol.solution1};
    }

    return {this, sol.solution2};
}

IntersectionProperties SimpleSphere::intersect_properties(const Ray &ray) const{
    Ray copy = ray;
    copy.walk(ray_intersect(ray).get_distance());
    return {getNormal(copy.read_base()), material};
}

bool SimpleSphere::onSphere(Vector3D pt, double epsilon) const {
    return utility::equals_about((pt-center).norm(), radius, epsilon);
}

Vector3D SimpleSphere::getNormal(Vector3D pt) const {
    assert(onSphere(pt, utility::EPSILON));
    return (pt-center)/radius;
}

BoundingBox SimpleSphere::get_bounds() const{
    return bounds;
}