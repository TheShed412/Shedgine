#pragma once
#include <glm/glm.hpp>

namespace Rendering
{
    class Light {
        public:
            Light();
            Light(glm::vec3, glm::vec3, glm::vec3,
                float, float, float);
            void setPosition(glm::vec3);
            glm::vec3 getPosition();
        private:
            glm::vec3 position;
        
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            
            float constant;
            float linear;
            float quadratic;
    };
} // namespace Rendering
