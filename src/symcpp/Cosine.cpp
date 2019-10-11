#include <cmath>
#include <iostream>
#include "Cosine.h"
#include "Multiply.h"
#include "Sine.h"
#include "Constant.h"

namespace symcpp {
    std::unique_ptr<Expression> Cosine::simplify() {
        std::unique_ptr<Expression> p(new Cosine(a->simplify()));
        return p;
    }

    double Cosine::op(double x) const {
        return cos(x);
    }

    std::unique_ptr<Expression> Cosine::partial_derivative() const {
        std::unique_ptr<Expression> p(new Multiply(Constant(-1.0), Sine(a->copy())));
        return p;
    }

    std::unique_ptr<Expression> Cosine::copy() const {
        std::unique_ptr<Expression> p(new Cosine(a->copy()));
        return p;
    }

    std::ostream &Cosine::print(std::ostream &sink) const {
        return sink << "cos(" << *a << ")";
    }
}