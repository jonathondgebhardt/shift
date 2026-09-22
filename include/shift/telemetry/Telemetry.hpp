#pragma once

#include <ranges>
#include <utility>

#include "shift/core/World.hpp"
#include "shift/telemetry/DataDefinition.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"
#include "shift/time/TimePoint.hpp"
#include "shift/utilities/Exception.hpp"

namespace shift::telemetry
{

// todo: this class can be defined in a cpp if Observer is external
class Telemetry
{
public:
    explicit Telemetry(std::unique_ptr<TelemetryRecorder> recorder)
        : m_recorder{std::move(recorder)}
    {
    }

    auto recorder() const -> TelemetryRecorder* { return m_recorder.get(); }

    template<typename Owner, typename Value>
    auto observe(const DataDefinition<Owner, Value>& definition) -> void
    {
        m_observations.push_back(
            std::make_unique<Observation<Owner, Value>>(definition));
    }

    auto sample(time::TimePoint time, const World& world) -> void
    {
        if (m_recorder == nullptr) {
            throw Exception{"recorder cannot be null"};
        }

        for (const auto& observation : m_observations) {
            observation->sample(time, world, *m_recorder);
        }
    }

    auto shutdown() -> void
    {
        if (m_recorder != nullptr) {
            m_recorder->shutdown();
        }
    }

private:
    struct ObservationConcept
    {
        ObservationConcept() = default;
        ObservationConcept(const ObservationConcept&) = default;
        ObservationConcept(ObservationConcept&&) noexcept = default;
        virtual ~ObservationConcept() = default;
        auto operator=(const ObservationConcept&) -> ObservationConcept& =
                                                         default;
        auto operator=(ObservationConcept&&) noexcept -> ObservationConcept& =
                                                             default;

        virtual auto sample(time::TimePoint,
                            const World&,
                            TelemetryRecorder&) const -> void = 0;
    };

    // todo: can template args be constrained?
    template<typename Owner, typename Value>
    class Observation : public ObservationConcept
    {
    public:
        explicit Observation(const DataDefinition<Owner, Value>& definition)
            : m_definition{definition}
        {
        }

        auto sample(time::TimePoint time,
                    const World& world,
                    TelemetryRecorder& recorder) const -> void override
        {
            for (const auto& entity : world.entities()
                     | std::views::filter([](const auto& entity)
                                          { return entity != nullptr; }))
            {
                const auto value = m_definition.get(*entity);

                if (!value) {
                    continue;
                }

                recorder.record({.time = time,
                                 .uid = entity->uid(),
                                 .channel = m_definition.name(),
                                 .value = TelemetryValue{*value}});
            }
        }

    private:
        DataDefinition<Owner, Value> m_definition;
    };

    // todo: may want to move these out into some other file or delegate to a
    // class
    // todo: TelemetryValue type erases, can we just use T?

    std::vector<std::unique_ptr<ObservationConcept>> m_observations;
    std::unique_ptr<TelemetryRecorder> m_recorder;
};

}  // namespace shift::telemetry
