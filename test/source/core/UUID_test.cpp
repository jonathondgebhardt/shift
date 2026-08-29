#include <regex>

#include "shift/core/UUID.hpp"

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("UUID is unique from build", "[core][UUID]")
{
    REQUIRE(shift::UUID::build() != shift::UUID::build());
}

TEST_CASE("UUID to_string", "[core][UUID]")
{
    const auto uuid_str = shift::UUID::build().to_string();
    REQUIRE(!uuid_str.empty());

    const auto pattern = std::regex{
        R"([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})"};
    CHECK(std::regex_match(uuid_str, pattern));
}

TEST_CASE("UUID vs Boost::uuid", "[core][UUID][!benchmark]")
{
    SECTION("generation")
    {
        BENCHMARK("Boost")
        {
            return boost::uuids::random_generator_mt19937()();
        };

        BENCHMARK("SHIFT")
        {
            return shift::UUID::build();
        };
    }

    SECTION("comparison equal")
    {
        const auto boost_uuid = boost::uuids::random_generator()();
        BENCHMARK("Boost")
        {
            return boost_uuid == boost_uuid;
        };

        const auto shift_uuid = shift::UUID::build();
        BENCHMARK("SHIFT")
        {
            return shift_uuid == shift_uuid;
        };
    }

    SECTION("comparison unequal")
    {
        const auto boost_uuid_1 = boost::uuids::random_generator()();
        const auto boost_uuid_2 = boost::uuids::random_generator()();
        BENCHMARK("Boost")
        {
            return boost_uuid_1 == boost_uuid_2;
        };

        const auto shift_uuid_1 = shift::UUID::build();
        const auto shift_uuid_2 = shift::UUID::build();
        BENCHMARK("SHIFT")
        {
            return shift_uuid_1 == shift_uuid_2;
        };
    }
}
