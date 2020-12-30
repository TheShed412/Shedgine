#pragma once
#include <map>
#include <vector>
#include <functional>


/** 
 * This will be a general class that can be used to make and listen to events.
 * 
*/
namespace Shed
{
    class EventManager {
        private:
            std::map<std::string, std::vector<std::function<void()>>> events;
        public:
            void addFunction(std::string, std::function<void()>);
            void callFunctions(std::string);
    };
} // namespace Shed