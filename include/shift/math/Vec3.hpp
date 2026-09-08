#pragma once

#include <stdexcept>

#include "shift/math/Utilities.hpp"
#include "shift/math/shift_math_export.hpp"

namespace shift::math
{

struct SHIFT_MATH_EXPORT Vec3
{
    double x{};
    double y{};
    double z{};

    // NOLINTBEGIN(bugprone-easily-swappable-parameters,
    // readability-identifier-length)
    constexpr Vec3(double _x, double _y, double _z)
        : x{_x}
        , y{_y}
        , z{_z}
    {
    }

    // NOLINTEND(bugprone-easily-swappable-parameters,
    // readability-identifier-length)

    constexpr explicit Vec3(double xyz)
        : Vec3{xyz, xyz, xyz}
    {
    }

    constexpr Vec3() = default;

    constexpr auto operator==(const Vec3& other) const -> bool
    {
        return math::floating_point_eq(x, other.x)
            && math::floating_point_eq(y, other.y)
            && math::floating_point_eq(z, other.z);
    }

    friend constexpr auto operator+(const Vec3& lhs, const Vec3& rhs) -> Vec3
    {
        auto tmp = lhs;
        return tmp += rhs;
    }

    constexpr auto operator+=(const Vec3 vec) -> Vec3&
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }

    friend constexpr auto operator-(const Vec3& lhs, const Vec3 rhs) -> Vec3
    {
        auto tmp = lhs;
        return tmp -= rhs;
    }

    constexpr auto operator-=(const Vec3 vec) -> Vec3&
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }

    friend constexpr auto operator*(const Vec3& vec,
                                    const double scalar) -> Vec3
    {
        auto tmp = vec;
        return tmp *= scalar;
    }

    constexpr auto operator*=(const double scalar) -> Vec3&
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    friend constexpr auto operator/(Vec3 vec, const double scalar) -> Vec3
    {
        auto tmp = vec;
        return tmp /= scalar;
    }

    constexpr auto operator/=(const double scalar) -> Vec3&
    {
        if (floating_point_eq(scalar, 0.0)) {
            throw std::runtime_error("cannot divide Vec3 by zero");
        }

        // todo: check that scalar is not zero
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    auto magnitude() const -> double;

    static auto distance(Vec3 lhs, Vec3 rhs) -> double;

    static constexpr auto dot(const Vec3 lhs, const Vec3 rhs) -> double
    {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
    }

    static auto normalize(const Vec3 vec) -> Vec3
    {
        if (const auto magnitude = vec.magnitude();
            !floating_point_eq(magnitude, 0.0))
        {
            return vec / magnitude;
        }

        return {};
    }

    static constexpr auto cross(const Vec3 lhs, const Vec3 rhs) -> Vec3
    {
        // NOLINTBEGIN(readability-identifier-length)
        const auto i = (lhs.y * rhs.z) - (lhs.z * rhs.y);
        const auto j = (lhs.x * rhs.z) - (lhs.z * rhs.x);
        const auto k = (lhs.x * rhs.y) - (lhs.y * rhs.x);
        // NOLINTEND(readability-identifier-length)

        return {i, -j, k};
    }
};

}  // namespace shift::math
