#pragma once

#include <cstdint>
#include <format>
#include <string>

// todo: move Vec3 out of Entity
#include "shift/core/Entity.hpp"

namespace shift::telemetry
{

// template<typename T>
//     requires std::is_convertible_v<T, std::string>
// struct TelemetryTraits
// {
// };

template<typename T>
struct TelemetryTraits;

// todo: can I do something like this?
// template<typename T>
//     requires std::is_convertible_v<T, std::string>
// struct TelemetryTraits
// {
//     static auto to_string(double value) -> std::string
//     {
//         return std::to_string(value);
//     }
// };

template<>
struct TelemetryTraits<double>
{
    static auto to_string(double value) -> std::string
    {
        return std::to_string(value);
    }
};

template<>
struct TelemetryTraits<float>
{
    static auto to_string(float value) -> std::string
    {
        return std::to_string(value);
    }
};

template<>
struct TelemetryTraits<int>
{
    static auto to_string(int value) -> std::string
    {
        return std::to_string(value);
    }
};

template<>
struct TelemetryTraits<std::int64_t>
{
    static auto to_string(std::int64_t value) -> std::string
    {
        return std::to_string(value);
    }
};

template<>
struct TelemetryTraits<Vec3>
{
    static auto to_string(const Vec3& value) -> std::string
    {
        return std::format("({}, {}, {})", value.x, value.y, value.z);
    }
};

}  // namespace shift::telemetry
