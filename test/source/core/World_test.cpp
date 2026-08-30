#include <utility>

#include "shift/core/World.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Entity.hpp"
#include "shift/core/UUID.hpp"

TEST_CASE("World add_entity", "[core][World]")
{
    auto world = shift::World{};
    REQUIRE(world.entities().empty());
    CHECK_NOTHROW(world.add_entity(shift::Entity{}));
    CHECK(world.entities().size() == 1u);
}

TEST_CASE("World find_entity", "[core][World]")
{
    auto entity = shift::Entity{};
    const auto uuid = entity.uuid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(!uuid.empty());
    REQUIRE(!entity.name().empty());

    auto world = shift::World{};
    CHECK_NOTHROW(world.add_entity(std::move(entity)));

    SECTION("UUID")
    {
        const auto entity_ref = world.find_entity(uuid);
        REQUIRE(entity_ref.has_value());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ref.value().get().uuid() == uuid);
    }

    SECTION("name")
    {
        const auto entity_ref = world.find_entity(name);
        REQUIRE(entity_ref.has_value());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        CHECK(entity_ref.value().get().name() == name);
    }
}

TEST_CASE("World remove_entity", "[core][World]")
{
    auto entity = shift::Entity{};
    const auto uuid = entity.uuid();
    constexpr auto name = "name";
    entity.set_name(name);

    REQUIRE(!uuid.empty());
    REQUIRE(!entity.name().empty());

    auto world = shift::World{};
    CHECK_NOTHROW(world.add_entity(std::move(entity)));

    SECTION("UUID")
    {
        CHECK(world.remove_entity(uuid));
    }

    SECTION("name")
    {
        CHECK(world.remove_entity(name));
    }
}
