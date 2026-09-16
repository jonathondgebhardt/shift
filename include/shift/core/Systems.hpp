#pragma once

#include <memory>
#include <vector>

#include "shift/core/System.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Systems
{
public:
    Systems() = default;
    Systems(const Systems&) = delete;
    Systems(Systems&&) noexcept = default;
    ~Systems() = default;
    auto operator=(const Systems&) -> Systems& = delete;
    auto operator=(Systems&&) noexcept -> Systems& = default;

    auto add_system(std::unique_ptr<System> system) -> void;

    auto remove_system(SystemUID uid) -> bool;

    auto find_system(SystemUID uid) -> System*;

    auto systems() const -> std::span<const std::unique_ptr<System>>
    {
        return m_systems;
    }

    auto startup(const World& world) -> void;

private:
    SHIFT_SUPPRESS_C4251
    std::vector<std::unique_ptr<System>> m_systems;
};

}  // namespace shift
