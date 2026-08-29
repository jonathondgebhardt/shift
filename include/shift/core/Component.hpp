#pragma once

#include <string>
#include <string_view>

#include "shift/core/UUID.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Component
{
public:
    Component() = default;
    Component(const Component&) = default;
    Component(Component&&) noexcept = default;
    virtual ~Component() = default;
    auto operator=(const Component&) -> Component& = default;
    auto operator=(Component&&) noexcept -> Component& = default;

    virtual auto type() const -> const char* { return "Component"; }

    auto uuid() const -> UUID;

    auto set_name(std::string name) -> void;

    auto name() -> std::string_view { return m_name; }

private:
    SHIFT_SUPPRESS_C4251
    std::string m_name;
    UUID m_uuid{UUID::build()};
};

}  // namespace shift
