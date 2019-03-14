#include <cmath>
#include "Color.h"

Color::Color(unsigned int red, unsigned int green, unsigned int blue): Vector3D(red, green, blue){}

Color::Color(): Vector3D(){}

void Color::clip()
{
    x = std::fmax(0, std::fmin(x, 255));
    y = std::fmax(0, std::fmin(y, 255));
    z = std::fmax(0, std::fmin(z, 255));
}

Color::Color(const Vector3D& v) {
    x = v[0];
    y = v[1];
    z = v[2];
}

Color Color::elementWiseMult(const Color& other) const {
    return Color(Vector3D({x*other.x, y*other.y, z*other.z}));
}


Color& Color::operator+=(const Color &other) {
    x+=other.x;
    y+=other.y;
    z+=other.z;
    return *this;
}

Color Color::power(double p) const {
    return Color(Vector3D({pow(x, p), pow(y, p), pow(z, p)}));
}