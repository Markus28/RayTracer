#ifndef RAYTRACER_ADD_H
#define RAYTRACER_ADD_H


#include "Expression.h"

class Add: public Expression {
public:
    Add(const Expression& a, const Expression& b);
    Add(std::unique_ptr<Expression>&& a, std::unique_ptr<Expression>&& b);
    double subs(const std::unordered_map<std::string, double>& env) const override;
    std::unique_ptr<Expression> diff(std::string var) const override;
    std::unique_ptr<Expression> copy() const override;
    std::unique_ptr<Expression> simplify() override;
    unsigned int precedence() const override;
    bool is_constant() const override;
    double const_eval() const override;

private:
    std::ostream& print(std::ostream& sink) const override;
    std::unique_ptr<Expression> a;
    std::unique_ptr<Expression> b;
};


#endif //RAYTRACER_ADD_H
