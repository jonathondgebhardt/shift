#include <string>

#include "shift/math/DegreesAngle.hpp"

// todo: throw or do math to put angle between [0, 360)?

namespace shift::math
{

DegreesAngle::DegreesAngle(float angle)
    : m_angle{angle}
{
}

auto DegreesAngle::set_angle(float angle) -> void
{
    m_angle = angle;
}

auto DegreesAngle::to_string() const -> std::string
{
    return std::to_string(m_angle);
}

}  // namespace shift::math
