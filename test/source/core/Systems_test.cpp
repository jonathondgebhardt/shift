#include <memory>

#include "shift/core/Systems.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/System.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
#include "shift/time/Clock.hpp"

namespace
{

class TestSystem : public shift::System
{
public:
    auto first_update() -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_now();
    }

    auto process([[maybe_unused]] shift::World& world,
                 [[maybe_unused]] shift::time::Clock::TimeStep time_step)
        -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_now();
    }
};

}  // namespace

TEST_CASE("Systems add_system", "[core][Systems]")
{
    auto systems = shift::Systems{};

    SECTION("sets System UID")
    {
        systems.add_system(std::make_unique<TestSystem>());
        REQUIRE(!systems.systems().empty());

        CHECK(systems.systems().front()->uid() != shift::SystemUID{});
    }

    SECTION("add null system")
    {
        CHECK_NOTHROW(systems.add_system(nullptr));
    }
}

TEST_CASE("Systems remove_system", "[core][Systems]")
{
    auto systems = shift::Systems{};

    systems.add_system(std::make_unique<TestSystem>());
    REQUIRE(!systems.systems().empty());

    SECTION("one system")
    {
        const auto uid = systems.systems().back()->uid();
        REQUIRE(uid != shift::SystemUID{});

        CHECK(systems.remove_system(uid));
        CHECK(systems.systems().empty());
    }

    SECTION("two systems")
    {
        systems.add_system(std::make_unique<TestSystem>());
        REQUIRE(systems.systems().size() == 2u);

        const auto uid = systems.systems().back()->uid();
        REQUIRE(uid != shift::SystemUID{});

        CHECK(systems.remove_system(uid));
        CHECK(systems.systems().size() == 1u);

        SECTION("remove already removed system")
        {
            CHECK(!systems.remove_system(uid));
        }
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("Systems find_system", "[core][Systems]")
{
    auto systems = shift::Systems{};

    SECTION("no systems")
    {
        CHECK(systems.find_system(shift::SystemUID{}) == nullptr);
    }

    systems.add_system(std::make_unique<TestSystem>());
    REQUIRE(systems.systems().size() == 1u);

    const auto get_last_uid = [&]() { return systems.systems().back()->uid(); };

    SECTION("one system")
    {
        const auto uid = get_last_uid();
        const auto* system = systems.find_system(uid);
        REQUIRE(system != nullptr);
        CHECK(system->uid() == uid);
    }

    systems.add_system(std::make_unique<TestSystem>());
    REQUIRE(systems.systems().size() == 2u);

    SECTION("two systems")
    {
        const auto uid = get_last_uid();
        const auto* system = systems.find_system(uid);
        REQUIRE(system != nullptr);
        CHECK(system->uid() == uid);
    }
}

// NOLINTEND(readability-function-cognitive-complexity)
