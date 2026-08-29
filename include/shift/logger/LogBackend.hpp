#pragma once

#include <memory>
#include <source_location>
#include <string_view>

#include "shift/logger/Log.hpp"

namespace shift::log::detail
{

class Backend
{
public:
    class Output
    {
    public:
        Output() = default;
        Output(const Output&) = default;
        Output(Output&&) noexcept = default;
        virtual ~Output() = default;
        auto operator=(const Output&) -> Output& = default;
        auto operator=(Output&&) noexcept -> Output& = default;

        virtual auto enabled(Level level) const noexcept -> bool = 0;

        virtual auto write(Level level,
                           std::string_view message,
                           std::source_location location) -> void = 0;
    };

    Backend();
    ~Backend();

    Backend(const Backend&) = delete;
    Backend(Backend&&) = delete;

    auto operator=(const Backend&) -> Backend& = delete;
    auto operator=(Backend&&) -> Backend& = delete;

    auto enabled(Level level) const noexcept -> bool;

    auto write(Level level,
               std::string_view message,
               std::source_location location) -> void;

    auto set_output(std::shared_ptr<Output> output) -> std::shared_ptr<Output>;

private:
    std::shared_ptr<Output> m_output;
};

auto backend() -> Backend&;

}  // namespace shift::log::detail
