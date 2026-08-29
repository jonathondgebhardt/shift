#include "shift/core/Component.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Component type", "[core][Component]")
{
    REQUIRE(std::string{shift::Component{}.type()} == "Component");
}

TEST_CASE("Component uuid", "[core][Component]")
{
    REQUIRE(!shift::Component{}.uuid().empty());
    REQUIRE(shift::Component{}.uuid() != shift::Component{}.uuid());
}

TEST_CASE("Component name", "[core][Component]")
{
    auto object = shift::Component{};

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
