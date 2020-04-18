#include "Add.h"
#include "Constant.h"
#include <iostream>
#include <cassert>

namespace symcpp {
    Add::Add(const Expression &a, const Expression &b) {
        this->a = a.copy();
        this->b = b.copy();
    }

    Add::Add(std::unique_ptr<Expression> &&a, std::unique_ptr<Expression> &&b) : a(std::move(a)), b(std::move(b)) {}

    double Add::subs(const std::unordered_map<std::string, double> &env) const {
        return a->subs(env) + b->subs(env);
    }

    std::unique_ptr<Expression> Add::copy() const {
        std::unique_ptr<Expression> p(new Add(a->copy(), b->copy()));
        return p;
    }

    std::unique_ptr<Expression> Add::diff(std::string var) const {
        std::unique_ptr<Expression> p(new Add(a->diff(var), b->diff(var)));
        return p;
    }

    std::ostream &Add::print(std::ostream &sink) const {
        return sink << *a << "+" << *b;
    }

    unsigned int Add::precedence() const {
        return 1;
    }

    bool Add::is_constant() const {
        return (a->is_constant() && b->is_constant());
    }

    std::unique_ptr<Expression> Add::simplify() {
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

        std::unique_ptr<Expression> p(new Add(a->simplify(), b->simplify()));
        return p;
    }

    double Add::const_eval() const {
        assert(is_constant());
        return a->const_eval() + b->const_eval();
    }
}