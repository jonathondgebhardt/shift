#pragma once

#include <string>

#include "shift/math/shift_math_export.hpp"

namespace shift::math
{

class SHIFT_MATH_EXPORT DegreesAngle
{
public:
    explicit DegreesAngle(float angle);

    constexpr DegreesAngle() = default;
    constexpr DegreesAngle(const DegreesAngle&) = default;
    constexpr DegreesAngle(DegreesAngle&&) noexcept = default;
    ~DegreesAngle() = default;
    constexpr auto operator=(const DegreesAngle&) -> DegreesAngle& = default;
    constexpr auto operator=(DegreesAngle&&) noexcept
        -> DegreesAngle& = default;

    constexpr auto angle() const -> float { return m_angle; }

    auto set_angle(float angle) -> void;

    // todo: consider adding overloads for float

    friend auto operator+(const DegreesAngle& lhs, const DegreesAngle& rhs)
        -> DegreesAngle
    {
        auto temp = lhs;
        return temp += rhs;
    }

    auto operator+=(const DegreesAngle& other) -> DegreesAngle&;

    friend auto operator-(const DegreesAngle& lhs, const DegreesAngle& rhs)
        -> DegreesAngle
    {
        auto temp = lhs;
        return temp -= rhs;
    }

    auto operator-=(const DegreesAngle& other) -> DegreesAngle&;

    auto to_string() const -> std::string;

private:
    float m_angle{};
};

}  // namespace shift::math
