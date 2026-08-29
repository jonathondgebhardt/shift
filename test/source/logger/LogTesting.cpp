#include <memory>
#include <source_location>
#include <string>
#include <string_view>
#include <utility>

#include "LogTesting.hpp"

#include "shift/logger/Log.hpp"
#include "shift/logger/LogBackend.hpp"

namespace shift::log::testing
{

namespace
{

class TestOutput final : public detail::Backend::Output
{
public:
    explicit TestOutput(std::shared_ptr<Sink> sink)
        : m_sink(std::move(sink))
    {
    }

    auto enabled([[maybe_unused]] Level level) const noexcept -> bool override
    {
        return true;
    }

    auto write(Level level,
               std::string_view message,
               std::source_location location) -> void override
    {
        m_sink->write(Record{.level = level,
                             .message = std::string{message},
                             .location = location});
    }

private:
    std::shared_ptr<Sink> m_sink;
};

}  // namespace

struct ScopedSink::Impl
{
    std::shared_ptr<detail::Backend::Output> previous;
};

ScopedSink::ScopedSink(std::shared_ptr<Sink> sink)
    : m_impl(std::make_unique<Impl>())
{
    auto output = std::make_shared<TestOutput>(std::move(sink));

    m_impl->previous = detail::backend().set_output(std::move(output));
}

ScopedSink::~ScopedSink()
{
    detail::backend().set_output(std::move(m_impl->previous));
}

}  // namespace shift::log::testing
