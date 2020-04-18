#ifndef RAYTRACER_VARIABLE_H
#define RAYTRACER_VARIABLE_H


#include "Expression.h"

namespace symcpp {
    class Variable : public Expression {
    public:
        Variable(std::string name);

        std::unique_ptr<Expression> copy() const override;

        std::unique_ptr<Expression> diff(std::string v) const override;

        std::unique_ptr<Expression> simplify() override;

        double subs(const std::unordered_map<std::string, double> &env) const override;

        unsigned int precedence() const override;

        bool is_constant() const override;

        double const_eval() const override;

    private:
        std::ostream &print(std::ostream &sink) const override;

        std::string name;
    };
}


#endif //RAYTRACER_VARIABLE_H
