#include "Multiply.h"
#include "Add.h"
#include "Constant.h"
#include <iostream>
#include <cassert>

namespace symcpp {
    Multiply::Multiply(const Expression &a, const Expression &b) : a(a.copy()), b(b.copy()) {}

    Multiply::Multiply(std::unique_ptr<Expression> &&a, std::unique_ptr<Expression> &&b) : a(std::move(a)),
                                                                                           b(std::move(b)) {}

    std::unique_ptr<Expression> Multiply::copy() const {
        std::unique_ptr<Expression> p(new Multiply(a->copy(), b->copy()));
        return p;
    }

    std::unique_ptr<Expression> Multiply::diff(std::string v) const {
        std::unique_ptr<Expression> p(new Add(Multiply(a->copy(), b->diff(v)), Multiply(a->diff(v), b->copy())));
        return p;
    }

    double Multiply::subs(const std::unordered_map<std::string, double> &env) const {       //TODO a or b zero
        return a->subs(env) * b->subs(env);
    }

    unsigned int Multiply::precedence() const {
        return 4;
    }

    std::ostream &Multiply::print(std::ostream &sink) const {
        if (a->precedence() <= 4)
            sink << "(" << *a << ")";
        else
            sink << *a;

        sink << "*";

        if (b->precedence() <= 4)
            sink << "(" << *b << ")";
        else
            sink << *b;

        return sink;
    }

    bool Multiply::is_constant() const {
        std::unordered_map<std::string, double> empty;
        return (a->is_constant() && b->is_constant()) || (a->is_constant() && a->const_eval() == 0) ||
               (b->is_constant() && b->const_eval() == 0);
    }

    std::unique_ptr<Expression> Multiply::simplify() {
        if (a->is_constant()) {
            if (b->is_constant()) {
                std::unique_ptr<Expression> p(new Constant(a->const_eval() * b->const_eval()));
                return p;
            }

            double a_val = a->const_eval();

            if (a_val == 1)
                return b->simplify();

            if (a_val == 0) {
                std::unique_ptr<Expression> p(new Constant(0));
                return p;
            }

            std::unique_ptr<Expression> p(new Multiply(Constant(a->const_eval()), *(b->simplify())));
            return p;
        }

        if (b->is_constant()) {
            double b_val = b->const_eval();

            if (b_val == 1)
                return a->simplify();

            if (b_val == 0) {
                std::unique_ptr<Expression> p(new Constant(0));
                return p;
            }
        }

        std::unique_ptr<Expression> p(new Multiply(a->simplify(), b->simplify()));
        return p;
    }

    double Multiply::const_eval() const {
        assert(is_constant());
        double a_val, b_val;
        if (a->is_constant()) {
            a_val = a->const_eval();
            if (a_val == 0)
                return 0;
        }

        if (b->is_constant()) {
            b_val = b->const_eval();
            if (b_val == 0)
                return 0;
        }

        return b_val *
               a_val;     //a_val and b_val must have been intialized, otherwise assert(is_constant) would have failed
    }
}