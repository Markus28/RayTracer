#include <cassert>
#include <math.h>
#include "PinHoleCamera.h"
#include "../Utilities.h"
#include "../image/post_process.h"


namespace camera {
    Ray PinHoleCamera::ray_at(unsigned int i) const {
        assert(i < size);
        unsigned int x = i % width;
        unsigned int y = i / width;
        Vector3D result = forward + up * ((height / 2.0) - y) + right * (x - (width / 2.0));
        return Ray(position, result / result.norm());
    }

    PinHoleCamera::PinHoleCamera(Vector3D position, Vector3D up, Vector3D right, unsigned int width,
                                 unsigned int height,
                                 double width_angle) {
        width_angle /= 2;
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
        this->right *= (2 * tan(width_angle)) / width;
        this->up *= (2 * tan(width_angle)) / width;


        forward /= forward.norm();

        pixels = std::vector<Vector3D>(width * height);
        size = width * height;

        assert(width_angle > 0);
        assert(utility::equals_about(up * right, 0, utility::EPSILON));
    }

    Image PinHoleCamera::post_process() const {
        Image img(width, std::vector<Vector3D>(height));
        for (unsigned int i = 0; i < size; ++i) {
            img[i % width][i / width] = pixels[i];
        }
        return image::max_tone_mapping(image::gamma_correct(image::anti_alias(img, 2), 0.5));
    }
}