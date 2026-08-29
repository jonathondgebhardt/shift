#pragma once

#include <string>
#include <string_view>

#include "shift/core/UUID.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Object
{
public:
    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) noexcept = default;
    virtual ~Object() = default;
    auto operator=(const Object&) -> Object& = default;
    auto operator=(Object&&) noexcept -> Object& = default;

    virtual auto type() const -> const char* { return "Object"; }

    auto uuid() const -> UUID;

    auto set_name(std::string name) -> void;

    auto name() const -> std::string_view { return m_name; }

private:
    SHIFT_SUPPRESS_C4251
    std::string m_name;
    UUID m_uuid{UUID::build()};
};

}  // namespace shift
