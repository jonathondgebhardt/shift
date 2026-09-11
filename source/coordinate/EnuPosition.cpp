#include <format>
#include <string>

#include "shift/coordinate/EnuPosition.hpp"

namespace shift::coordinate
{

auto EnuPosition::to_string() const -> std::string
{
    return std::format("({}, {}, {})", east, north, up);
}

}  // namespace shift::coordinate
