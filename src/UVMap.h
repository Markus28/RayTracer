#ifndef RAYTRACER_UVMAP_H
#define RAYTRACER_UVMAP_H


#include <vector>

template <typename S, typename T>
class UVMap {
public:
    explicit UVMap(const std::vector<std::vector<T>>& texture)
    {
        this->texture = texture;
    }

    UVMap(const UVMap<S, T>& other)
    {
        this->texture = other.texture;
    }

    T get(S coordinates) const{
        std::pair<double, double> uv = map(coordinates);
        return texture[int(uv.first*texture.size())][int(uv.second*texture[0].size())];
    }

private:
    virtual std::pair<double, double> map(S coordinates) const = 0;
    std::vector<std::vector<T>> texture;
};


#endif //RAYTRACER_UVMAP_H
