#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "Vector3D.h"

class MTLLib;

class Material {
public:
    Material(const Vector3D& spec_refl, const Vector3D& diff_refl, const Vector3D& ambient_refl,
            const Vector3D& shininess, double transparency, double reflectivity, double eta);

    Material() = default;
    Vector3D& specularReflectivity();
    Vector3D& diffuseReflectivity();
    Vector3D& ambientReflectivity();
    Vector3D& shininess();
    bool isReflective() const;
    double getReflectivity() const;
    double getTransparency() const;
    bool isTransparent() const;
    double getIndex() const;
    std::ostream& print(std::ostream& sink) const;
    friend std::ostream& operator<<(std::ostream& sink, const Material& mat);
    friend class MTLLib;

private:
    Vector3D spec_refl;
    Vector3D diff_refl;
    Vector3D ambient_refl;
    Vector3D sh;
    double transparency;
    double reflectivity;
    double eta;
};


#endif //RAYTRACER_MATERIAL_H