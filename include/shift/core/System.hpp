#pragma once

#include "shift/core/World.hpp"
#include "shift/time/Clock.hpp"

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

    // todo: maybe systems should "schedule" their next update. that would
    // potentially be a complete shift away from other time updaters unless they
    // just ignored scheduling.

    virtual auto startup() -> void {}

    virtual auto process(World& world, time::Clock::TimeStep time_step)
        -> void = 0;

private:
};

}  // namespace shift
