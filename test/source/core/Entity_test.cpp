#include <memory>
#include <utility>

#include "shift/core/Entity.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Component.hpp"

TEST_CASE("Entity type", "[core][Entity]")
{
    REQUIRE(std::string{shift::Entity{}.type()} == "Entity");
}

TEST_CASE("Entity uuid", "[core][Entity]")
{
    REQUIRE(!shift::Entity{}.uuid().empty());
    REQUIRE(shift::Entity{}.uuid() != shift::Entity{}.uuid());
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

    // todo: the linter complaints that "Moved-from object 'component' is moved"
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

    // todo: the linter complaints that "Moved-from object 'component' is moved"
    REQUIRE(object.add_component(std::move(component)));

    SECTION("UUID")
    {
        CHECK(object.get_component(uuid));
    }

    SECTION("name")
    {
        CHECK(object.get_component(name));
    }
}
