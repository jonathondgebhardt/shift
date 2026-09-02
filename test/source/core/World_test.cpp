#include "shift/core/World.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Entity.hpp"
#include "shift/core/UUID.hpp"

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

    const auto uuid = entity.uuid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(!uuid.empty());
    REQUIRE(!entity.name().empty());

    SECTION("UUID")
    {
        const auto entity_ref = world.find_entity(uuid);
        REQUIRE(!entity_ref.empty());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ref.unwrap().uuid() == uuid);
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

    const auto uuid = entity.uuid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(!uuid.empty());
    REQUIRE(!entity.name().empty());

    SECTION("UUID")
    {
        CHECK(world.remove_entity(uuid));
    }

    SECTION("name")
    {
        CHECK(world.remove_entity(name));
    }
}
