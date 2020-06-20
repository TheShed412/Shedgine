#pragma once
#include <map>
#include "../Actor.hpp"
 
using namespace Rendering;
namespace Game
{
    namespace Managers
    {
          class ActorManager
            {
                public:
                    ActorManager();
                    ~ActorManager();
            
                    void Draw();
                    void Update();
                    void DeleteActor(const std::string& actorName);
                    void AddActor(const std::string& ActorName, Actor* Actor);
                    Actor& GetActor(const std::string& ActorName) const;
            
                private:
                    std::map<std::string, Actor*> actorList;
            };
    } // namespace Managers
    

}