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

    auto uid() const { return m_uid; }

    // todo: friend function
    auto set_uid(SystemUID uid) { m_uid = uid; }

    virtual auto startup() -> void {}

    virtual auto first_update() -> UpdateResult = 0;

    virtual auto update(World& world,
                        time::Clock::TimeStep time_step) -> UpdateResult = 0;

private:
    SystemUID m_uid{};
};

}  // namespace shift
