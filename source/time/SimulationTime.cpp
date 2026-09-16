#include <format>
#include <string>

#include "shift/time/SimulationTime.hpp"

namespace shift::time
{

auto SimulationTime::to_string() const -> std::string
{
    return std::format("{:%T}", m_time);
}

}  // namespace shift::time
