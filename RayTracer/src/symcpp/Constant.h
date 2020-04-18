#ifndef RAYTRACER_CONSTANT_H
#define RAYTRACER_CONSTANT_H


#include "Expression.h"

namespace symcpp {
    class Constant : public Expression {
    public:
        Constant(double c);

        std::unique_ptr<Expression> copy() const override;

        std::unique_ptr<Expression> diff(std::string var) const override;

        std::unique_ptr<Expression> simplify() override;

        double subs(const std::unordered_map<std::string, double> &env) const override;

        unsigned int precedence() const override;

        bool is_constant() const override;

        double const_eval() const override;

    private:
        std::ostream &print(std::ostream &sink) const override;

        double c;
    };
}


#endif //RAYTRACER_CONSTANT_H
