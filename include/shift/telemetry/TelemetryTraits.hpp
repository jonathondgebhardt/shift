#pragma once

#include <cstdint>
#include <format>
#include <string>

// todo: move Vec3 out of Entity
#include "shift/core/Entity.hpp"

namespace shift::telemetry
{

template<typename T>
struct TelemetryTraits
{
    static auto to_string(const T& value) -> std::string
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
