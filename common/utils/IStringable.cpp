#include "IStringable.hpp"

std::ostream& operator<<(std::ostream& lhs, IStringable const& rhs)
{
    lhs << rhs.toString();
    return lhs;
}
