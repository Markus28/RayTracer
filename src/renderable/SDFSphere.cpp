#include "SDFSphere.h"

double SDFSphere::distance_bound(const Vector3D &pos) const {
    return (pos-center).norm()-r;
}

IntersectionProperties SDFSphere::properties_at(const Vector3D &pos) const {
    Vector3D r = pos-center;
    r /= r.norm();
    return IntersectionProperties{r, mat};
}

SDFSphere::SDFSphere(const Vector3D &center, double r, Material mat): center(center), r(r), mat(mat) {
    bounds = BoundingBox({center[0]-r, center[0]+r}, {center[1]-r, center[1]+r}, {center[2]-r, center[2]+r});
}