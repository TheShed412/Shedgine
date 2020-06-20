#pragma once
#include <map>
#include "../GameObject.hpp"
 
using namespace Rendering;
namespace Game
{
    namespace Managers
    {
          class ObjectManager
            {
                public:
                    ObjectManager();
                    ~ObjectManager();
            
                    void Draw();
                    void Update();
                    void DeleteObject(const std::string& gameObjectName);
                    void AddObject(const std::string& gameObjectName, GameObject* gameObject);
                    GameObject& GetObject(const std::string& gameObjectName) const;
            
                private:
                    std::map<std::string, GameObject*> gameObjectList;
            };
    } // namespace Managers
    

}