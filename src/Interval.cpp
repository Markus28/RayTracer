#include <algorithm>
#include "Interval.h"

Interval::Interval(double mini, double maxi) {
    if(mini>maxi)
    {
        empty = true;
    }

    else{
        empty = false;
    }

    this->mini = mini;
    this->maxi = maxi;
}

Interval::Interval() {
    empty = true;
    mini = 0;
    maxi = -1;
}

Interval Interval::operator+(const Interval &other) const {         //TODO: Special cases: Empty Intervals
    if(empty)
    {
        return other;
    }

    if(other.empty)
    {
        return {mini, maxi};
    }

    return {std::min(mini, other.mini), std::max(maxi, other.maxi)};
}

double Interval::midPoint() const {
    return (mini+maxi)/2;
}

Interval Interval::operator*(const Interval &other) const {         //TODO: Special cases: Empty Intervals
    if(empty||other.empty){
        return {};
    }

    return {std::max(mini, other.mini), std::min(maxi, other.maxi)};
}

bool Interval::isEmpty() const {
    return empty;
}

bool Interval::containsPositive() const {
    return !empty && maxi>=0;
}

bool Interval::contains(double x) const {
    return !empty&&x<=maxi&&x>=mini;
}

double Interval::getMin() const{
    return mini;
}

double Interval::getMax() const{
    return maxi;
}

double Interval::length() const {
    if(empty)
    {
        return 0;
    }

    return maxi-mini;
}

double Interval::getCenter() const {
    return (mini+maxi)/2.0;
}

bool operator<(const Interval& first, const Interval& second){
    return first.length()<second.length();
}

std::ostream& operator<<(std::ostream& sink, const Interval& i){
    sink<<'[';
    if(!i.empty){
        sink<<i.mini<<", "<<i.maxi;
    }
    return sink<< ']';
}