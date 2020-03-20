#ifndef RAYTRACER_TRANSFORMATION_H
#define RAYTRACER_TRANSFORMATION_H


#include "Matrix3D.h"
#include "../Ray.h"
#include "../Intersection.h"

namespace linalg {
/**
 * @brief Transformation objects represent angle-preserving transformations
 * @details These transformations are modelled as the composition of a translation, a rotation (i.e. orthogonal linear transform)
 * and a scaling step.
 */
    class Transformation {
    public:
        Transformation(): A(), A_transpose(), translation(), scale(1) {};

        Transformation(Matrix3D A, Vector3D v, double s);

        Transformation(Vector3D v, double psi, double theta, double phi, double s);

        void compose_back(const Transformation &b);

        Vector3D transform(const Vector3D &v) const;

        Ray transform(const Ray &ray) const;

        Ray inverse_transform(const Ray &ray) const;

        Intersection transform(const Intersection& intersection) const;

        Intersection inverse_transform(const Intersection& intersection) const;

        IntersectionProperties transform(const IntersectionProperties& properties) const;

        IntersectionProperties inverse_transform(const IntersectionProperties& properties) const;

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
