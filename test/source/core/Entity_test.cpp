#include <memory>
#include <utility>

#include "shift/core/Entity.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "shift/coordinate/EcefPosition.hpp"
#include "shift/coordinate/EcefVector.hpp"
#include "shift/coordinate/EulerOrientation.hpp"
#include "shift/core/Component.hpp"

TEST_CASE("Entity uid zero on ctor", "[core][Entity]")
{
    CHECK(shift::Entity{}.uid() == shift::EntityUID{});
}

TEST_CASE("Entity name", "[core][Entity]")
{
    auto object = shift::Entity{};

    SECTION("empty on construction")
    {
        REQUIRE(object.name().empty());
    }

    constexpr auto name = "name";
    object.set_name(name);
    SECTION("populated by setter")
    {
        REQUIRE(object.name() == name);
    }
}

TEST_CASE("Entity add_component", "[core][Entity]")
{
    auto object = shift::Entity{};

    SECTION("pass component")
    {
        CHECK(object.add_component(std::make_unique<shift::Component>()));
    }

    SECTION("templated")
    {
        CHECK(object.add_component<shift::Component>());
    }
}

TEST_CASE("Entity has_component", "[core][Entity]")
{
    auto object = shift::Entity{};
    auto component = std::make_unique<shift::Component>();
    REQUIRE(component);

    const auto uuid = component->uuid();
    constexpr auto name = "name";
    component->set_name(name);

    // the linter complaints that "Moved-from object 'component' is moved"
    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
    REQUIRE(object.add_component(std::move(component)));

    SECTION("UUID")
    {
        CHECK(object.has_component(uuid));
    }

    SECTION("name")
    {
        CHECK(object.has_component(name));
    }
}

TEST_CASE("Entity get_component", "[core][Entity]")
{
    auto object = shift::Entity{};
    auto component = std::make_unique<shift::Component>();
    REQUIRE(component);

    const auto uuid = component->uuid();
    constexpr auto name = "name";
    component->set_name(name);

    // the linter complaints that "Moved-from object 'component' is moved"
    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
    REQUIRE(object.add_component(std::move(component)));

    SECTION("UUID")
    {
        CHECK(object.find_component(uuid));
    }

    SECTION("name")
    {
        CHECK(object.find_component(name));
    }
}

TEST_CASE("Entity position", "[core][Entity]")
{
    auto entity = shift::Entity{};

    SECTION("setter")
    {
        constexpr auto position =
            shift::coordinate::EcefPosition{1.0, 2.0, 3.0};
        entity.set_position(position);
        CHECK(entity.position() == position);
    }

    SECTION("reference getter")
    {
        entity.position().x = 1.0;
        CHECK_THAT(entity.position().x, Catch::Matchers::WithinRel(1.0));
        entity.position().y = 1.0;
        CHECK_THAT(entity.position().y, Catch::Matchers::WithinRel(1.0));
        entity.position().z = 1.0;
        CHECK_THAT(entity.position().z, Catch::Matchers::WithinRel(1.0));
    }
}

TEST_CASE("Entity orientation", "[core][Entity]")
{
    auto entity = shift::Entity{};

    SECTION("setter")
    {
        const auto orientation =
            shift::coordinate::EulerOrientation{1.0, 2.0, 3.0};
        entity.set_orientation(orientation);
        CHECK(entity.orientation() == orientation);
    }

    SECTION("reference getter")
    {
        entity.orientation().set_yaw(1.0f);
        CHECK_THAT(entity.orientation().yaw(), Catch::Matchers::WithinRel(1.0));
        entity.orientation().set_pitch(1.0f);
        CHECK_THAT(entity.orientation().pitch(),
                   Catch::Matchers::WithinRel(1.0));
        entity.orientation().set_roll(1.0f);
        CHECK_THAT(entity.orientation().roll(),
                   Catch::Matchers::WithinRel(1.0));
    }
}

TEST_CASE("Entity velocity", "[core][Entity]")
{
    auto entity = shift::Entity{};

    SECTION("setter")
    {
        constexpr auto velocity = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
        entity.set_velocity(velocity);
        CHECK(entity.velocity() == velocity);
    }

    SECTION("reference getter")
    {
        entity.velocity().x = 1.0;
        CHECK_THAT(entity.velocity().x, Catch::Matchers::WithinRel(1.0));
        entity.velocity().y = 1.0;
        CHECK_THAT(entity.velocity().y, Catch::Matchers::WithinRel(1.0));
        entity.velocity().z = 1.0;
        CHECK_THAT(entity.velocity().z, Catch::Matchers::WithinRel(1.0));
    }
}

TEST_CASE("Entity acceleration", "[core][Entity]")
{
    auto entity = shift::Entity{};

    SECTION("setter")
    {
        constexpr auto acceleration =
            shift::coordinate::EcefVector{1.0, 2.0, 3.0};
        entity.set_acceleration(acceleration);
        CHECK(entity.acceleration() == acceleration);
    }

    SECTION("reference getter")
    {
        entity.acceleration().x = 1.0;
        CHECK_THAT(entity.acceleration().x, Catch::Matchers::WithinRel(1.0));
        entity.acceleration().y = 1.0;
        CHECK_THAT(entity.acceleration().y, Catch::Matchers::WithinRel(1.0));
        entity.acceleration().z = 1.0;
        CHECK_THAT(entity.acceleration().z, Catch::Matchers::WithinRel(1.0));
    }
}
