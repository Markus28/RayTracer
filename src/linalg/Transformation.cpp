#include <cmath>
#include "Transformation.h"

namespace linalg {
/**
 * @brief Construct Transformation from Orthogonal Matrix A, translation and scaling-factor
 * @param A Orthogonal Matrix describing rotation
 * @param v Translation
 * @param s Scaling Factor
 */
    Transformation::Transformation(Matrix3D A, Vector3D v, double s) : A(A), translation(v), scale(s) {
        A_transpose = A.transpose();
    }

/**
 * @brief Construct the Transformation from euler angles, translation and scaling-factor
 * @param v The translation
 * @param psi Euler angle 1
 * @param theta Euler angle 2
 * @param phi Euler angle 3
 * @param s Scaling Factor
 */
    Transformation::Transformation(Vector3D v, double psi, double theta, double phi, double s) : translation(v),
                                                                                                 scale(s) {
        Matrix3D R1, R2, R3;

        R1.at(0, 0) = cos(psi);
        R1.at(1, 1) = cos(psi);
        R1.at(0, 1) = -sin(psi);
        R1.at(1, 0) = sin(psi);

        R2.at(0, 0) = cos(theta);
        R2.at(2, 2) = cos(theta);
        R2.at(0, 2) = -sin(theta);
        R2.at(2, 0) = sin(theta);

        R3.at(1, 1) = cos(phi);
        R3.at(2, 2) = cos(phi);
        R3.at(1, 2) = -sin(phi);
        R3.at(2, 1) = sin(phi);

        A = R1 * R2 * R3;
        A_transpose = A.transpose();
    }


/**
 * @brief Compose this transformation with b
 * @details From now on b will be applied first, the the original transformation.
 * @param b Other transformation
 */
    void Transformation::compose_back(const Transformation &b) {
        scale *= b.scale;
        translation += A * b.translation;
        A *= b.A;
        A_transpose = A.transpose();
    }

/**
 * @brief Apply this transformation to v in 3D space
 * @param v The vector that is supposed to be transformed
 * @return The transformed vector
 */
    Vector3D Transformation::transform(const Vector3D &v) const {
        return A * (v * scale) + translation;
    }

/**
 * @brief The inverse to Transformation::transform
 * @param v The vector that is supposed to be transformed
 * @return The transformed vector
 */
    Vector3D Transformation::inverse_transform(const Vector3D &v) const {
        return A_transpose * ((v - translation) / scale);
    }

    Ray Transformation::transform(const Ray &ray) const {
        return {transform(ray.readBase()), A * ray.readBase()};
    }

    Ray Transformation::inverse_transform(const Ray &ray) const {
        return {inverse_transform(ray.readBase()), A_transpose * ray.readDirection()};
    }

    Vector3D Transformation::rotate(const Vector3D &v) const {
        return A * v;
    }

    Vector3D Transformation::inverse_rotate(const Vector3D &v) const {
        return A_transpose * v;
    }
}