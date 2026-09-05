#include "shift/time/SimulationTime.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/TimeTypes.hpp"

TEST_CASE("SimulationTime as", "[time][SimulationTime]")
{
    const auto time = shift::time::Seconds{1};
    const auto sim_time = shift::time::SimulationTime{shift::time::Seconds{1}};

    CHECK(sim_time.as<shift::time::Microseconds>()
          == shift::time::time_cast<shift::time::Microseconds>(time));
    CHECK(sim_time.as<shift::time::Milliseconds>()
          == shift::time::time_cast<shift::time::Milliseconds>(time));
    CHECK(sim_time.as<shift::time::Seconds>() == time);
    CHECK(sim_time.as<shift::time::Minutes>()
          == shift::time::time_cast<shift::time::Minutes>(time));
    CHECK(sim_time.as<shift::time::Hours>()
          == shift::time::time_cast<shift::time::Hours>(time));
    CHECK(sim_time.as<shift::time::Days>()
          == shift::time::time_cast<shift::time::Days>(time));
}

// TEST_CASE("SimulationTime operator+", "[time][SimulationTime]")
// {
//     const auto sim_time =
//     shift::time::SimulationTime{shift::time::Seconds{0}};
//
//     SECTION("SimulationTime")
//     {
//         const auto next_sim_time =
//             sim_time + shift::time::SimulationTime{shift::time::Seconds{1}};
//         CHECK(next_sim_time.as<shift::time::Seconds>()
//               == shift::time::Seconds{1});
//     }
//
//     SECTION("TimeType")
//     {
//         const auto next_sim_time = sim_time + shift::time::Seconds{1};
//         CHECK(next_sim_time.as<shift::time::Seconds>()
//               == shift::time::Seconds{1});
//     }
// }
//
// TEST_CASE("SimulationTime operator+=", "[time][SimulationTime]")
// {
//     auto sim_time = shift::time::SimulationTime{shift::time::Seconds{0}};
//
//     SECTION("SimulationTime")
//     {
//         sim_time += shift::time::SimulationTime{shift::time::Seconds{1}};
//         CHECK(sim_time.as<shift::time::Seconds>() ==
//         shift::time::Seconds{1});
//     }
//
//     SECTION("TimeType")
//     {
//         sim_time += shift::time::Seconds{1};
//         CHECK(sim_time.as<shift::time::Seconds>() ==
//         shift::time::Seconds{1});
//     }
// }
//
// TEST_CASE("SimulationTime operator-", "[time][SimulationTime]")
// {
//     const auto sim_time =
//     shift::time::SimulationTime{shift::time::Seconds{1}};
//
//     SECTION("SimulationTime")
//     {
//         const auto next_sim_time =
//             sim_time - shift::time::SimulationTime{shift::time::Seconds{1}};
//         CHECK(next_sim_time.as<shift::time::Seconds>()
//               == shift::time::Seconds{0});
//     }
//
//     SECTION("TimeType")
//     {
//         const auto next_sim_time = sim_time - shift::time::Seconds{1};
//         CHECK(next_sim_time.as<shift::time::Seconds>()
//               == shift::time::Seconds{0});
//     }
// }
//
// TEST_CASE("SimulationTime operator-=", "[time][SimulationTime]")
// {
//     auto sim_time = shift::time::SimulationTime{shift::time::Seconds{1}};
//
//     SECTION("SimulationTime")
//     {
//         sim_time -= shift::time::SimulationTime{shift::time::Seconds{1}};
//         CHECK(sim_time.as<shift::time::Seconds>() ==
//         shift::time::Seconds{0});
//     }
//
//     SECTION("TimeType")
//     {
//         sim_time -= shift::time::Seconds{1};
//         CHECK(sim_time.as<shift::time::Seconds>() ==
//         shift::time::Seconds{0});
//     }
// }
