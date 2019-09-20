#include "Sine.h"
#include "Cosine.h"
#include <cmath>
#include <iostream>

double Sine::op(double x) const {
    return sin(x);
}

std::unique_ptr<Expression> Sine::simplify() {
    std::unique_ptr<Expression> p(new Sine(a->simplify()));
    return p;
}

std::unique_ptr<Expression> Sine::partial_derivative() const {
    std::unique_ptr<Expression> p(new Cosine(a->copy()));
    return p;
}

std::unique_ptr<Expression> Sine::copy() const {
    std::unique_ptr<Expression> p(new Sine(a->copy()));
    return p;
}

std::ostream& Sine::print(std::ostream &sink) const {
    return sink<<"sin("<<*a<<")";
}