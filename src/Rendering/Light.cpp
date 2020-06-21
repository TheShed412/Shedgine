#include "Light.hpp"

using namespace Rendering;

Light::Light(){}

// Playing with the constant, linear, and quadratic values will play with the brightness of the light, the lower, the brighter it will be
// TODO: make a wrapper that lets you play withh brightness in a simpler way
Light::Light(   glm::vec3 position, 
                glm::vec3 ambient,
                glm::vec3 diffuse,
                glm::vec3 specular,
                float constant,
                float linear,
                float quadratic)
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

const glm::vec3* Light::getPosition()
{
    return &this->position;
}

const glm::vec3* Light::getAmbient()
{
    return &this->ambient;
}

const glm::vec3* Light::getDiffuse()
{
    return &this->diffuse;
}
const glm::vec3* Light::getSpecular()
{
    return &this->specular;
}

float Light::getConstant()
{
    return this->constant;
}

float Light::getQuadratic()
{
    return this->quadratic;
}

float Light::getLinear()
{
    return this->linear;
}

void Light::setPosition(glm::vec3 position) {
    this->position = position;
}