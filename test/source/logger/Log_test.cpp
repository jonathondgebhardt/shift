#include <memory>
#include <vector>

#include "shift/logger/Log.hpp"

#include <catch2/catch_test_macros.hpp>

#include "LogTesting.hpp"

namespace
{

struct TestSink final : public shift::log::testing::Sink
{
    auto write(const shift::log::testing::Record& record) -> void override
    {
        records.push_back(record);
    }

    std::vector<shift::log::testing::Record> records;
};

}  // namespace

TEST_CASE("Log trace", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::trace().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::TRACE);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log debug", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::debug().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::DEBUG);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log info", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::info().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::INFO);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log warning", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::warning().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::WARNING);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log error", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::error().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::ERROR);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log critical", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    shift::log::critical().append("Something went wrong");

    REQUIRE(sink->records.size() == 1);
    CHECK(sink->records[0].level == shift::log::Level::CRITICAL);
    CHECK(sink->records[0].message == "Something went wrong");
}

TEST_CASE("Log multiple messages", "[logger]")
{
    auto sink = std::make_shared<TestSink>();
    const auto scoped_sink = shift::log::testing::ScopedSink{sink};

    {
        auto critical = shift::log::critical();
        critical.append("Something went wrong");
        critical.append("Something else went wrong");
    }

    CHECK(sink->records.size() == 2);
}
