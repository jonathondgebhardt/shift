#include "shift/core/World.hpp"

#include <catch2/catch_test_macros.hpp>

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
    auto& entity = world.add_entity();

    const auto uid = entity.uid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(uid != shift::EntityUID{});
    REQUIRE(!entity.name().empty());

    SECTION("uid")
    {
        const auto entity_ref = world.find_entity(uid);
        REQUIRE(!entity_ref.empty());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ref.unwrap().uid() == uid);
    }

    SECTION("name")
    {
        const auto entity_ref = world.find_entity(name);
        REQUIRE(!entity_ref.empty());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ref.unwrap().name() == name);
    }
}

TEST_CASE("World remove_entity", "[core][World]")
{
    auto world = shift::World{};
    auto& entity = world.add_entity();

    const auto uid = entity.uid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(uid != shift::EntityUID{});
    REQUIRE(!entity.name().empty());

    SECTION("uid")
    {
        CHECK(world.remove_entity(uid));
    }

    SECTION("name")
    {
        CHECK(world.remove_entity(name));
    }
}
