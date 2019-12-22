#ifndef RAYTRACER_DISTANCEESTIMATEDSPHERE_H
#define RAYTRACER_DISTANCEESTIMATEDSPHERE_H

#include "SDFObject.h"
#include "../linalg/Vector3D.h"


class SDFSphere: public SDFObject {
public:
    SDFSphere(const Vector3D& center, double r);
    BoundingBox get_bounds() const override {return bounds;};

private:
    Vector3D center;
    BoundingBox bounds;
    double r;
    double distance_bound(const Vector3D& pos) const override;
};


#endif //RAYTRACER_DISTANCEESTIMATEDSPHERE_H
