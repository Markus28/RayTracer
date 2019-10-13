#include "Scene.h"
#include "Light.h"
#include "Intersection.h"
#include "RenderObject.h"
#include "Utilities.h"
#include <iostream>

Scene::Scene(const std::vector<RenderObject*>& objects, const std::vector<Light*>& lights, Camera* camera, Vector3D background, Vector3D ambient)
{
    assert(!objects.empty());
    this->cam = camera;
    this->objs = objects;
    this->lights = lights;
    this->backgrnd = background;
    this->ambient = ambient;
}

void Scene::render(unsigned int recursion_depth) {
    for(cam->resetRay(); !cam->endRay(); cam->advanceRay())
    {
        cam->setRay(traceRay(cam->currentRay(), recursion_depth));
    }
}


Vector3D Scene::traceRay(const Ray &ray, unsigned int recursion_depth) {
    Intersection hit = firstHit(ray);

    if(hit.does_intersect())
    {
        assert(hit.get_object()!=nullptr);
        IntersectionProperties properties;
        if(hit.has_properties()){
            properties = hit.get_properties();
        }
        else {
            properties = hit.get_object()->intersect_properties(ray);
        }
        Vector3D illumination = ambient.elementWiseMultiplication(properties.material.ambient_reflectivity());
        Vector3D intersectionPoint = ray.read_base()+ ray.read_direction()* hit.get_distance();

        for(Light* light: lights)
        {
            Ray shaddow = light->shaddowRay(intersectionPoint);
            shaddow.offset(properties.normal*utility::EPSILON);
            Intersection shadowHit = firstHit(shaddow, true);
            if(!shadowHit.does_intersect() || shadowHit.get_distance() > light->getDistance(intersectionPoint))      //Check shaddow ray
            {
                double dd = shaddow.read_direction()*properties.normal;
                double ds = (shaddow.read_direction()*-1).reflectAround(properties.normal)*(ray.read_direction()*-1);
                if(dd>0)
                {
                    illumination += properties.material.diffuse_reflectivity().elementWiseMultiplication(light->diffuseComponent(
                            shaddow.read_base()))*dd;
                    if(ds>0)
                    {
                        illumination += properties.material.specular_reflectivity().elementWiseMultiplication(light->specularComponent(
                                shaddow.read_base())).elementWiseMultiplication(properties.material.shininess().elementWisePower(ds));
                    }
                }
            }
        }

        Vector3D refractionAndReflection;

        if(recursion_depth!=0)
        {
            if(properties.material.is_reflective() && ray.read_direction()*properties.normal<0)
            {
                Ray reflection = Ray(intersectionPoint, ray.read_direction().reflectAround(properties.normal));
                reflection.offset(properties.normal*utility::EPSILON);
                refractionAndReflection += traceRay(reflection, recursion_depth-1)*
                                           properties.material.get_reflectivity();
            }

            if(properties.material.is_transparent())
            {
                Ray refraction = Ray(intersectionPoint, ray.read_direction().refractAround(properties.normal,
                                                                                           properties.material.get_index()));
                refraction.walk(utility::EPSILON);
                refractionAndReflection += traceRay(refraction, recursion_depth-1)*
                                           properties.material.get_transparency();
            }
        }


        return illumination + refractionAndReflection;
    }

    else
    {
        return backgrnd;
    }
}


Intersection Scene::firstHit(const Ray &ray) {
    Intersection firstHit = objs[0]->ray_intersect(ray);
    for(unsigned int i = 1; i<objs.size(); ++i)
    {
        firstHit = std::min(firstHit, objs[i]->ray_intersect(ray));
    }
    return firstHit;
}


Intersection Scene::firstHit(const Ray &ray, bool ignore_transparent) {
    Intersection firstHit;
    Intersection newHit;
    for(unsigned int i = 0; i<objs.size(); ++i)
    {
        newHit = objs[i]->ray_intersect(ray);
        if(!ignore_transparent || (newHit.does_intersect() && !newHit.get_object()->intersect_properties(
                ray).material.is_transparent())) {                      //TODO: USE newHit.has_properties
            firstHit = std::min(firstHit, newHit);
        }
    }
    return firstHit;
}