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

/**
 * @brief Given a point pt, this method checks whether it is reasonable to say that it lies in plane.
 * @note The epsilon is only really meaningful if the plane is in hesse normal form (normed normal).
 * Then epsilon denotes the maximum distance to the plane at which pt would be considered in plane.
 * @param pt The point in question
 * @param epsilon Tolerance for deciding whether or not pt is in plane
 * @return Returns true iff pt is reasonably (epsilon) close to the plane
 */
bool SimplePlane::onPlane(const Vector3D& pt, const double& epsilon) const {
    return utility::equals_about(normal*pt - d, 0, epsilon);
}

Intersection SimplePlane::ray_intersect(const Ray &ray) const {
    return {this, (d- ray.read_base()*normal)/(normal* ray.read_direction())};
}

IntersectionProperties SimplePlane::intersect_properties(const Ray &ray) const
{
    return {normal, material};
}