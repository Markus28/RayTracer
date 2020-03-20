#include <cassert>
#include "Matrix3D.h"


namespace linalg {
/**
 * @brief Constructs the identity matrix
 */
    Matrix3D::Matrix3D() {
        a[0] = 1;
        b[1] = 1;
        c[2] = 1;
    }

    Matrix3D &Matrix3D::operator+=(const Matrix3D &B) {
        a += B.a;
        b += B.b;
        c += B.c;
        return (*this);
    }

    Matrix3D &Matrix3D::operator-=(const Matrix3D &B) {
        a -= B.a;
        b -= B.b;
        c -= B.c;
        return (*this);
    }

    Vector3D operator*(const Matrix3D &A, const Vector3D &v) {
        return A.a * v[0] + A.b * v[1] + A.c * v[2];
    }

    Matrix3D &Matrix3D::operator*=(const Matrix3D &B) {
        Vector3D a_temp = (*this) * B.a;
        Vector3D b_temp = (*this) * B.b;
        c = (*this) * B.c;
        a = a_temp;
        b = b_temp;
        return *this;
    }

    Matrix3D operator*(Matrix3D A, const Matrix3D &B) {
        A *= B;
        return A;
    }

    Matrix3D operator+(Matrix3D A, const Matrix3D &B) {
        A += B;
        return A;
    }

    Matrix3D operator-(Matrix3D A, const Matrix3D &B) {
        A -= B;
        return A;
    }

/**
 * @brief Returns a reference to the entry A[i, j] if the i and j are valid (i.e. 0<=i,j<3)
 * @param i The row
 * @param j The column
 * @return A reference to the entry in row i, column j
 */
    double &Matrix3D::at(unsigned int i, unsigned int j) {
        switch (j) {
            case 0:
                return a[i];
            case 1:
                return b[i];
            case 2:
                return c[i];
            default:
                throw std::out_of_range("j must be such that 0<=j<3");
        }
    }

/**
 * @brief Returns a const reference to the entry A[i, j] if the i and j are valid (i.e. 0<=i,j<3)
 * @param i The row
 * @param j The column
 * @return A const reference to the entry in row i, column j
 */
    const double &Matrix3D::at(unsigned int i, unsigned int j) const {
        switch (j) {
            case 0:
                return a[i];
            case 1:
                return b[i];
            case 2:
                return c[i];
            default:
                throw std::out_of_range("j must be such that 0<=j<3");
        }
    }

/**
 * @brief Returns the transpose of this matrix
 * @return A.T if A is this matrix
 */
    Matrix3D Matrix3D::transpose() const {
        Matrix3D result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.at(i, j) = at(j, i);
            }
        }
        return result;
    }
}