#include <format>
#include <string>

#include "shift/math/DegreesAngle.hpp"

#include "shift/math/Utilities.hpp"

namespace
{

// todo: move this into math
auto fix_up(float angle_degrees) -> float
{
    constexpr auto lower_bound = 0.0f;
    constexpr auto upper_bound = 359.0f;

    if (angle_degrees >= lower_bound && angle_degrees <= upper_bound) {
        return angle_degrees;
    }

    // put angle_degrees within [0, 360)
    constexpr auto full_circle = 360.0f;
    while (angle_degrees > upper_bound) {
        angle_degrees -= full_circle;
    }
    while (angle_degrees < lower_bound) {
        angle_degrees += full_circle;
    }

    return angle_degrees;
}

}  // namespace

namespace shift::math
{

DegreesAngle::DegreesAngle(float angle)
    : m_angle{fix_up(angle)}
{
}

auto DegreesAngle::operator==(const DegreesAngle& other) const -> bool
{
    return math::floating_point_eq(m_angle, other.m_angle);
}

auto DegreesAngle::set_angle(float angle) -> void
{
    m_angle = fix_up(angle);
}

auto DegreesAngle::operator+=(const DegreesAngle& other) -> DegreesAngle&
{
    m_angle = fix_up(m_angle + other.m_angle);
    return *this;
}

auto DegreesAngle::operator-=(const DegreesAngle& other) -> DegreesAngle&
{
    m_angle = fix_up(m_angle - other.m_angle);
    return *this;
}

auto DegreesAngle::to_string() const -> std::string
{
    return std::format("{:.2f}", m_angle);
}

}  // namespace shift::math
