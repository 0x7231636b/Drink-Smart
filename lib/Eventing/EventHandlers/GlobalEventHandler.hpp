#pragma once

#include <vector>
#include <memory>

#include "EventHandler.hpp"
#include "EventListener.hpp"

class GlobalEventHandler : public EventHandler {
public:
    virtual void addEventListener(const std::shared_ptr<EventListener>& listener);
    virtual void removeEventListener(const std::shared_ptr<EventListener>& listener);

    virtual void distributeEvent(const Event& event);
private:
    std::vector<const std::shared_ptr<EventListener> > listeners;
};
