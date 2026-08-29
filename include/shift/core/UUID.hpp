#pragma once

#include <cstdint>
#include <string>

#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT UUID
{
public:
    static auto build() -> UUID;

    auto to_string() const -> std::string;
    auto empty() const -> bool;

    auto operator<=>(const UUID&) const noexcept -> bool = default;

private:
    UUID(std::uint64_t first, std::uint64_t second)
        : m_first{first}
        , m_second{second}
    {
    }

    std::uint64_t m_first{};
    std::uint64_t m_second{};
};

}  // namespace shift
