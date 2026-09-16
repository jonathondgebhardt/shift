#include <format>
#include <string>

#include "shift/coordinate/EulerOrientation.hpp"

#include "shift/math/DegreesAngle.hpp"

namespace shift::coordinate
{

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
EulerOrientation::EulerOrientation(float yaw, float pitch, float roll)
    : m_yaw{yaw}
    , m_pitch{pitch}
    , m_roll{roll}
{
}

auto EulerOrientation::yaw() const -> float
{
    return m_yaw.angle();
}

auto EulerOrientation::set_yaw(float yaw) -> void
{
    m_yaw.set_angle(yaw);
}

auto EulerOrientation::pitch() const -> float
{
    return m_pitch.angle();
}

auto EulerOrientation::set_pitch(float pitch) -> void
{
    m_pitch.set_angle(pitch);
}

auto EulerOrientation::roll() const -> float
{
    return m_roll.angle();
}

auto EulerOrientation::set_roll(float roll) -> void
{
    m_roll.set_angle(roll);
}

auto EulerOrientation::to_string() const -> std::string
{
    return std::format("({:.2f}, {:.2f}, {:.2f})",
                       m_yaw.angle(),
                       m_pitch.angle(),
                       m_roll.angle());
}

}  // namespace shift::coordinate
