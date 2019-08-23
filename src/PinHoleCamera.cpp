#include <cassert>
#include <math.h>
#include "PinHoleCamera.h"
#include "Utilities.h"


Ray PinHoleCamera::currentRay() const {
    Vector3D result = forward+up*((height/2.0)-y)+right*(x-(width/2.0));
    return Ray(position, result/result.norm());
}

PinHoleCamera::PinHoleCamera(Vector3D position, Vector3D up, Vector3D right, unsigned int width, unsigned int height,
                             double width_angle) {
    width_angle/=2;
    this->width = width;
    this->height = height;
    this->position = position;
    this->up = up;
    this->right = right;
    this->forward = up.cross(right);

    //w = 2*tan(w_angle) = width*right.norm();
    //right.norm() = 2*tan(w_angle)/width

    this->right /= right.norm();
    this->up /= up.norm();
    this->right *= (2*tan(width_angle))/width;
    this->up *= (2*tan(width_angle))/width;


    forward/=forward.norm();

    image = Image(width, std::vector<Vector3D>(height));

    assert(width_angle>0);
    assert(utility::equals_about(up*right, 0, utility::EPSILON));
}

Image PinHoleCamera::postProcess() const {
    return image;
}