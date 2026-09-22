#pragma once

#include <optional>
#include <string_view>

namespace shift::telemetry
{

template<typename Owner, typename Value>
class DataDefinition
{
public:
    using OwnerType = Owner;
    using ValueType = Value;
    using Getter = std::optional<Value> (*)(const Owner&);

    constexpr DataDefinition(std::string_view name, Getter getter)
        : m_name(name)
        , m_getter(getter)
    {
    }

    constexpr auto name() const noexcept -> std::string_view { return m_name; }

    auto get(const Owner& owner) const -> std::optional<Value>
    {
        return m_getter(owner);
    }

private:
    std::string_view m_name;
    Getter m_getter;
};

}  // namespace shift::telemetry
