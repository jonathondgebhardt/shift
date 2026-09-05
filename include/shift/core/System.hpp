#pragma once

#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
#include "shift/time/Clock.hpp"

namespace shift
{

using SystemUID = std::uint64_t;

class System
{
public:
    // todo: or a friend function
    explicit constexpr System(SystemUID uid)
        : m_uid{uid}
    {
    }

    System() = default;
    System(const System&) = default;
    System(System&&) noexcept = default;
    virtual ~System() = default;
    auto operator=(const System&) -> System& = default;
    auto operator=(System&&) noexcept -> System& = default;

    // todo: maybe systems should "schedule" their next update. that would
    // potentially be a complete shift away from other time updaters unless they
    // just ignored scheduling.

    auto uid() const { return m_uid; }

    virtual auto startup() -> void {}

    virtual auto first_update() -> UpdateResult = 0;

    virtual auto process(World& world, time::Clock::TimeStep time_step)
        -> UpdateResult = 0;

private:
    SystemUID m_uid{};
};

}  // namespace shift
