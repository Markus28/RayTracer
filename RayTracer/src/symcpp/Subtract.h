#ifndef RAYTRACER_SUBTRACT_H
#define RAYTRACER_SUBTRACT_H


#include "Expression.h"

namespace symcpp {
    class Subtract : public Expression {
    public:
        Subtract(const Expression &a, const Expression &b);

        Subtract(const std::unique_ptr<Expression> &a, const std::unique_ptr<Expression> &b);

        double subs(const std::unordered_map<std::string, double> &env) const override;

        std::unique_ptr<Expression> diff(std::string var) const override;

        std::unique_ptr<Expression> copy() const override;

        std::unique_ptr<Expression> simplify() override;

        unsigned int precedence() const override;

        double const_eval() const override;

        bool is_constant() const override;

    private:
        std::ostream &print(std::ostream &sink) const override;

        std::unique_ptr<Expression> a;
        std::unique_ptr<Expression> b;
    };
}

#endif //RAYTRACER_SUBTRACT_H
