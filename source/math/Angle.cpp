#include "shift/math/Angle.hpp"

// todo: throw or do math to put angle between [0, 360)?

namespace shift::math
{

Angle::Angle(float angle)
    : m_angle{angle}
{
}

auto Angle::set_angle(float angle) -> void
{
    m_angle = angle;
}

}  // namespace shift::math
