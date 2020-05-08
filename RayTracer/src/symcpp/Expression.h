#ifndef RAYTRACER_EXPRESSION_H
#define RAYTRACER_EXPRESSION_H

#include <string>
#include <memory>
#include <unordered_map>

namespace symcpp {
    class Expression {
    public:
        virtual double subs(const std::unordered_map<std::string, double> &env) const = 0;

        virtual std::unique_ptr<Expression> diff(std::string var) const = 0;

        virtual std::unique_ptr<Expression> copy() const = 0;

        virtual std::unique_ptr<Expression>
        simplify() = 0;     //Calling simplify might corrupt the original Expression. Only use the result of simplify()
        virtual bool is_constant() const = 0;

        virtual unsigned int precedence() const = 0;

        virtual double
        const_eval() const = 0;   //If this method is called assert(is_constant()) must hold. The Expression is constant and the value is returned

    private:
        virtual std::ostream &print(std::ostream &sink) const = 0;

        friend std::ostream &operator<<(std::ostream &sink, const Expression &expr);
    };
}

#endif //RAYTRACER_EXPRESSION_H
