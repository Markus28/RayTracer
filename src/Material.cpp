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

Vector3D& Material::ambientReflectivity() {
    return ambient_refl;
}

Vector3D& Material::diffuseReflectivity() {
    return diff_refl;
}

Vector3D& Material::specularReflectivity() {
    return spec_refl;
}

Vector3D& Material::shininess() {
    return sh;
}

bool Material::isReflective() const {
    return reflectivity!=0;
}

bool Material::isTransparent() const {
    return transparency!=0;
}

double Material::getIndex()const {
    return eta;
}

double Material::getReflectivity() const
{
    return reflectivity;
}

double Material::getTransparency() const {
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