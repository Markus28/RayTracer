#include "OBJFile.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

OBJFile::OBJFile(const char* f_name, Material mat) {
    std::ifstream f(f_name);
    std::string line;
    std::string id;
    std::string current_material;
    double x, y, z;
    char ignore;
    long unsigned int a, b, c;
    std::istringstream iss;


    //Strip away comments and empty lines...
    do {
        if (!std::getline(f, line)) {
            return;
        }

        iss = std::istringstream(line);
        iss>>id;
    } while(id.at(0) == '#' || line.size() == 1);


    //Load the material library
    if(id=="mtllib")
    {
        iss>>id;
        materials = MTLLib(id.c_str());
    }

    do {
        iss = std::istringstream(line);
        iss>>id;

        if(id=="v")
        {
            if(!(iss>>x>>y>>z))
            {
                throw std::runtime_error("OBJ-File corrupted at Vertex...");
            }

            vertices.emplace_back(x, y, z);
        }

        else if(id=="vn")
        {
            if(!(iss>>x>>y>>z))
            {
                throw std::runtime_error("OBJ-File corrupted at Normal...");
            }

            normals.emplace_back(x, y, z);
        }

        else if(id=="f")
        {
            FaceData data = FaceData(iss);
            std::vector<Triangle> new_triangles = data.get_triangles(vertices, normals, mat);
            polygons.insert(polygons.end(), new_triangles.begin(), new_triangles.end());
        }

        else if(id=="usemtl")
        {
            if(!(iss>>current_material))
            {
                throw std::runtime_error("File corrupted...");
            }

            if(materials.contains(current_material)) {
                mat = materials[current_material];
            }
        }

    } while(std::getline(f, line));
}

std::vector<Triangle> OBJFile::get_triangles() const {
    return polygons;
}

void OBJFile::dump(std::string file_name) const {
    return;     //TODO: Implement
}


BinaryVolumeHierarchy OBJFile::getBVH() {
    std::vector<BoundedVolume*> triangle_ptrs;

    for(Triangle& t: polygons)
    {
        triangle_ptrs.push_back(&t);
    }

    return {triangle_ptrs.begin(), triangle_ptrs.end()};
}


FaceData::FaceData(std::istringstream &iss) {
    std::string s;
    size_t pos = 0;
    std::string token;
    int i = 0;

    while(iss>>s)
    {
        data.push_back({-1,-1,-1});
        i = 0;
        while ((pos = s.find("/")) != std::string::npos) {
            token = s.substr(0, pos);
            if(i==0 && token=="" || i>=2)
            {
                throw std::runtime_error("File corrupted...");
            }

            else if(token==""){
                data[data.size()-1][i] = -1;
            }

            else{
                data[data.size()-1][i] = stoi(token);
            }

            s.erase(0, pos + 1);
            ++i;
        }

        data[data.size()-1][i] = stoi(s);
    }
}

std::vector<Triangle> FaceData::get_triangles(const std::vector<Vector3D> &vertices, const std::vector<Vector3D>& normals, Material mat) {
    std::vector<Triangle> result;

    //Data contains the indeces of all vertices. The face may be a polygon with more than 3 vertices. Thus we split it up into triangles
    for(int i = 1; i<data.size()-1; ++i)
    {
        result.emplace_back(vertices[data[i+1][0]-1], vertices[data[i][0]-1], vertices[data[0][0]-1], mat);
        if(data[i+1][2]!=-1 && data[i][2]!=-1 && data[0][2]!=-1)
        {
            result[result.size()-1].set_normals(normals[data[i+1][2]-1], normals[data[i][2]-1], normals[data[0][2]-1]);
            result[result.size()-1].enable_interpolation();
        }
    }

    return result;
}
