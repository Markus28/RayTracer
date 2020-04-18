#include "Variable.h"
#include "Constant.h"
#include <cassert>

namespace symcpp {
    Variable::Variable(std::string name) : name(name) {}

    std::unique_ptr<Expression> Variable::copy() const {
        std::unique_ptr<Expression> p(new Variable(name));
        return p;
    }

    std::unique_ptr<Expression> Variable::diff(std::string v) const {
        int d = 0;
        if (v == name) {
            d = 1;
        }
        std::unique_ptr<Expression> p(new Constant(d));
        return p;
    }

    double Variable::subs(const std::unordered_map<std::string, double> &env) const {
        return env.at(name);
    }

    std::ostream &Variable::print(std::ostream &other) const {
        return other << name;
    }

    unsigned int Variable::precedence() const {
        return 6;
    }

    bool Variable::is_constant() const {
        return false;
    }

    double Variable::const_eval() const {
        assert(false);
        return 0;
    }

    std::unique_ptr<Expression> Variable::simplify() {
        return copy();
    }
}