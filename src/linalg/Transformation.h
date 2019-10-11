#ifndef RAYTRACER_TRANSFORMATION_H
#define RAYTRACER_TRANSFORMATION_H


#include "Matrix3D.h"
#include "../Ray.h"

namespace linalg {
/**
 * @brief Transformation objects represent angle-preserving transformations
 * @details These transformations are modelled as a composition of a transition, a rotation (i.e. orthogonal linear transform)
 * and a scaling step.
 */
    class Transformation {
    public:
        Transformation(Matrix3D A, Vector3D v, double s);

        Transformation(Vector3D v, double psi, double theta, double phi, double s);

        void compose_back(const Transformation &b);

        Vector3D transform(const Vector3D &v) const;

        Ray transform(const Ray &ray) const;

        Ray inverse_transform(const Ray &ray) const;

        Vector3D inverse_transform(const Vector3D &v) const;

        Vector3D rotate(const Vector3D &v) const;

        Vector3D inverse_rotate(const Vector3D &v) const;

    private:
        Matrix3D A;
        Matrix3D A_transpose;
        Vector3D translation;
        double scale;
    };
}


#endif //RAYTRACER_TRANSFORMATION_H
