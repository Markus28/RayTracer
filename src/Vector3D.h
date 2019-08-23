#ifndef RAYTRACER_VECTOR3D_H
#define RAYTRACER_VECTOR3D_H

#include <iostream>

class Vector3D {
public:
    Vector3D(double x, double y, double z);

    Vector3D();

    double norm() const;

    Vector3D elementWiseMultiplication(const Vector3D& other) const;

    Vector3D elementWisePower(double p) const;

    Vector3D cross(const Vector3D& other) const;

    Vector3D reflectAround(const Vector3D& normal) const;

    Vector3D refractAround(Vector3D normal, double refractive_index) const;

    Vector3D& operator+=(const Vector3D& other);

    Vector3D& operator-=(const Vector3D& other);

    Vector3D operator+(const Vector3D& other) const;

    Vector3D operator-(const Vector3D& other) const;

    Vector3D& operator/=(const double& scalar);

    Vector3D operator/(const double& scalar) const;

    Vector3D operator*(const double& scalar) const;

    Vector3D& operator*=(const double& scalar);

    double operator*(const Vector3D& other) const;

    double& operator[](unsigned int index);

    const double& operator[](unsigned int index) const;

    friend std::ostream& operator<<(std::ostream& sink, const Vector3D& v);

protected:
    double x;
    double y;
    double z;

private:
    std::ostream& print(std::ostream& sink) const;
};


#endif //RAYTRACER_VECTOR3D_H