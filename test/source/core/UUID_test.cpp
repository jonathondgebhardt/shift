#include <regex>

#include "shift/core/UUID.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("UUID is unique from build", "[core][uuid]")
{
    REQUIRE(shift::UUID::build() != shift::UUID::build());
}

TEST_CASE("UUID to_string", "[core][uuid]")
{
    const auto uuid_str = shift::UUID::build().to_string();
    REQUIRE(!uuid_str.empty());

    const auto pattern = std::regex{
        R"([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})"};
    CHECK(std::regex_match(uuid_str, pattern));
}
