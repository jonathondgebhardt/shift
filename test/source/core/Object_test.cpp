#include <memory>
#include <utility>

#include "shift/core/Object.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Component.hpp"

TEST_CASE("Object type", "[core][Object]")
{
    REQUIRE(std::string{shift::Object{}.type()} == "Object");
}

TEST_CASE("Object uuid", "[core][Object]")
{
    REQUIRE(!shift::Object{}.uuid().empty());
    REQUIRE(shift::Object{}.uuid() != shift::Object{}.uuid());
}

TEST_CASE("Object name", "[core][Object]")
{
    auto object = shift::Object{};

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

TEST_CASE("Object add_component", "[core][Object]")
{
    auto object = shift::Object{};

    SECTION("pass component")
    {
        CHECK(object.add_component(std::make_unique<shift::Component>()));
    }

    SECTION("templated")
    {
        CHECK(object.add_component<shift::Component>());
    }
}

TEST_CASE("Object has_component", "[core][Object]")
{
    auto object = shift::Object{};
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

TEST_CASE("Object get_component", "[core][Object]")
{
    auto object = shift::Object{};
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
