#pragma once

#include <format>
#include <string>

#include "shift/math/Vec3.hpp"

namespace shift::telemetry
{

template<typename T>
struct TelemetryTraits;

template<typename T>
concept ToStringable = requires(T value) {
    { std::to_string(value) } -> std::same_as<std::string>;
};

template<typename T>
    requires ToStringable<T>
struct TelemetryTraits<T>
{
    static auto to_string(const T& value) -> std::string
    {
        return std::to_string(value);
    }
};

template<>
struct TelemetryTraits<math::Vec3>
{
    static auto to_string(const math::Vec3& value) -> std::string
    {
        return std::format("({}, {}, {})", value.x, value.y, value.z);
    }
};

}  // namespace shift::telemetry
