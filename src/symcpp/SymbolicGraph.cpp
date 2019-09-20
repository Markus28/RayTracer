#include <iostream>
#include <cassert>
#include "SymbolicGraph.h"
#include "Add.h"
#include "Multiply.h"
#include "Divide.h"
#include "Subtract.h"
#include "Power.h"
#include "Sine.h"
#include "Cosine.h"
#include "Exponential.h"


SymbolicGraph::SymbolicGraph(const Expression &h) {
    head = h.copy();
}

SymbolicGraph::SymbolicGraph(const std::unique_ptr<Expression> &h) {
    head = h->copy();
}

SymbolicGraph::SymbolicGraph(const SymbolicGraph &other) {
    head = other.head->copy();
}

double SymbolicGraph::subs(const std::unordered_map<std::string, double> &env) const {
    return head->subs(env);
}

SymbolicGraph SymbolicGraph::diff(std::string var) const {
    return SymbolicGraph(head->diff(var)->simplify());
}

SymbolicGraph& SymbolicGraph::operator=(const SymbolicGraph &other) {
    head = other.head->copy();
    return *this;
}

SymbolicGraph& SymbolicGraph::operator+=(const SymbolicGraph &other) {
    head = std::unique_ptr<Expression>(new Add(std::move(head), other.head->copy()));
    return *this;
}

SymbolicGraph& SymbolicGraph::operator*=(const SymbolicGraph &other) {
    head = std::unique_ptr<Expression>(new Multiply(std::move(head), other.head->copy()));
    return *this;
}

SymbolicGraph& SymbolicGraph::operator/=(const SymbolicGraph &other) {
    head = std::unique_ptr<Expression>(new Divide(head, other.head));
    return *this;
}

SymbolicGraph& SymbolicGraph::operator-=(const SymbolicGraph &other) {
    head = std::unique_ptr<Expression>(new Subtract(head, other.head));
    return *this;
}

SymbolicGraph operator+(SymbolicGraph a, const SymbolicGraph& b){
    a += b;
    return a;
}

SymbolicGraph operator*(SymbolicGraph a, const SymbolicGraph& b){
    a *= b;
    return a;
}

SymbolicGraph operator-(SymbolicGraph a, const SymbolicGraph& b){
    a -= b;
    return a;
}

SymbolicGraph operator/(SymbolicGraph a, const SymbolicGraph& b){
    a /= b;
    return a;
}

std::ostream& operator<<(std::ostream& sink, const SymbolicGraph& obj){
    return sink<<*obj.head;
}

SymbolicGraph operator^(const SymbolicGraph& a, const SymbolicGraph& b){
    return SymbolicGraph(Power(a.head->copy(), b.head->copy()));
}

void SymbolicGraph::simplify() {
    head = head->simplify();
}

/*
 * EBNF For Math-Expressions:
 *
 * SUM = TERM {'+' TERM | '-' TERM}
 * TERM = FACTOR{'*' FACTOR| '/' FACTOR|}
 * FACTOR = BASE['^'BASE]
 * BASE = VAR | DOUBLE | '(' SUM ')' | 'sin(' SUM ')' | ...
 *
 * NO WHITESPACES!
*/

struct ComplexToken{
    enum Type{
        VAR, SIN, COS, EXP, LOG
    };
    ComplexToken(): name("") {};
    std::string name;
    Type get_type() {
        if(name=="sin")
            return Type::SIN;
        if(name=="cos")
            return Type::COS;
        if(name=="exp")
            return Type::EXP;
        if(name=="log")
            return Type::LOG;

        return Type::VAR;
    }
};

std::istream& operator>>(std::istream& in, ComplexToken& a){
    char b;
    bool wrote_something = false;
    while((in.peek()<=90 && in.peek()>=65) || (in.peek()<=122 && in.peek()>=97)){
        in>>b;
        a.name.push_back(b);
        wrote_something = true;
    }
    if(!wrote_something)
        in.setstate(std::istream::failbit);
    return in;
}

SymbolicGraph parse_sum(std::istream& in);

SymbolicGraph parse_base(std::istream &in){
    double a;
    char ignore;


    if(in.peek()=='('){
        in>>ignore;
        SymbolicGraph result = parse_sum(in);
        assert(in.peek()==')');
        in>>ignore;
        return result;
    }

    ComplexToken b;

    if(in>>b){
        SymbolicGraph result;
        switch(b.get_type()){
            case ComplexToken::Type::SIN: {
                in >> ignore;
                assert(ignore == '(');
                result = Sine(parse_sum(in));
                in >> ignore;
                assert(ignore == ')');
                return result;
            }
            case ComplexToken::Type::COS: {
                in >> ignore;
                assert(ignore == '(');
                result = Cosine(parse_sum(in));
                in >> ignore;
                assert(ignore == ')');
                return result;
            }
            case ComplexToken::Type::EXP: {
                in >> ignore;
                assert(ignore == '(');
                result = Exponential(parse_sum(in));
                in >> ignore;
                assert(ignore == ')');
                return result;
            }
            case ComplexToken::Type::LOG: {
                in >> ignore;
                assert(ignore == '(');
                result = Cosine(parse_sum(in));
                in >> ignore;
                assert(ignore == ')');
                return result;
            }
            default: {
                result = Variable(b.name);
                return result;
            }
        }
    }

    in.clear();

    if(in>>a){
        return Constant(a);
    }

    assert(false);
}

SymbolicGraph parse_factor(std::istream &in){
    SymbolicGraph a = parse_base(in);
    char ignore;
    if(in.peek()=='^'){
        in>>ignore;
        return a^parse_base(in);
    }
    return a;
}

SymbolicGraph parse_term(std::istream& in){
    char ignore;
    SymbolicGraph result = parse_factor(in);
    while(!in.eof()) {
        if (in.peek() == '*') {
            in >> ignore;
            result *= parse_factor(in);
        }

        else if (in.peek() == '/') {
            in >> ignore;
            result /= parse_factor(in);
            return result;
        }

        else
            return result;
    }

    return result;
}

SymbolicGraph parse_sum(std::istream& in){
    SymbolicGraph result;
    char last_op = '+';
    while(true){
        SymbolicGraph expr = parse_term(in);
        if(last_op=='+')
            result += expr;
        else
            result -= expr;

        if(in.peek()!='+' && in.peek()!='-')
            return result;
        in>>last_op;
    }
}

std::istream& operator>>(std::istream& in, SymbolicGraph& a){
    a = parse_sum(in);
    a.simplify();
    return in;
}