#include "Expression.h"


std::ostream& operator<<(std::ostream& sink, const Expression& expr)
{
    return expr.print(sink);
}
