#pragma once

#include <memory>

#include "Event.hpp"
#include "EventListener.hpp"

class EventHandler {
public:
    virtual ~EventHandler() = default;

    virtual void addEventListener(const std::shared_ptr<EventListener>& listener) = 0;
    virtual void removeEventListener(const std::shared_ptr<EventListener>& listener) = 0;

    virtual void distributeEvent(const Event& event) = 0;
};
