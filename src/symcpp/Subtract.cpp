#include "Subtract.h"
#include "Constant.h"
#include <iostream>
#include <cassert>

namespace symcpp {
    Subtract::Subtract(const Expression &a, const Expression &b) {
        this->a = a.copy();
        this->b = b.copy();
    }

    Subtract::Subtract(const std::unique_ptr<Expression> &a, const std::unique_ptr<Expression> &b) {
        this->a = a->copy();
        this->b = b->copy();
    }

    double Subtract::subs(const std::unordered_map<std::string, double> &env) const {
        return a->subs(env) - b->subs(env);
    }

    std::unique_ptr<Expression> Subtract::copy() const {
        std::unique_ptr<Expression> p(new Subtract(a->copy(), b->copy()));
        return p;
    }

    std::unique_ptr<Expression> Subtract::diff(std::string var) const {
        std::unique_ptr<Expression> p(new Subtract(a->diff(var), b->diff(var)));
        return p;
    }

    unsigned int Subtract::precedence() const {
        return 1;
    }

    std::ostream &Subtract::print(std::ostream &sink) const {
        return sink << *a << "-" << *b;
    }

    bool Subtract::is_constant() const {
        return a->is_constant() && b->is_constant();
    }

    double Subtract::const_eval() const {
        assert(is_constant());
        return a->const_eval() - b->const_eval();
    }

    std::unique_ptr<Expression> Subtract::simplify() {
        if (a->is_constant()) {
            if (b->is_constant()) {
                std::unique_ptr<Expression> p(new Constant(const_eval()));
                return p;
            }

            if (a->const_eval() == 0) {
                return b->simplify();
            }
        }

        if (b->is_constant() && b->const_eval() == 0) {
            return a->simplify();
        }

        std::unique_ptr<Expression> p(new Subtract(a->simplify(), b->simplify()));
        return p;
    }
}