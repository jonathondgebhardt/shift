#include "shift/telemetry/DataDefinition.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

namespace
{

struct TestOwner
{
    int number{};
};

constexpr auto test_definition =
    shift::telemetry::DataDefinition<TestOwner, int>{
        "test_definition",
        [](const TestOwner& test_owner) -> std::optional<int>
        { return test_owner.number; }};

}  // namespace

TEST_CASE("DataDefinition name", "[telemetry][DataDefinition]")
{
    CHECK(test_definition.name() == "test_definition");
}

TEST_CASE("DataDefinition get", "[telemetry][DataDefinition]")
{
    constexpr auto owner = TestOwner{.number = 1337};
    CHECK(test_definition.get(owner) == owner.number);
}
