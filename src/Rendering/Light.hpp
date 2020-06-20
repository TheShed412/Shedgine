#pragma once
#include <glm/glm.hpp>

namespace Rendering
{
    class Light {
        public:
            Light();
            Light(glm::vec3, glm::vec3, glm::vec3, glm::vec3,
                float, float, float);
            void setPosition(glm::vec3);
            const glm::vec3* getPosition();
            const glm::vec3* getAmbient();
            const glm::vec3* getDiffuse();
            const glm::vec3* getSpecular();
            float getConstant();
            float getLinear();
            float getQuadratic();
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
