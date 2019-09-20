#include <cassert>
#include "UnaryOperator.h"
#include "Multiply.h"


std::unique_ptr<Expression> UnaryOperator::diff(std::string v) const {
    std::unique_ptr<Expression> p (new Multiply(a->diff(v), partial_derivative()));
    return p;
}

unsigned int UnaryOperator::precedence() const {
    return 6;
}

bool UnaryOperator::is_constant() const {
    return a->is_constant();
}

double UnaryOperator::subs(const std::unordered_map<std::string, double> &env) const {
    return op(a->subs(env));
}

double UnaryOperator::const_eval() const {
    assert(a->is_constant());
    return op(a->const_eval());
}