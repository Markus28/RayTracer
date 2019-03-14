#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "Vector3D.h"
#include "Color.h"

class Material {
public:
    Material(const Vector3D& spec_refl, const Vector3D& diff_refl, const Vector3D& ambient_refl,
            const Vector3D& shininess, Color color, double transparency, double reflectivity, double eta);

    Vector3D specularReflectivity();

    Vector3D diffuseReflectivity();

    Vector3D ambientReflectivity();

    Vector3D shininess();

    Color getColor();

    bool isReflective();

    double getReflectivity();

    bool isTransparent();

    double getIndex();

private:
    Vector3D spec_refl;
    Vector3D diff_refl;
    Vector3D ambient_refl;
    Vector3D sh;
    Color color;
    double transparency;
    double reflectivity;
    double eta;
};


#endif //RAYTRACER_MATERIAL_H