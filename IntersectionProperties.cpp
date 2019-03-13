#include "IntersectionProperties.h"

IntersectionProperties::IntersectionProperties(const Vector3D& n, const Material& mat): material(mat) {
    normal = n;
}