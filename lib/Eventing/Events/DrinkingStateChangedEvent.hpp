#pragma once

#include "EventType.hpp"
#include "Event.hpp"
#include "DrinkDetectionScale.hpp"


class DrinkingStateChangedEvent : public Event {
public:
    virtual EventType getType() const {
        return EventType::DRINKING_STATE_CHANGED;
    }

private:
    DrinkDetectionScale::State currentState;
};
