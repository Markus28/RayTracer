#ifndef RAYTRACER_SDFBOX_H
#define RAYTRACER_SDFBOX_H


#include "SDFObject.h"

class SDFBox: public SDFObject {
public:
    SDFBox(Vector3D center, double depth, double length, double height);

private:
    double depth, length, height;
    Vector3D center;
    BoundingBox bounds;

    double distance_bound(const Vector3D& pos) const override;
};


#endif //RAYTRACER_SDFBOX_H
