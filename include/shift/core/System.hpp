#pragma once

#include "shift/core/Clock.hpp"
#include "shift/core/World.hpp"

namespace shift
{

class System
{
public:
    System() = default;
    System(const System&) = default;
    System(System&&) noexcept = default;
    virtual ~System() = default;
    auto operator=(const System&) -> System& = default;
    auto operator=(System&&) noexcept -> System& = default;

    virtual auto startup() -> void {}

    virtual auto process(World& world, Clock::TimeStep time_step) -> void = 0;

private:
};

}  // namespace shift
