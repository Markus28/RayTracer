#ifndef RAYTRACER_COSINE_H
#define RAYTRACER_COSINE_H


#include "UnaryOperator.h"

namespace symcpp {
    class Cosine : public UnaryOperator {
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


#endif //RAYTRACER_COSINE_H
