#ifndef RAYTRACER_POST_PROCESS_H
#define RAYTRACER_POST_PROCESS_H

#include "../Vector3D.h"
#include <vector>

namespace image{
    using Image = std::vector<std::vector<Vector3D>>;

    Image gamma_correct(const Image& original, double gamma);

    Image gamma_correct(const Image& original, double gamma, double A);

    Image max_tone_mapping(const Image& original);

    Image max_tone_mapping(const Image& original, double max);

    Image anti_alias(const Image& original, unsigned int window_size);
}

#endif //RAYTRACER_POST_PROCESS_H
