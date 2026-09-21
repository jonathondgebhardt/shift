#include <format>
#include <string>

#include "shift/time/TimePoint.hpp"

namespace shift::time
{

auto TimePoint::to_string() const -> std::string
{
    return std::format("{:%T}", m_time);
}

}  // namespace shift::time
