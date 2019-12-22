#include "SDFSphere.h"

double SDFSphere::distance_bound(const Vector3D &pos) const {
    return (pos-center).norm()-r;
}

SDFSphere::SDFSphere(const Vector3D &center, double r): center(center), r(r) {
    bounds = BoundingBox({center[0]-r, center[0]+r}, {center[1]-r, center[1]+r}, {center[2]-r, center[2]+r});
}