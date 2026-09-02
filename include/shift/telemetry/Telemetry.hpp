#pragma once

#include "shift/core/TimeTypes.hpp"
#include "shift/core/World.hpp"
#include "shift/telemetry/DataDefinition.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

namespace shift::telemetry
{

class Telemetry
{
public:
    explicit Telemetry(TelemetryRecorder& recorder)
        : m_recorder{recorder}
    {
    }

    template<typename Owner, typename Value>
    auto observe(const DataDefinition<Owner, Value>& definition) -> void
    {
        m_observations.push_back(
            std::make_unique<Observation<Owner, Value>>(definition));
    }

    auto sample(time::Microseconds time, const World& world) -> void
    {
        for (const auto& observation : m_observations) {
            observation->sample(time, world, m_recorder);
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

        virtual auto sample(time::Microseconds,
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

        auto sample(time::Microseconds time,
                    const World& world,
                    TelemetryRecorder& recorder) const -> void override
        {
            for (const auto& entity : world.entities()) {
                const auto value = m_definition.get(entity);

                if (!value) {
                    continue;
                }

                record_value(
                    recorder, time, entity, m_definition.name(), *value);
            }
        }

    private:
        DataDefinition<Owner, Value> m_definition;
    };

    // todo: may want to move these out into some other file or delegate to a
    // class
    static void record_value(TelemetryRecorder& recorder,
                             time::Microseconds time,
                             const Entity& entity,
                             std::string_view channel,
                             double value)
    {
        recorder.record({.time = time,
                         .uuid = entity.uuid(),
                         .channel = channel,
                         .value = TelemetryValue{value}});
    }

    static void record_value(TelemetryRecorder& recorder,
                             time::Microseconds time,
                             const Entity& entity,
                             std::string_view channel,
                             const Vec3& value)
    {
        recorder.record({.time = time,
                         .uuid = entity.uuid(),
                         .channel = channel,
                         .value = TelemetryValue{value}});
    }

    std::vector<std::unique_ptr<ObservationConcept>> m_observations;
    std::reference_wrapper<TelemetryRecorder> m_recorder;
};

}  // namespace shift::telemetry
