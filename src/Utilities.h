#ifndef RAYTRACER_UTILITIES_H
#define RAYTRACER_UTILITIES_H

#endif //RAYTRACER_UTILITIES_H

#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include "renderable/BoundedVolume.h"


namespace utility {

    template <class T>
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, std::function<bool(T , T)> compare)
    {
        assert(begin!=end);
        T pivot = *begin;
        typename std::vector<T>::iterator change = begin;
        for(typename std::vector<T>::iterator it = begin+1; it!=end; ++it)
        {
            if(compare(*it,pivot))
            {
                T tmp = *it;
                *it = *(change+1);
                *(change+1) = tmp;
                ++change;
            }
        }

        T tmp = *begin;
        *begin = *(change);
        *(change) = tmp;
        return change;
    }


    template <class T>
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        std::function<bool(T,T)> lambda = [](T a, T b)->bool
        {
            return a<b;
        };

        return partition<T>(begin, end, lambda);
    }


    template <class T>
    typename std::vector<T>::iterator split_middle(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, std::function<bool(T , T)> compare, unsigned int index, unsigned int length)
    {
        if(std::distance(begin, end)<=1)
        {
            return begin;
        }

        typename std::vector<T>::iterator split = partition<T>(begin, end, compare);

        if(std::distance(begin, split)+index<(length-1)/2)
        {
            return split_middle(split+1, end, compare, index+std::distance(begin, split)+1, length);
        }

        else if(std::distance(begin, split)+index>(length-1)/2)
        {
            return split_middle(begin, split, compare, index, length);
        }

        return split;
    }


    template <class T>
    typename std::vector<T>::iterator split_middle(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, std::function<bool(T , T)> compare)
    {
        return split_middle(begin, end, compare, 0, std::distance(begin, end));
    }

    template <class T>
    typename std::vector<T>::iterator split_middle(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        std::function<bool(T,T)> lambda = [](T a, T b)->bool
        {
            return a<b;
        };
        return split_middle(begin, end, lambda);
    }

    template <class T>
    void quicksort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        if(std::distance(begin, end)>1)
        {
            typename std::vector<T>::iterator split = partition<T>(begin, end);
            quicksort<T>(begin, split);
            quicksort<T>(split+1, end);
        }
    }

    /**
     * @brief Class containing solution to quadratic equation
     */
    struct QuadraticSolution
    {
        /// Indicates wether the equation has any solutions
        bool exists;
        double solution1;
        double solution2;
    };

    const double EPSILON = 1E-5;

    bool equals_about(const double &test, const double &truth, const double &epsilon);

    QuadraticSolution solveQuadraticEquation(double a, double b, double c);

    void writeImage(std::vector<std::vector<Vector3D>>& im, std::string file_name);

    BoundingBox sumBoundingBoxes(const std::vector<BoundedVolume*>& v);

    BoundingBox sumBoundingBoxes(std::vector<BoundedVolume*>::const_iterator b, std::vector<BoundedVolume*>::const_iterator e);

    const double& min(const double& x, const double& y, const double&z);

    const double& max(const double& x, const double& y, const double&z);
}