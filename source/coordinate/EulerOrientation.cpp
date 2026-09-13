#include "shift/coordinate/EulerOrientation.hpp"

#include "shift/math/DegreesAngle.hpp"

namespace shift::coordinate
{

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
EulerOrientation::EulerOrientation(math::DegreesAngle yaw,
                                   math::DegreesAngle pitch,
                                   math::DegreesAngle roll)
    : m_yaw{yaw}
    , m_pitch{pitch}
    , m_roll{roll}
{
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
EulerOrientation::EulerOrientation(float yaw, float pitch, float roll)
    : m_yaw{yaw}
    , m_pitch{pitch}
    , m_roll{roll}
{
}

auto EulerOrientation::set_yaw(float yaw) -> void
{
    m_yaw.set_angle(yaw);
}

auto EulerOrientation::set_pitch(float pitch) -> void
{
    m_pitch.set_angle(pitch);
}

auto EulerOrientation::set_roll(float roll) -> void
{
    m_roll.set_angle(roll);
}

}  // namespace shift::coordinate
