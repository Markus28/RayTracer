#ifndef RAYTRACER_MTLLIB_H
#define RAYTRACER_MTLLIB_H


#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Material.h"

class MTLLib {
public:
    explicit MTLLib(const char* filename);
    MTLLib() = default;
    bool contains(std::string key) const;
    Material& operator[](std::string key);
    std::ostream& print(std::ostream& sink) const;
    friend std::ostream& operator<<(std::ostream& sink, const MTLLib& lib);

private:
    std::unordered_map<std::string, Material> materials;
};


#endif //RAYTRACER_MTLLIB_H
