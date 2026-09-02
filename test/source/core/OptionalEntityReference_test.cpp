#include "shift/core/OptionalEntityReference.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Entity.hpp"

TEST_CASE("OptionalEntityReference no entity",
          "[core][OptionalEntityReference]")
{
    const auto oer = shift::OptionalEntityReference{};
    SECTION("try_unwrap")
    {
        CHECK_THROWS(oer.try_unwrap());
    }

    SECTION("unwrap")
    {
        CHECK_THROWS(oer.unwrap());
    }

    SECTION("empty")
    {
        CHECK(oer.empty());
    }
}

TEST_CASE("OptionalEntityReference", "[core][OptionalEntityReference]")
{
    auto entity = shift::Entity{};
    const auto oer = shift::OptionalEntityReference{entity};

    SECTION("try_unwrap")
    {
        CHECK_NOTHROW(oer.try_unwrap());
    }

    SECTION("unwrap")
    {
        CHECK_NOTHROW(oer.unwrap());
    }

    SECTION("empty")
    {
        CHECK(!oer.empty());
    }
}
