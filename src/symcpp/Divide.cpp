#include "Divide.h"
#include "Multiply.h"
#include "Subtract.h"
#include "Constant.h"
#include <iostream>
#include <cassert>

Divide::Divide(const Expression &a, const Expression &b): a(a.copy()), b(b.copy()) {}

Divide::Divide(const std::unique_ptr<Expression> &a, const std::unique_ptr<Expression> &b): a(a->copy()), b(b->copy()) {}

std::unique_ptr<Expression> Divide::copy() const{
    std::unique_ptr<Expression> p (new Divide(a, b));
    return p;
}

std::unique_ptr<Expression> Divide::diff(std::string v) const {
    std::unique_ptr<Expression> p (new Divide(Subtract(Multiply(a->diff(v), b->copy()), Multiply(a->copy(), b->diff(v))), Multiply(b->copy(), b->copy())));
    return p;
}

double Divide::subs(const std::unordered_map<std::string, double> &env) const {
    return a->subs(env)/b->subs(env);
}

unsigned int Divide::precedence() const {
    return 4;
}

std::ostream& Divide::print(std::ostream &sink) const {
    if(a->precedence()<=4)
        sink<<"("<<*a<<")";
    else
        sink<<*a;

    sink<<"/";

    if(b->precedence()<=4)
        sink<<"("<<*b<<")";
    else
        sink<<*b;

    return sink;
}

bool Divide::is_constant() const {
    return (a->is_constant()&&b->is_constant()) || (a->is_constant() && a->const_eval()==0);
}

double Divide::const_eval() const {
    assert(is_constant());
    double a_val = a->const_eval();
    if(a==0)
        return 0;

    return a_val*b->const_eval();
}

std::unique_ptr<Expression> Divide::simplify() {
    if(a->is_constant()){
        double a_val = a->const_eval();

        if(a_val==0){
            std::unique_ptr<Expression> p(new Constant(0));
            return p;
        }

        if(b->is_constant()){
            std::unique_ptr<Expression> p(new Constant(a_val/b->const_eval()));
            return p;
        }
    }

    if(b->is_constant()&&b->const_eval()==1){
        a->simplify();
    }

    std::unique_ptr<Expression> p(new Divide(a->simplify(), b->simplify()));
    return p;
}