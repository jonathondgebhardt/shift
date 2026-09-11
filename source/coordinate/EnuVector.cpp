#include <format>
#include <string>

#include "shift/coordinate/EnuVector.hpp"

namespace shift::coordinate
{

auto EnuVector::to_string() const -> std::string
{
    return std::format("({}, {}, {})", east, north, up);
}

}  // namespace shift::coordinate
