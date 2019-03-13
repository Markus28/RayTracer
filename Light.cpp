#include "Light.h"

Ray Light::shaddowRay(const Vector3D &pt) const {
    return Ray(pt, getLightDirection(pt));
}