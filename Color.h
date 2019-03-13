#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include "Vector3D.h"

class Color: public Vector3D {
public:
    Color(unsigned int red, unsigned int green, unsigned int blue);

    Color();

    explicit Color(const Vector3D& v);

    void clip();

    Color power(double p) const;

    Color elementWiseMult(const Color& other) const;

    Color& operator+=(const Color& other);
};


#endif //RAYTRACER_COLOR_H
