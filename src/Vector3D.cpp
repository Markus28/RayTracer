#include <cmath>
#include <cassert>
#include "Utilities.h"
#include "Vector3D.h"


Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3D Vector3D::elementWiseMultiplication(const Vector3D& other) const {
    return Vector3D(x*other.x, y*other.y, z*other.z);
}

Vector3D Vector3D::reflectAround(const Vector3D &normal) const {
    assert(utility::equals_about(normal.norm(), 1, utility::EPSILON));
    return *this-normal*(*this*normal)*2;
}

Vector3D Vector3D::refractAround(Vector3D normal, double refractive_index) const {
    assert(utility::equals_about(normal.norm(), 1, utility::EPSILON));
    assert(utility::equals_about(norm(), 1, utility::EPSILON));

    if(normal*(*this)>0)
    {
        refractive_index  = 1/refractive_index;
        normal*=-1;
    }

    if(normal.cross(*this).norm()>(1.0/refractive_index))
    {
        return reflectAround(normal);
    }

    Vector3D result = (*this-normal*(normal*(*this)))*refractive_index - normal*sqrt(1-pow(refractive_index,2)*(1-pow(normal*(*this),2)));
    result /= result.norm();
    assert(utility::equals_about(result.norm(), 1, utility::EPSILON));
    return result;
}

Vector3D Vector3D::cross(const Vector3D &other) const {
    return Vector3D(y*other.z-z*other.y, z*other.x-x*other.z, x*other.y-y*other.x);
}

double Vector3D::norm() const {
    return sqrt(x * x + y * y + z * z);
}


Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &other) const {
    return Vector3D(other.x + x, other.y + y, other.z + z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
    return Vector3D(x-other.x, y-other.y, z-other.z);
}

Vector3D& Vector3D::operator/=(const double& scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3D Vector3D::operator/(const double& scalar) const {
    return Vector3D(x/scalar, y/scalar, z/scalar);
}

Vector3D Vector3D::operator*(const double& scalar) const {
    return Vector3D(x*scalar, y*scalar, z*scalar);
}

Vector3D& Vector3D::operator*=(const double& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

double Vector3D::operator*(const Vector3D& other) const {
    return x*other.x + y*other.y + z*other.z;
}

double& Vector3D::operator[](unsigned int index) {
    switch(index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default: throw("Index out of bounds");
    }
}

const double& Vector3D::operator[](unsigned int index) const {
    switch(index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default: throw("Index out of bounds");
    }
}

std::ostream& Vector3D::print(std::ostream& sink) const {
    sink<< '[' << x <<", " <<y<< ", "<<z<<']';
    return sink;
}

std::ostream& operator<<(std::ostream& sink, const Vector3D& v)
{
    return v.print(sink);
}

Vector3D Vector3D::elementWisePower(double p) const {
    return Vector3D(pow(p,x), pow(p,y), pow(p,z));
}