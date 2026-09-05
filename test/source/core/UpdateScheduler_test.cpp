#include "shift/core/UpdateScheduler.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/System.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/SimulationTime.hpp"

namespace
{

class TestSystem : public shift::System
{
public:
    static constexpr auto invalid_system() -> TestSystem
    {
        return TestSystem{shift::SystemUID{}};
    }

    static constexpr auto valid_system() -> TestSystem
    {
        return TestSystem{shift::SystemUID{1}};
    }

    auto first_update() -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_now();
    }

    auto process([[maybe_unused]] shift::World& world,
                 [[maybe_unused]] shift::time::Clock::TimeStep time_step)
        -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_after(
            shift::time::Duration{shift::time::Seconds{1}});
    }

private:
    constexpr explicit TestSystem(shift::SystemUID uid)
        : shift::System(uid)
    {
    }
};

}  // namespace

TEST_CASE("UpdateEvent operator<", "[core][UpdateEvent]")
{
    constexpr auto lhs = shift::UpdateEvent{
        .uid = shift::SystemUID{},
        .time = shift::time::SimulationTime{shift::time::Seconds{0}}};
    constexpr auto rhs = shift::UpdateEvent{
        .uid = shift::SystemUID{},
        .time = shift::time::SimulationTime{shift::time::Seconds{1}}};
    CHECK(lhs < rhs);
    CHECK(rhs >= lhs);
}

TEST_CASE("UpdateScheduler empty on ctor", "[core][UpdateScheduler]")
{
    CHECK(shift::UpdateScheduler{}.empty());
}

TEST_CASE("UpdateScheduler top empty", "[core][UpdateScheduler]")
{
    CHECK_NOTHROW(shift::UpdateScheduler{}.pop());
}

TEST_CASE("UpdateScheduler pop empty", "[core][UpdateScheduler]")
{
    CHECK(!shift::UpdateScheduler{}.top());
}

TEST_CASE("UpdateScheduler processed empty", "[core][UpdateScheduler]")
{
    CHECK(shift::UpdateScheduler{}.processed().empty());
}

TEST_CASE("UpdateScheduler schedule", "[core][UpdateScheduler]")
{
    auto scheduler = shift::UpdateScheduler{};
    constexpr auto sim_time =
        shift::time::SimulationTime{shift::time::Seconds{0}};

    SECTION("invalid system")
    {
        constexpr auto system = TestSystem::invalid_system();
        CHECK_THROWS(scheduler.schedule(system, sim_time));
        CHECK(scheduler.empty());
    }

    SECTION("valid system")
    {
        constexpr auto system = TestSystem::valid_system();
        CHECK_NOTHROW(scheduler.schedule(system, sim_time));
        CHECK(!scheduler.empty());
    }
}

TEST_CASE("UpdateScheduler pop", "[core][UpdateScheduler]")
{
    auto scheduler = shift::UpdateScheduler{};

    const auto schedule_event = [&](shift::time::Seconds time)
    {
        scheduler.schedule(TestSystem::valid_system(),
                           shift::time::SimulationTime{time});
    };

    // todo: mix time types?
    schedule_event(shift::time::Seconds{1});
    schedule_event(shift::time::Seconds{0});
    schedule_event(shift::time::Seconds{2});

    REQUIRE(!scheduler.empty());

    const auto check_and_pop = [&](shift::time::Seconds time)
    {
        const auto event = scheduler.top();
        REQUIRE(event);
        CHECK(event->time == shift::time::SimulationTime{time});
        scheduler.pop();
    };

    check_and_pop(shift::time::Seconds{0});
    check_and_pop(shift::time::Seconds{1});
    check_and_pop(shift::time::Seconds{2});
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("UpdateScheduler processed", "[core][UpdateScheduler]")
{
    auto scheduler = shift::UpdateScheduler{};

    const auto schedule_event = [&](shift::time::Seconds time)
    {
        scheduler.schedule(TestSystem::valid_system(),
                           shift::time::SimulationTime{time});
    };

    // todo: mix time types?
    schedule_event(shift::time::Seconds{1});
    schedule_event(shift::time::Seconds{0});
    schedule_event(shift::time::Seconds{2});

    REQUIRE(!scheduler.empty());
    CHECK(scheduler.processed().empty());

    const auto pop_and_check = [&](shift::time::Seconds time)
    {
        scheduler.pop();
        CHECK(scheduler.processed().back().time
              == shift::time::SimulationTime{time});
    };

    pop_and_check(shift::time::Seconds{0});
    CHECK(scheduler.processed().size() == 1u);
    pop_and_check(shift::time::Seconds{1});
    CHECK(scheduler.processed().size() == 2u);
    pop_and_check(shift::time::Seconds{2});
    CHECK(scheduler.processed().size() == 3u);
}

// NOLINTEND(readability-function-cognitive-complexity)
