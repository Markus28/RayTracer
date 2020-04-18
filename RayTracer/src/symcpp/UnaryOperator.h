#ifndef RAYTRACER_UNARYOPERATOR_H
#define RAYTRACER_UNARYOPERATOR_H


#include "Expression.h"

namespace symcpp {
    class UnaryOperator : public Expression {
    public:
        UnaryOperator(const Expression &a) : a(a.copy()) {};

        UnaryOperator(std::unique_ptr<Expression> &&a) : a(std::move(a)) {};

        std::unique_ptr<Expression> diff(std::string v) const override;

        double subs(const std::unordered_map<std::string, double> &env) const override;

        unsigned int precedence() const override;

        bool is_constant() const override;

        double const_eval() const override;

    protected:
        std::unique_ptr<Expression> a;

    private:
        virtual double op(double x) const = 0;

        virtual std::unique_ptr<Expression> partial_derivative() const = 0;
    };
}


#endif //RAYTRACER_UNARYOPERATOR_H
