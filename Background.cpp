#include "Background.h"

Background::Background(Color c): map(std::vector<std::vector<Color>>(1, std::vector<Color>(1, c))){}

Background::Background(const SphereMap<Color>& im): map(im) {
}

Color Background::getColor(Vector3D coordinates) {
    return map.get(coordinates);
}