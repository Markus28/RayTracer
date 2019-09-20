#include "Constant.h"
#include <iostream>

Constant::Constant(double c): c(c){}

std::unique_ptr<Expression> Constant::copy() const {
    std::unique_ptr<Expression> p (new Constant(c));
    return p;
}

std::unique_ptr<Expression> Constant::diff(std::string var) const {
    std::unique_ptr<Expression> p (new Constant(0));
    return p;
}

double Constant::subs(const std::unordered_map<std::string, double> &env) const {
    return c;
}

unsigned int Constant::precedence() const {
    return 6;
}

std::ostream& Constant::print(std::ostream &sink) const {
    return sink<<c;
}

bool Constant::is_constant() const {
    return true;
}

double Constant::const_eval() const {
    return c;
}

std::unique_ptr<Expression> Constant::simplify() {
    return copy();                  //TODO: without copying
}