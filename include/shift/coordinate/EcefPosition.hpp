#pragma once

#include "shift/coordinate/EcefVector.hpp"
#include "shift/coordinate/shift_coordinate_export.hpp"

namespace shift::coordinate
{

struct SHIFT_COORDINATE_EXPORT EcefPosition
{
    double x{};
    double y{};
    double z{};

    constexpr EcefPosition() = default;

    constexpr explicit EcefPosition(double xyz)
        : x{xyz}
        , y{xyz}
        , z{xyz}
    {
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters,
    // readability-identifier-length)
    constexpr EcefPosition(double _x, double _y, double _z)
        : x{_x}
        , y{_y}
        , z{_z}
    {
    }

    // NOLINTEND(bugprone-easily-swappable-parameters,
    // readability-identifier-length)

    constexpr auto operator==(const EcefPosition other) const -> bool
    {
        return math::floating_point_eq(x, other.x)
            && math::floating_point_eq(y, other.y)
            && math::floating_point_eq(z, other.z);
    }

    friend constexpr auto operator+(const EcefPosition lhs,
                                    const EcefVector rhs) -> EcefPosition
    {
        auto tmp = lhs;
        return tmp += rhs;
    }

    constexpr auto operator+=(const EcefVector vector) -> EcefPosition&
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    friend constexpr auto operator-(const EcefPosition lhs,
                                    const EcefVector rhs) -> EcefPosition
    {
        auto tmp = lhs;
        return tmp -= rhs;
    }

    constexpr auto operator-=(const EcefVector vector) -> EcefPosition&
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
        return *this;
    }

    friend constexpr auto operator-(const EcefPosition lhs,
                                    const EcefPosition rhs) -> EcefVector
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    auto to_string() const -> std::string;
};

}  // namespace shift::coordinate
