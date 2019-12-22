#ifndef RAYTRACER_SDFCYLINDER_H
#define RAYTRACER_SDFCYLINDER_H

#include "SDFObject.h"


class SDFCylinder: public SDFObject {
public:

    BoundingBox get_bounds() const override {return bounds;};

private:
    double distance_bound(const Vector3D& pos) const override;
    BoundingBox bounds;
    Vector3D point;
    Vector3D axis;
    double length;
};


#endif //RAYTRACER_SDFCYLINDER_H
