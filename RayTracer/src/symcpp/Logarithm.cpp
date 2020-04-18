#include <cmath>
#include <iostream>
#include "Logarithm.h"
#include "Constant.h"
#include "Divide.h"

namespace symcpp {
    std::unique_ptr<Expression> Logarithm::partial_derivative() const {
        std::unique_ptr<Expression> p(new Divide(Constant(1), *a));
        return p;
    }

    std::unique_ptr<Expression> Logarithm::copy() const {
        std::unique_ptr<Expression> p(new Logarithm(a->copy()));
        return p;
    }

    std::ostream &Logarithm::print(std::ostream &sink) const {
        return sink << "log(" << *a << ")";
    }

    std::unique_ptr<Expression> Logarithm::simplify() {
        std::unique_ptr<Expression> p(new Logarithm(a->simplify()));
        return p;
    }

    double Logarithm::op(double x) const {
        return log(x);
    }
}