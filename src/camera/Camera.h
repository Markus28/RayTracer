#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <vector>
#include <string>
#include "../Ray.h"


namespace camera {
    using Image = std::vector<std::vector<Vector3D>>;

    class Camera {
    public:

        void set_pixel(unsigned int i, const Vector3D &c);

        virtual Ray ray_at(unsigned int i) const = 0;

        void write_file(std::string file_name) const;

        unsigned int length() const;

        virtual ~Camera() = default;

    protected:
        std::vector<Vector3D> pixels;
        unsigned int size;

        virtual Image post_process() const = 0;
    };
}

#endif //RAYTRACER_CAMERA_H