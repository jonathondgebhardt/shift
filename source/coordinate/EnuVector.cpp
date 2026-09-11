#include <cmath>
#include <format>
#include <string>

#include "shift/coordinate/EnuVector.hpp"

namespace shift::coordinate
{

auto EnuVector::magnitude() const -> double
{
    return std::hypot(east, north, up);
}

auto EnuVector::distance(const EnuVector lhs, const EnuVector rhs) -> double
{
    return (lhs - rhs).magnitude();
}

auto EnuVector::to_string() const -> std::string
{
    return std::format("({}, {}, {})", east, north, up);
}

}  // namespace shift::coordinate
