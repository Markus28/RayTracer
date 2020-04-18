#include "Background.h"

Background::Background(Vector3D c): map(std::vector<std::vector<Vector3D>>(1, std::vector<Vector3D>(1, c))){}

Background::Background(const SphereMap<Vector3D>& im): map(im) {
}

Vector3D Background::getColor(Vector3D coordinates) {
    return map.get(coordinates);
}