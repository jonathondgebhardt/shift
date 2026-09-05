#pragma once

#include <optional>
#include <variant>

#include "shift/core/shift_core_export.hpp"
#include "shift/time/Duration.hpp"
#include "shift/time/SimulationTime.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT UpdateResult
{
public:
    static constexpr auto schedule_at(time::SimulationTime time) -> UpdateResult
    {
        return UpdateResult{At{time}};
    }

    static constexpr auto schedule_after(time::Duration delta) -> UpdateResult
    {
        return UpdateResult{After{delta}};
    }

    static constexpr auto schedule_now() -> UpdateResult
    {
        return UpdateResult{After{time::Duration{}}};
    }

    static constexpr auto stop() -> UpdateResult { return UpdateResult{}; }

    [[nodiscard]]
    constexpr auto stopped() const -> bool
    {
        return !m_next;
    }

    [[nodiscard]]
    constexpr auto next_time(time::SimulationTime current) const
        -> std::optional<time::SimulationTime>
    {
        if (!m_next) {
            return std::nullopt;
        }

        return std::visit([&](const auto& value) -> time::SimulationTime
                          { return value.resolve(current); },
                          *m_next);
    }

private:
    struct At
    {
        constexpr auto resolve([[maybe_unused]] time::SimulationTime current)
            const -> time::SimulationTime
        {
            return time;
        }

        time::SimulationTime time;
    };

    struct After
    {
        constexpr auto resolve(time::SimulationTime current) const
            -> time::SimulationTime
        {
            return current + delta;
        }

        time::Duration delta;
    };

    using UpdateResultType = std::variant<At, After>;

    UpdateResult() = default;

    constexpr explicit UpdateResult(UpdateResultType next)
        : m_next{next}
    {
    }

    std::optional<UpdateResultType> m_next;
};

}  // namespace shift
