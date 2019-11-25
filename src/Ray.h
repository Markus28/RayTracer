#ifndef RAYTRACER_LINE_H
#define RAYTRACER_LINE_H

#include "linalg/Vector3D.h"


class Ray {
public:
    Ray(const Vector3D& pt, const Vector3D& dir);

    const Vector3D& read_direction() const;

    const Vector3D& read_base() const;

    const Vector3D& read_inverse_direction() const;

    void walk(double d);

    void offset(const Vector3D& v);

    friend std::ostream& operator<<(std::ostream& sink, const Ray& ray);

private:
    Vector3D point;
    Vector3D direction;
    Vector3D inverse_direction;

    std::ostream& print(std::ostream& sink) const;
};


#endif //RAYTRACER_LINE_H