#include "Expression.h"

namespace symcpp {
    std::ostream &operator<<(std::ostream &sink, const Expression &expr) {
        return expr.print(sink);
    }
}