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
            std::map<std::string, std::vector<std::function<void(bool, int)>>> events;
        public:
            EventManager();
            virtual ~EventManager() {};
            void addFunction(std::string, std::function<void(bool, int)>);
            void callFunctions(std::string, int button, bool state);
    };
} // namespace Shed