#include <format>
#include <string>

#include "shift/time/Duration.hpp"

namespace shift::time
{

auto Duration::to_string() const -> std::string
{
    return std::format("{:%T}", m_duration);
}

}  // namespace shift::time
