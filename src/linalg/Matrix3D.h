#ifndef RAYTRACER_MATRIX3D_H
#define RAYTRACER_MATRIX3D_H


#include "../Vector3D.h"

namespace linalg {
/**
 * @brief Square 3x3 Matrix
 */
    class Matrix3D {
    public:
        Matrix3D();

        Matrix3D(const Vector3D &a, const Vector3D &b, const Vector3D &c) : a(a), b(b), c(c) {};

        double &at(unsigned int i, unsigned int j);

        const double &at(unsigned int i, unsigned int j) const;

        Matrix3D transpose() const;

        Matrix3D &operator*=(const Matrix3D &B);

        Matrix3D &operator+=(const Matrix3D &B);

        friend Vector3D operator*(const Matrix3D &A, const Vector3D &v);

        friend Matrix3D operator*(Matrix3D A, const Matrix3D &B);

        friend Matrix3D operator+(Matrix3D A, const Matrix3D &B);

    private:
        /// The columns of the Matrix [a, b, c]
        Vector3D a, b, c;
    };
}


#endif //RAYTRACER_MATRIX3D_H
