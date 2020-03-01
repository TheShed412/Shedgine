#pragma once
#include <glm/glm.hpp>
 
namespace Rendering
{
 
  struct VertexFormat
  {
     glm::vec3 position;
     glm::vec3 normal;
     glm::vec3 tangent;
     glm::vec3 bitTangent;
     glm::vec4 color;
     glm::vec2 texture;
 
     VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor)
     {
       position = iPos;
       color = iColor;
    }

    VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iTexture)
     {
       position = iPos;
       texture = iTexture;
    }
 
    VertexFormat() {}
 
  };
}