#include "Scene.h"
#include "Light.h"
#include "Intersection.h"
#include "renderable/RenderObject.h"
#include "Utilities.h"
#include <iostream>

Scene::Scene(const std::vector<RenderObject*>& objects, const std::vector<Light*>& lights, camera::Camera* camera, Vector3D background, Vector3D ambient)
{
    assert(!objects.empty());
    this->cam = camera;
    this->objs = objects;
    this->lights = lights;
    this->backgrnd = background;
    this->ambient = ambient;
}

void Scene::render(unsigned int recursion_depth) {
    #pragma omp parallel for
    for(unsigned int i = 0; i<cam->length(); ++i)
    {
        cam->set_pixel(i, trace_ray(cam->ray_at(i), recursion_depth));
    }
}


Vector3D Scene::trace_ray(const Ray &ray, unsigned int recursion_depth) {
    Intersection hit = first_hit(ray);

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
        Vector3D intersection_point = ray.read_base()+ ray.read_direction()* hit.get_distance();

        for(Light* light: lights)
        {
            Ray shadow = light->shaddowRay(intersection_point);
            shadow.offset(properties.normal*utility::EPSILON);
            Intersection shadowHit = first_hit(shadow, true);
            if(!shadowHit.does_intersect() || shadowHit.get_distance() > light->getDistance(intersection_point))      //Check shadow ray
            {
                double dd = shadow.read_direction()*properties.normal;
                double ds = (shadow.read_direction()*-1).reflectAround(properties.normal)*(ray.read_direction()*-1);
                if(dd>0)
                {
                    illumination += properties.material.diffuse_reflectivity().elementWiseMultiplication(light->diffuseComponent(
                            shadow.read_base()))*dd;
                    if(ds>0)
                    {
                        illumination += properties.material.specular_reflectivity().elementWiseMultiplication(light->specularComponent(
                                shadow.read_base())).elementWiseMultiplication(properties.material.shininess().elementWisePower(ds));
                    }
                }
            }
        }

        Vector3D refraction_and_reflection;

        if(recursion_depth!=0)
        {
            if(properties.material.is_reflective() && ray.read_direction()*properties.normal<0)
            {
                Ray reflection = Ray(intersection_point, ray.read_direction().reflectAround(properties.normal));
                reflection.offset(properties.normal*utility::EPSILON);
                refraction_and_reflection += trace_ray(reflection, recursion_depth - 1)*
                                           properties.material.get_reflectivity();
            }

            if(properties.material.is_transparent())
            {
                Ray refraction = Ray(intersection_point, ray.read_direction().refractAround(properties.normal,
                                                                                           properties.material.get_index()));
                refraction.walk(utility::EPSILON);
                refraction_and_reflection += trace_ray(refraction, recursion_depth - 1)*
                                           properties.material.get_transparency();
            }
        }


        return illumination + refraction_and_reflection;
    }

    else
    {
        return backgrnd;
    }
}


Intersection Scene::first_hit(const Ray &ray) {
    Intersection first = objs[0]->ray_intersect(ray);
    for(unsigned int i = 1; i<objs.size(); ++i)
    {
        first = std::min(first, objs[i]->ray_intersect(ray));
    }
    return first;
}


Intersection Scene::first_hit(const Ray &ray, bool ignore_transparent) {
    if(!ignore_transparent)
        return first_hit(ray);

    Intersection first;
    Intersection new_hit;
    for(unsigned int i = 0; i<objs.size(); ++i)
    {
        new_hit = objs[i]->ray_intersect(ray);

        if(new_hit.does_intersect() && !new_hit.has_properties()) {
            new_hit.set_properties(new_hit.get_object()->intersect_properties(ray));
        }

        if((new_hit.does_intersect() && !new_hit.get_properties().material.is_transparent())) {
            first = std::min(first, new_hit);
        }
    }
    return first;
}