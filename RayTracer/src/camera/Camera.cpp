#include "Camera.h"
#include "../Utilities.h"


namespace camera {
    unsigned int Camera::length() const {
        return size;
    }

    void Camera::set_pixel(unsigned int i, const Vector3D &c) {
        pixels[i] = c;
    }

    void Camera::write_file(std::string file_name) const {
        Image post_processed = post_process();
        utility::writeImage(post_processed, file_name);
    }
}