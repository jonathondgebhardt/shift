#include "shift/core/Object.hpp"

#include <catch2/catch_test_macros.hpp>

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
