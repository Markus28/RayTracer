#ifndef RAYTRACER_SYMBOLICGRAPH_H
#define RAYTRACER_SYMBOLICGRAPH_H

#include "Expression.h"
#include "Constant.h"
#include "Variable.h"


class SymbolicGraph {
public:
    SymbolicGraph(): head(new Constant(0)) {};
    SymbolicGraph(double a): head(new Constant(a)) {};
    SymbolicGraph(std::string v): head(new Variable(v)) {};
    SymbolicGraph(const SymbolicGraph& other);
    SymbolicGraph(const Expression& h);
    explicit SymbolicGraph(const std::unique_ptr<Expression>& h);
    SymbolicGraph& operator=(const SymbolicGraph& other);
    SymbolicGraph diff(std::string var) const;
    void simplify();
    double subs(const std::unordered_map<std::string, double>& env) const;
    SymbolicGraph& operator+=(const SymbolicGraph& other);
    SymbolicGraph& operator*=(const SymbolicGraph& other);
    SymbolicGraph& operator-=(const SymbolicGraph& other);
    SymbolicGraph&operator/=(const SymbolicGraph& other);

    operator std::unique_ptr<Expression>() const{return head->copy();};

private:
    friend SymbolicGraph operator+(SymbolicGraph a, const SymbolicGraph& b);
    friend SymbolicGraph operator*(SymbolicGraph a, const SymbolicGraph& b);
    friend SymbolicGraph operator/(SymbolicGraph a, const SymbolicGraph& b);
    friend SymbolicGraph operator-(SymbolicGraph a, const SymbolicGraph& b);
    friend std::ostream& operator<<(std::ostream& sink, const SymbolicGraph& obj);
    friend SymbolicGraph operator^(const SymbolicGraph& a, const SymbolicGraph& b);
    std::unique_ptr<Expression> head;
};

SymbolicGraph operator+(SymbolicGraph a, const SymbolicGraph& b);
SymbolicGraph operator*(SymbolicGraph a, const SymbolicGraph& b);
std::ostream& operator<<(std::ostream& sink, const SymbolicGraph& obj);
SymbolicGraph operator/(SymbolicGraph a, const SymbolicGraph& b);
SymbolicGraph operator-(SymbolicGraph a, const SymbolicGraph& b);
SymbolicGraph operator^(const SymbolicGraph& a, const SymbolicGraph& b);
std::istream& operator>>(std::istream& in, SymbolicGraph& a);


#endif //RAYTRACER_SYMBOLICGRAPH_H
