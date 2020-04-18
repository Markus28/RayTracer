#ifndef RAYTRACER_DISTANCEESTIMATEDSPHERE_H
#define RAYTRACER_DISTANCEESTIMATEDSPHERE_H

#include "SDFObject.h"
#include "../linalg/Vector3D.h"


class SDFSphere: public SDFObject {
public:
    SDFSphere(const Vector3D& center, double r, Material material);
    BoundingBox get_bounds() const override {return bounds;};

private:
    IntersectionProperties properties_at(const Vector3D& pos) const override;

    Material mat;
    Vector3D center;
    BoundingBox bounds;
    double r;
    double distance_bound(const Vector3D& pos) const override;
};


#endif //RAYTRACER_DISTANCEESTIMATEDSPHERE_H
