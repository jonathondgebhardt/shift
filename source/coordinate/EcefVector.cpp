#include <cmath>
#include <format>
#include <string>

#include "shift/coordinate/EcefVector.hpp"

namespace shift::coordinate
{

auto EcefVector::magnitude() const -> double
{
    return std::hypot(x, y, z);
}

auto EcefVector::distance(const EcefVector lhs, const EcefVector rhs) -> double
{
    return (lhs - rhs).magnitude();
}

auto EcefVector::to_string() const -> std::string
{
    return std::format("({}, {}, {})", x, y, z);
}

}  // namespace shift::coordinate
