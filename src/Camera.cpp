#include "Camera.h"
#include "Utilities.h"


bool Camera::endRay() const {
    return x==width;
}

void Camera::resetRay() {
    x=0;
    y=0;
}

void Camera::setRay(Vector3D c){
    image[x][y] = c;
}

void Camera::writeFile(std::string file_name) const {
    Image postprocessed = postProcess();
    utility::writeImage(postprocessed, file_name);
}

void Camera::advanceRay() {
    y = (y+1)%height;
    if(y==0)
    {
        ++x;
    }
}
