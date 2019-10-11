#include <cmath>
#include <iostream>
#include "Exponential.h"
#include "Multiply.h"

namespace symcpp {
    std::unique_ptr<Expression> Exponential::partial_derivative() const {
        return copy();
    }

    std::unique_ptr<Expression> Exponential::copy() const {
        std::unique_ptr<Expression> p(new Exponential(a->copy()));
        return p;
    }

    std::ostream &Exponential::print(std::ostream &sink) const {
        return sink << "exp(" << *a << ")";
    }

    std::unique_ptr<Expression> Exponential::simplify() {
        std::unique_ptr<Expression> p(new Exponential(a->simplify()));
        return p;
    }

    double Exponential::op(double x) const {
        return exp(x);
    }
}