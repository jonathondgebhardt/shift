#pragma once

#include <stdexcept>
#include <string>

#include "shift/coordinate/shift_coordinate_export.hpp"
#include "shift/math/Utilities.hpp"

namespace shift::coordinate
{

struct SHIFT_COORDINATE_EXPORT EnuVector
{
    double east{};
    double north{};
    double up{};

    constexpr EnuVector() = default;

    constexpr explicit EnuVector(double enu)
        : east{enu}
        , north{enu}
        , up{enu}
    {
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters,
    // readability-identifier-length)
    constexpr EnuVector(double _east, double _north, double _up)
        : east{_east}
        , north{_north}
        , up{_up}
    {
    }

    // NOLINTEND(bugprone-easily-swappable-parameters,
    // readability-identifier-length)

    constexpr auto operator==(const EnuVector other) const -> bool
    {
        return math::floating_point_eq(east, other.east)
            && math::floating_point_eq(north, other.north)
            && math::floating_point_eq(up, other.up);
    }

    friend constexpr auto operator+(const EnuVector lhs, const EnuVector rhs)
        -> EnuVector
    {
        auto tmp = lhs;
        return tmp += rhs;
    }

    constexpr auto operator+=(const EnuVector vector) -> EnuVector&
    {
        east += vector.east;
        north += vector.north;
        up += vector.up;
        return *this;
    }

    friend constexpr auto operator-(const EnuVector lhs, const EnuVector rhs)
        -> EnuVector
    {
        auto tmp = lhs;
        return tmp -= rhs;
    }

    constexpr auto operator-=(const EnuVector vector) -> EnuVector&
    {
        east -= vector.east;
        north -= vector.north;
        up -= vector.up;
        return *this;
    }

    friend constexpr auto operator*(const EnuVector vector, const double scalar)
        -> EnuVector
    {
        auto tmp = vector;
        return tmp *= scalar;
    }

    constexpr auto operator*=(const double scalar) -> EnuVector&
    {
        east *= scalar;
        north *= scalar;
        up *= scalar;
        return *this;
    }

    friend constexpr auto operator/(const EnuVector vector, const double scalar)
        -> EnuVector
    {
        auto tmp = vector;
        return tmp /= scalar;
    }

    constexpr auto operator/=(const double scalar) -> EnuVector&
    {
        if (math::floating_point_eq(scalar, 0.0)) {
            throw std::runtime_error("cannot divide Vec3 by zero");
        }

        east /= scalar;
        north /= scalar;
        up /= scalar;
        return *this;
    }

    constexpr auto operator-() const -> EnuVector
    {
        return {-east, -north, -up};
    }

    static constexpr auto dot(const EnuVector lhs, const EnuVector rhs)
    {
        return (lhs.east * rhs.east) + (lhs.north * rhs.north)
            + (lhs.up * rhs.up);
    }

    auto magnitude() const -> double;

    static auto distance(EnuVector lhs, EnuVector rhs) -> double;

    static auto normalize(const EnuVector vec) -> EnuVector
    {
        if (const auto magnitude = vec.magnitude();
            !math::floating_point_eq(magnitude, 0.0))
        {
            return vec / magnitude;
        }

        return {};
    }

    static constexpr auto cross(const EnuVector lhs, const EnuVector rhs)
        -> EnuVector
    {
        // NOLINTBEGIN(readability-identifier-length)
        const auto i = (lhs.north * rhs.up) - (lhs.up * rhs.north);
        const auto j = (lhs.east * rhs.up) - (lhs.up * rhs.east);
        const auto k = (lhs.east * rhs.north) - (lhs.north * rhs.east);
        // NOLINTEND(readability-identifier-length)

        return {i, -j, k};
    }

    auto to_string() const -> std::string;
};

}  // namespace shift::coordinate
