#pragma once

#include "shift/coordinate/shift_coordinate_export.hpp"
#include "shift/math/DegreesAngle.hpp"

namespace shift::coordinate
{

class SHIFT_COORDINATE_EXPORT EulerOrientation
{
public:
    EulerOrientation(float yaw, float pitch, float roll);

    constexpr EulerOrientation() = default;
    constexpr EulerOrientation(const EulerOrientation&) = default;
    constexpr EulerOrientation(EulerOrientation&&) noexcept = default;
    ~EulerOrientation() = default;
    constexpr auto operator=(const EulerOrientation&)
        -> EulerOrientation& = default;
    constexpr auto operator=(EulerOrientation&&) noexcept
        -> EulerOrientation& = default;

    auto operator==(const EulerOrientation&) const -> bool = default;

    auto yaw() const -> float;

    auto set_yaw(float yaw) -> void;

    auto pitch() const -> float;

    auto set_pitch(float pitch) -> void;

    auto roll() const -> float;

    auto set_roll(float roll) -> void;

private:
    math::DegreesAngle m_yaw;
    math::DegreesAngle m_pitch;
    math::DegreesAngle m_roll;
};

}  // namespace shift::coordinate
