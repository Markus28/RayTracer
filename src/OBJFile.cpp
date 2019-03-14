#include "OBJFile.h"

#include <fstream>
#include <sstream>

OBJFile::OBJFile(const char* f_name, Material mat) {
    std::ifstream f(f_name);
    std::string line;
    char id;
    double x, y, z;
    unsigned int a, b, c;
    int i = 0;

    while(std::getline(f, line))
    {
        std::istringstream iss(line);
        iss>>id;

        if(id=='v')
        {
            if(!(iss>>x>>y>>z))
            {
                throw("File corrupted...");
            }

            vertices.emplace_back(x, y, z);
        }

        else if(id=='f')
        {
            if(!(iss>>a>>b>>c))
            {
                throw("File corrupted...");
            }

            polygons.emplace_back(vertices[c-1], vertices[b-1], vertices[a-1], mat);
        }
    }
}

std::vector<Triangle> OBJFile::getTriangles() const {
    return polygons;
}

void OBJFile::dump(std::string file_name) const {
    return;     //TODO: Implement
}