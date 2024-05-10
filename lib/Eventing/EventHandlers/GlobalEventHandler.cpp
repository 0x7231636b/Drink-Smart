#include "GlobalEventHandler.hpp"

#include <algorithm>

void GlobalEventHandler::addEventListener(const std::shared_ptr<EventListener>& listener) {
    listeners.push_back(listener);
}

void GlobalEventHandler::removeEventListener(const std::shared_ptr<EventListener>& listener) {
    auto it = std::remove(listeners.begin(), listeners.end(), listener);
    listeners.erase(it, listeners.end());
}

void GlobalEventHandler::distributeEvent(const Event& event) {
    for (const auto& listener : listeners) {
        listener->handleEvent(event);
    }
}
