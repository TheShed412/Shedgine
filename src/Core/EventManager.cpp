#include "EventManager.hpp"

using namespace Shed;

EventManager::EventManager() {}

void EventManager::addFunction(std::string eventName, std::function<void(bool, int)> function) {
    // TODO: check for repeats
    this->events[eventName].push_back(function);
}

void EventManager::callFunctions(std::string eventName, int button, bool state) {
    std::vector<std::function<void(bool, int)>> funcsToCall = this->events[eventName];

    for (size_t i = 0; i < funcsToCall.size(); i++)
    {
        funcsToCall.at(i)(button, state);
    }
}