#include "Material.h"


Material::Material(const Vector3D& spec_refl, const Vector3D& diff_refl, const Vector3D& ambient_refl, const Vector3D& shininess, Color color,
                   double transparency, double reflectivity, double eta)
{
    this->spec_refl = spec_refl;
    this->diff_refl = diff_refl;
    this->ambient_refl = ambient_refl;
    this->sh = shininess;
    this->color = color;
    this->reflectivity = reflectivity;
    this->transparency = transparency;
    this->eta = eta;
}

Vector3D Material::ambientReflectivity() {
    return ambient_refl;
}

Vector3D Material::diffuseReflectivity() {
    return diff_refl;
}

Vector3D Material::specularReflectivity() {
    return spec_refl;
}

Vector3D Material::shininess() {
    return sh;
}

bool Material::isReflective() {
    return reflectivity!=0;
}

bool Material::isTransparent() {
    return transparency!=0;
}

double Material::getIndex() {
    return eta;
}

double Material::getReflectivity()
{
    return reflectivity;
}

Color Material::getColor()
{
    return color;
}