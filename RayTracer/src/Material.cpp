#include "Material.h"


Material::Material(const Vector3D& spec_refl, const Vector3D& diff_refl, const Vector3D& ambient_refl, const Vector3D& shininess,
                   double transparency, double reflectivity, double eta) {
    this->spec_refl = spec_refl;
    this->diff_refl = diff_refl;
    this->ambient_refl = ambient_refl;
    this->sh = shininess;
    this->reflectivity = reflectivity;
    this->transparency = transparency;
    this->eta = eta;
}

Vector3D& Material::ambient_reflectivity() {
    return ambient_refl;
}

Vector3D& Material::diffuse_reflectivity() {
    return diff_refl;
}

Vector3D& Material::specular_reflectivity() {
    return spec_refl;
}

Vector3D& Material::shininess() {
    return sh;
}

bool Material::is_reflective() const {
    return reflectivity!=0;
}

bool Material::is_transparent() const {
    return transparency!=0;
}

double Material::get_index()const {
    return eta;
}

double Material::get_reflectivity() const
{
    return reflectivity;
}

double Material::get_transparency() const {
    return transparency;
}


std::ostream& Material::print(std::ostream& sink) const{
    sink<<"Ka: "<<ambient_refl<<std::endl;
    sink<<"Kd: "<<diff_refl<<std::endl;
    sink<<"Ks: "<<spec_refl<<std::endl;
    sink<<"Ns: "<<sh<<std::endl;
    sink<<"Transparency: "<<transparency<<std::endl;
    return sink;
}

std::ostream& operator<<(std::ostream& sink, const Material& mat){
    return mat.print(sink);
}