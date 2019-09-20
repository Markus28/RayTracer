#ifndef RAYTRACER_DIVIDE_H
#define RAYTRACER_DIVIDE_H


#include "Expression.h"

class Divide: public Expression {
public:
    Divide(const Expression& a, const Expression& b);
    Divide(const std::unique_ptr<Expression>& a, const std::unique_ptr<Expression>& b);
    std::unique_ptr<Expression> copy() const override;
    std::unique_ptr<Expression> diff(std::string v) const override;
    std::unique_ptr<Expression> simplify() override;
    double subs(const std::unordered_map<std::string, double>& env) const override;
    unsigned int precedence() const override;
    bool is_constant() const override;
    double const_eval() const override;

private:
    std::ostream& print(std::ostream& sink) const override;
    std::unique_ptr<Expression> a;
    std::unique_ptr<Expression> b;
};


#endif //RAYTRACER_DIVIDE_H
