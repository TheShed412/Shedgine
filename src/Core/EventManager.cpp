#include "EventManager.hpp"

using namespace Shed;

EventManager::EventManager() {}

void EventManager::addFunction(std::string eventName, std::function<void()> function) {
    // TODO: check for repeats
    this->events[eventName].push_back(function);
}

void EventManager::callFunctions(std::string eventName) {
    std::vector<std::function<void()>> funcsToCall = this->events[eventName];

    for (size_t i = 0; i < funcsToCall.size(); i++)
    {
        funcsToCall.at(i)();
    }
}