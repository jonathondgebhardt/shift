#include "shift/core/World.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/coordinate/EnuFrame.hpp"
#include "shift/coordinate/GeodeticPosition.hpp"
#include "shift/core/Entity.hpp"

TEST_CASE("World add_entity", "[core][World]")
{
    auto world = shift::World{};
    REQUIRE(world.entities().empty());
    CHECK_NOTHROW(world.add_entity());
    CHECK(world.entities().size() == 1u);
}

TEST_CASE("World find_entity", "[core][World]")
{
    auto world = shift::World{};
    auto* entity = world.add_entity();
    REQUIRE(entity != nullptr);

    const auto uid = entity->uid();
    constexpr auto name = "name";
    entity->set_name(name);

    REQUIRE(uid != shift::EntityUID{});
    REQUIRE(!entity->name().empty());

    SECTION("uid")
    {
        auto* const entity_ptr = world.find_entity(uid);
        REQUIRE(entity_ptr != nullptr);
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ptr->uid() == uid);
    }

    SECTION("name")
    {
        auto* const entity_ptr = world.find_entity(name);
        REQUIRE(entity_ptr != nullptr);
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ptr->name() == name);
    }
}

TEST_CASE("World remove_entity", "[core][World]")
{
    auto world = shift::World{};
    auto* entity = world.add_entity();
    REQUIRE(entity != nullptr);

    const auto uid = entity->uid();
    constexpr auto name = "name";
    entity->set_name(name);

    REQUIRE(uid != shift::EntityUID{});
    REQUIRE(!entity->name().empty());

    SECTION("uid")
    {
        CHECK(world.remove_entity(uid));
    }

    SECTION("name")
    {
        CHECK(world.remove_entity(name));
    }
}

TEST_CASE("World reference frame", "[core][World]")
{
    auto world = shift::World{};

    SECTION("zero initialized")
    {
        CHECK(world.reference_frame() == shift::coordinate::EnuFrame{});
    }

    const auto reference_frame = shift::coordinate::EnuFrame{
        .origin = shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0},
    };
    world.set_reference_frame(reference_frame);

    CHECK(world.reference_frame() == reference_frame);
}
