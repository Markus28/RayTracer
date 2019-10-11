#ifndef RAYTRACER_SINE_H
#define RAYTRACER_SINE_H


#include "UnaryOperator.h"

namespace symcpp {
    class Sine : public UnaryOperator {
    public:
        using UnaryOperator::UnaryOperator;

        std::unique_ptr<Expression> simplify() override;

        std::unique_ptr<Expression> copy() const override;

    private:
        std::ostream &print(std::ostream &sink) const override;

        double op(double x) const override;

        std::unique_ptr<Expression> partial_derivative() const override;
    };
}

#endif //RAYTRACER_SINE_H
