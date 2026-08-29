#pragma once

#include <memory>
#include <source_location>
#include <string>

#include "shift/logger/Log.hpp"
#include "shift/utilities/Pimpl.hpp"

namespace shift::log::testing
{

struct Record
{
    Level level;
    std::string message;
    std::source_location location;
};

class Sink
{
public:
    Sink() = default;
    Sink(const Sink&) = default;
    Sink(Sink&&) noexcept = default;
    virtual ~Sink() = default;
    auto operator=(const Sink&) -> Sink& = default;
    auto operator=(Sink&&) noexcept -> Sink& = default;

    virtual auto write(const Record& record) -> void = 0;
};

class ScopedSink
{
public:
    explicit ScopedSink(std::shared_ptr<Sink> sink);

    ~ScopedSink();

    ScopedSink(const ScopedSink&) = delete;
    ScopedSink(ScopedSink&&) = delete;

    auto operator=(const ScopedSink&) -> ScopedSink& = delete;
    auto operator=(ScopedSink&&) -> ScopedSink& = delete;

private:
    struct Impl;
    Pimpl<Impl> m_impl;
};

}  // namespace shift::log::testing
