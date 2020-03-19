#pragma once
#include <glm/glm.hpp>
#include <string>
 
namespace Rendering
{
 
  struct TextureFormat
  {
    unsigned int id;
    std::string type;
    std::string path;

    TextureFormat(unsigned int id, std::string type, std::string path) {
        this->id = id;
        this->path = path;
        this->type = type;
    }
 
    TextureFormat() {}
 
  };
}