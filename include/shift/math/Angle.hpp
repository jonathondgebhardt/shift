#pragma once

#include "shift/math/shift_math_export.hpp"

namespace shift::math
{

class SHIFT_MATH_EXPORT Angle
{
public:
    explicit Angle(float angle);

    constexpr Angle() = default;
    constexpr Angle(const Angle&) = default;
    constexpr Angle(Angle&&) noexcept = default;
    ~Angle() = default;
    constexpr auto operator=(const Angle&) -> Angle& = default;
    constexpr auto operator=(Angle&&) noexcept -> Angle& = default;

    constexpr auto angle() const -> float { return m_angle; }

    auto set_angle(float angle) -> void;

private:
    float m_angle{};
};

}  // namespace shift::math
