#pragma once

#include "EventType.hpp"

class Event {
public:
    virtual ~Event() = default;

    virtual EventType getType() const = 0;
};
