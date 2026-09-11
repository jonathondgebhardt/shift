#pragma once

#include <stdexcept>
#include <string>

#include "shift/coordinate/shift_coordinate_export.hpp"
#include "shift/math/Utilities.hpp"

namespace shift::coordinate
{

struct SHIFT_COORDINATE_EXPORT EcefVector
{
    double x{};
    double y{};
    double z{};

    constexpr EcefVector() = default;

    constexpr explicit EcefVector(double xyz)
        : x{xyz}
        , y{xyz}
        , z{xyz}
    {
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters,
    // readability-identifier-length)
    constexpr EcefVector(double _x, double _y, double _z)
        : x{_x}
        , y{_y}
        , z{_z}
    {
    }

    // NOLINTEND(bugprone-easily-swappable-parameters,
    // readability-identifier-length)

    constexpr auto operator==(const EcefVector other) const -> bool
    {
        return math::floating_point_eq(x, other.x)
            && math::floating_point_eq(y, other.y)
            && math::floating_point_eq(z, other.z);
    }

    friend constexpr auto operator+(const EcefVector lhs, const EcefVector rhs)
        -> EcefVector
    {
        auto tmp = lhs;
        return tmp += rhs;
    }

    constexpr auto operator+=(const EcefVector vector) -> EcefVector&
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    friend constexpr auto operator-(const EcefVector lhs, const EcefVector rhs)
        -> EcefVector
    {
        auto tmp = lhs;
        return tmp -= rhs;
    }

    constexpr auto operator-=(const EcefVector vector) -> EcefVector&
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
        return *this;
    }

    friend constexpr auto operator*(const EcefVector vector,
                                    const double scalar) -> EcefVector
    {
        auto tmp = vector;
        return tmp *= scalar;
    }

    constexpr auto operator*=(const double scalar) -> EcefVector&
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    friend constexpr auto operator/(const EcefVector vector,
                                    const double scalar) -> EcefVector
    {
        auto tmp = vector;
        return tmp /= scalar;
    }

    constexpr auto operator/=(const double scalar) -> EcefVector&
    {
        if (math::floating_point_eq(scalar, 0.0)) {
            throw std::runtime_error("cannot divide Vec3 by zero");
        }

        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr auto operator-() const -> EcefVector { return {-x, -y, -z}; }

    static constexpr auto dot(const EcefVector lhs, const EcefVector rhs)
    {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
    }

    auto magnitude() const -> double;

    static auto distance(EcefVector lhs, EcefVector rhs) -> double;

    static auto normalize(const EcefVector vec) -> EcefVector
    {
        if (const auto magnitude = vec.magnitude();
            !math::floating_point_eq(magnitude, 0.0))
        {
            return vec / magnitude;
        }

        return {};
    }

    static constexpr auto cross(const EcefVector lhs, const EcefVector rhs)
        -> EcefVector
    {
        // NOLINTBEGIN(readability-identifier-length)
        const auto i = (lhs.y * rhs.z) - (lhs.z * rhs.y);
        const auto j = (lhs.x * rhs.z) - (lhs.z * rhs.x);
        const auto k = (lhs.x * rhs.y) - (lhs.y * rhs.x);
        // NOLINTEND(readability-identifier-length)

        return {i, -j, k};
    }

    auto to_string() const -> std::string;
};

}  // namespace shift::coordinate
