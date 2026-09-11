#pragma once

#include <string>

#include "shift/coordinate/EnuVector.hpp"
#include "shift/coordinate/shift_coordinate_export.hpp"

namespace shift::coordinate
{

struct SHIFT_COORDINATE_EXPORT EnuPosition
{
    double east{};
    double north{};
    double up{};

    constexpr EnuPosition() = default;

    constexpr explicit EnuPosition(double enu)
        : east{enu}
        , north{enu}
        , up{enu}
    {
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters,
    // readability-identifier-length)
    constexpr EnuPosition(double _east, double _north, double _up)
        : east{_east}
        , north{_north}
        , up{_up}
    {
    }

    // NOLINTEND(bugprone-easily-swappable-parameters,
    // readability-identifier-length)

    constexpr auto operator==(const EnuPosition other) const -> bool
    {
        return math::floating_point_eq(east, other.east)
            && math::floating_point_eq(north, other.north)
            && math::floating_point_eq(up, other.up);
    }

    friend constexpr auto operator+(const EnuPosition lhs, const EnuVector rhs)
        -> EnuPosition
    {
        auto tmp = lhs;
        return tmp += rhs;
    }

    constexpr auto operator+=(const EnuVector vector) -> EnuPosition&
    {
        east += vector.east;
        north += vector.north;
        up += vector.up;
        return *this;
    }

    friend constexpr auto operator-(const EnuPosition lhs, const EnuVector rhs)
        -> EnuPosition
    {
        auto tmp = lhs;
        return tmp -= rhs;
    }

    constexpr auto operator-=(const EnuVector vector) -> EnuPosition&
    {
        east -= vector.east;
        north -= vector.north;
        up -= vector.up;
        return *this;
    }

    friend constexpr auto operator-(const EnuPosition lhs,
                                    const EnuPosition rhs) -> EnuVector
    {
        return {lhs.east - rhs.east, lhs.north - rhs.north, lhs.up - rhs.up};
    }

    auto to_string() const -> std::string;
};

}  // namespace shift::coordinate
