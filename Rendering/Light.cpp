#include "Light.hpp"

using namespace Rendering;

Light::Light(){}

Light::Light(   glm::vec3 position, 
                glm::vec3 ambient,
                glm::vec3 diffuse,
                float constant,
                float linear,
                float quadratic)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

glm::vec3 Light::getPosition()
{
    return this->position;
}

void Light::setPosition(glm::vec3 position) {
    this->position = position;
}