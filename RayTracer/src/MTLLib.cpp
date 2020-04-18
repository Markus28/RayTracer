#include "MTLLib.h"


MTLLib::MTLLib(const char* f_name) {            //TODO: Fail if file doesn't exist!
    std::ifstream f(f_name);
    std::string line;
    std::string id;
    std::string mtl_name;
    double x, y, z;

    while(std::getline(f, line))
    {
        std::istringstream iss(line);
        iss>>id;            //TODO: Check whether line is empty

        if(id == "newmtl")
        {
            iss>>mtl_name;
            materials.emplace(std::make_pair(mtl_name, Material()));

        }

        else if(id=="Ka")
        {
            iss>>x>>y>>z;
            materials[mtl_name].ambient_refl = Vector3D(x, y, z);
        }

        else if(id=="Kd")
        {
            iss>>x>>y>>z;
            materials[mtl_name].diff_refl = Vector3D(x, y, z);
        }

        else if(id=="Ks")
        {
            iss>>x>>y>>z;
            materials[mtl_name].spec_refl = Vector3D(x, y, z);
        }

        else if(id=="Tf")
        {
            iss>>x>>y>>z;
            materials[mtl_name].transparency = 1.0 - (x+y+z)/3.0;         //TODO: make transmission filter rgb
        }

        else if(id=="Ns")
        {
            iss>>x;
            materials[mtl_name].sh = Vector3D(x, x, x);
        }

        else if(id=="d")
        {
            iss>>x;
            materials[mtl_name].eta = x;
        }
    }
}


Material& MTLLib::operator[](std::string key) {
    return materials.at(key);
}


bool MTLLib::contains(std::string key) const {
    return materials.find(key)!=materials.end();
}


std::ostream& MTLLib::print(std::ostream& sink) const{
    for(auto mtl: materials){
        sink<<mtl.first<<std::endl<<mtl.second<<std::endl<<std::endl;
    }
    return sink;
}


std::ostream& operator<<(std::ostream& sink, const MTLLib& lib){
    return lib.print(sink);
}