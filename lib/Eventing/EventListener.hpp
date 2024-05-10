#pragma once

#include "Event.hpp"

class EventListener {

public:
    virtual ~EventListener() = default;

    virtual void handleEvent(const Event& event) = 0;
};
