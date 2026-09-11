#include <format>
#include <string>

#include "shift/coordinate/EcefPosition.hpp"

namespace shift::coordinate
{

auto EcefPosition::to_string() const -> std::string
{
    return std::format("({}, {}, {})", x, y, z);
}

}  // namespace shift::coordinate
