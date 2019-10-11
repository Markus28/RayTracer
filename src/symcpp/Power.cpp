#include <cmath>
#include <cassert>
#include <iostream>
#include "Power.h"
#include "Constant.h"
#include "Multiply.h"
#include "Logarithm.h"
#include "Add.h"
#include "Divide.h"

namespace symcpp {
    Power::Power(const Expression &a, const Expression &b) : a(a.copy()), b(b.copy()) {}

    Power::Power(const Expression &a, double p) : a(a.copy()), b(new Constant(p)) {}

    Power::Power(const std::unique_ptr<Expression> &a, const std::unique_ptr<Expression> &b) : a(a->copy()),
                                                                                               b(b->copy()) {}

    double Power::subs(const std::unordered_map<std::string, double> &env) const {
        return pow(a->subs(env), b->subs(env));
    }

    bool Power::is_constant() const {
        return (a->is_constant() && b->is_constant()) || (a->is_constant() && a->const_eval() == 1)
               || (a->is_constant() && a->const_eval() == 0) || (b->is_constant() && b->const_eval() == 0);
    }

    double Power::const_eval() const {
        assert(is_constant());
        if (a->is_constant()) {
            if (a->const_eval() == 1)
                return 1.0;
            if (a->const_eval() == 0)
                return 0.0;
            return pow(a->const_eval(), b->const_eval());
        }

        return 0;
    }

    std::unique_ptr<Expression> Power::simplify() {
        if (is_constant()) {
            std::unique_ptr<Expression> p(new Constant(const_eval()));
            return p;
        }

        if (b->is_constant() && b->const_eval() == 1) {
            return std::move(a);
        }

        std::unique_ptr<Expression> p(new Power(a->simplify(), b->simplify()));
        return p;
    }

    std::unique_ptr<Expression> Power::diff(std::string var) const {
        if (b->is_constant()) {
            //This is just a special case of the general derivative below. Not actually necessary but the Syntax-Tree is nicer.
            double b_val = b->const_eval();
            std::unique_ptr<Expression> p(new Multiply(a->diff(var), std::unique_ptr<Expression>(
                    new Multiply(Constant(b_val), Power(*a, Constant(b_val - 1.0))))));
            return p;
        }

        //General derivative:
        std::unique_ptr<Expression> p(new Multiply(
                Add(Multiply(b->diff(var), std::unique_ptr<Expression>(new Logarithm(*a))),
                    Multiply(b->copy(), Logarithm(*a).diff(var))), Power(a, b)));
        return p;
    }

    std::unique_ptr<Expression> Power::copy() const {
        std::unique_ptr<Expression> p(new Power(a->copy(), b->copy()));
        return p;
    }

    unsigned int Power::precedence() const {
        return 5;
    }

    std::ostream &Power::print(std::ostream &sink) const {
        if (a->precedence() <= 5)
            sink << "(" << *a << ")";
        else
            sink << *a;

        sink << "^";

        if (b->precedence() <= 5)
            sink << "(" << *b << ")";
        else
            sink << *b;

        return sink;
    }
}