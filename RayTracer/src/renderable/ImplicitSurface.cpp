#include "ImplicitSurface.h"
#include <cmath>
#include <cassert>


ImplicitSurface::ImplicitSurface(symcpp::SymbolicGraph f, Material m, BoundingBox b):F(f), mat(m), bounds(b) {
    dxF = F.diff("x");
    dyF = F.diff("y");
    dzF = F.diff("z");

    std::cout<< f << std::endl << dxF <<std::endl <<dyF<<std::endl<<dzF<<std::endl;

    max_iter = 70;
    epsilon = 0.00000000001;
}

BoundingBox ImplicitSurface::get_bounds() const {
    return bounds;
}

/**
 * @brief Uses the symbolic derivative and the Newton method to detect the earliest intersection
 * @see https://en.wikipedia.org/wiki/Newton%27s_method
 * @param ray The ray intersecting the surface
 * @return Intersection object containing distance of intersection and pointer to this
 */
Intersection ImplicitSurface::ray_intersect(const Ray &ray) const {
    Interval range = bounds.intersection_interval(ray);

    if(range.isEmpty() || range.getMax()<0){
        return {};
    }


    double guess_l = std::max(range.getMin(), 0.);
    Vector3D guess_v = ray.read_direction()+ ray.read_direction()*guess_l;
    std::unordered_map<std::string, double> env;
    env["x"] = guess_v[0];
    env["y"] = guess_v[1];
    env["z"] = guess_v[2];

    unsigned int i = 0;
    double F_value = F.subs(env);
    double deriv;
    double correction = 100;

    while(i<max_iter && std::abs(correction)>epsilon){
        deriv = dxF.subs(env)* ray.read_direction()[0] + dyF.subs(env)* ray.read_direction()[1] + dzF.subs(env)*
                                                                                              ray.read_direction()[2];
        correction = F_value/deriv;
        guess_l -= correction;
        guess_v = ray.read_base()+ ray.read_direction()*guess_l;
        env["x"] = guess_v[0];
        env["y"] = guess_v[1];
        env["z"] = guess_v[2];
        F_value = F.subs(env);
        ++i;
    }

    if(std::abs(F_value)<epsilon && guess_l>0){
        Vector3D normal(dxF.subs(env), dyF.subs(env), dzF.subs(env));
        normal /= normal.norm();
        return {this, guess_l, {normal, mat}};
    }

    return {};
}

IntersectionProperties ImplicitSurface::intersect_properties(const Ray &ray) const {
    Intersection is = this->ray_intersect(ray);            //TODO: add intersection information to call!!! This is inefficient!
    assert(is.does_intersect());
    Vector3D posn = ray.read_base()+ ray.read_direction()* is.get_distance();
    std::unordered_map<std::string, double> env;
    env["x"] = posn[0];
    env["y"] = posn[1];
    env["z"] = posn[2];

    Vector3D grad(dxF.subs(env), dyF.subs(env), dzF.subs(env));
    grad /= grad.norm();
    return {grad ,mat};
}

std::ostream& ImplicitSurface::print(std::ostream &sink) const {
    sink<<"Implicit Surface for Function F(x,y,z)="<<F;
    return sink;
}