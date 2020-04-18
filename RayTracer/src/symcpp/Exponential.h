#ifndef RAYTRACER_EXP_H
#define RAYTRACER_EXP_H


#include "Expression.h"
#include "UnaryOperator.h"

namespace symcpp {
    class Exponential : public UnaryOperator {
    public:
        using UnaryOperator::UnaryOperator;

        std::unique_ptr<Expression> copy() const override;

        std::unique_ptr<Expression> simplify() override;

    private:
        double op(double x) const override;

        std::ostream &print(std::ostream &sink) const override;

        std::unique_ptr<Expression> partial_derivative() const override;
    };
}


#endif //RAYTRACER_EXP_H
