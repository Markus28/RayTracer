#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

#include <iostream>

/**
 * @brief The closed interval [mini, maxi]
 */
class Interval {
public:
    Interval(double min, double max);
    Interval();
    Interval operator+(const Interval& other) const;    //Returns smallest interval containing both
    double midPoint() const;
    Interval operator*(const Interval& other) const;    //Intersection
    bool isEmpty() const;
    bool containsPositive() const;
    bool contains(double x) const;
    double getMin() const;
    double getMax() const;
    double getCenter() const;
    double length() const;
    friend std::ostream& operator<<(std::ostream& sink, const Interval& i);

private:
    double mini;
    double maxi;
    bool empty;
};

bool operator<(const Interval& first, const Interval& second);

#endif //RAYTRACER_INTERVAL_H
