#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "Vector3D.h"

class MTLLib;

/**
 * @brief Typically stores information about material of RenderObjects
 */
class Material {
public:
    Material(const Vector3D& spec_refl, const Vector3D& diff_refl, const Vector3D& ambient_refl,
            const Vector3D& shininess, double transparency, double reflectivity, double eta);

    Material() = default;
    Vector3D& specular_reflectivity();
    Vector3D& diffuse_reflectivity();
    Vector3D& ambient_reflectivity();
    Vector3D& shininess();
    bool is_reflective() const;
    double get_reflectivity() const;
    double get_transparency() const;
    bool is_transparent() const;
    double get_index() const;
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