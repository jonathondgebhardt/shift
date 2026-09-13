#pragma once

#include "shift/coordinate/shift_coordinate_export.hpp"
#include "shift/math/DegreesAngle.hpp"

namespace shift::coordinate
{

class SHIFT_COORDINATE_EXPORT EulerOrientation
{
public:
    EulerOrientation(math::DegreesAngle yaw,
                     math::DegreesAngle pitch,
                     math::DegreesAngle roll);
    EulerOrientation(float yaw, float pitch, float roll);

    constexpr EulerOrientation() = default;
    constexpr EulerOrientation(const EulerOrientation&) = default;
    constexpr EulerOrientation(EulerOrientation&&) noexcept = default;
    ~EulerOrientation() = default;
    constexpr auto operator=(const EulerOrientation&)
        -> EulerOrientation& = default;
    constexpr auto operator=(EulerOrientation&&) noexcept
        -> EulerOrientation& = default;

    auto yaw() const -> math::DegreesAngle { return m_yaw; }

    auto set_yaw(math::DegreesAngle yaw) -> void { m_yaw = yaw; }

    auto set_yaw(float yaw) -> void;

    auto pitch() const -> math::DegreesAngle { return m_pitch; }

    auto set_pitch(math::DegreesAngle pitch) -> void { m_pitch = pitch; }

    auto set_pitch(float pitch) -> void;

    auto roll() const -> math::DegreesAngle { return m_roll; }

    auto set_roll(math::DegreesAngle roll) -> void { m_roll = roll; }

    auto set_roll(float roll) -> void;

private:
    math::DegreesAngle m_yaw;
    math::DegreesAngle m_pitch;
    math::DegreesAngle m_roll;
};

}  // namespace shift::coordinate
