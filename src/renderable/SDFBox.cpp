#include "SDFBox.h"

SDFBox::SDFBox(Vector3D c, double d, double l, double h) {
    depth = d/2;
    length = l/2;
    height = h/2;
    center = c;
    bounds = BoundingBox({c[0]-depth, c[0]+depth}, {c[1]-length, c[1]+length}, {c[2]-depth, c[2]+depth});
}

double SDFBox::distance_bound(const Vector3D &pos) const {
    Vector3D vec = pos-center;

}