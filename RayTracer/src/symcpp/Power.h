#ifndef RAYTRACER_POWER_H
#define RAYTRACER_POWER_H


#include "Expression.h"

namespace symcpp {
    class Power : public Expression {
    public:
        Power(const Expression &a, const Expression &b);

        Power(const Expression &a, double p);

        Power(const std::unique_ptr<Expression> &a, const std::unique_ptr<Expression> &b);

        double subs(const std::unordered_map<std::string, double> &env) const override;

        std::unique_ptr<Expression> diff(std::string var) const override;

        std::unique_ptr<Expression> copy() const override;

        std::unique_ptr<Expression> simplify() override;

        bool is_constant() const override;

        unsigned int precedence() const override;

        double const_eval() const override;

    private:
        std::unique_ptr<Expression> a;
        std::unique_ptr<Expression> b;

        std::ostream &print(std::ostream &sink) const override;
    };
}

#endif //RAYTRACER_POWER_H
