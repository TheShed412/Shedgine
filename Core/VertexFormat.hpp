#ifndef  VertexFormat_H_
#define VertexFormat_H_
 
#include <glm/glm.hpp>
 
struct VertexFormat
{
  glm::vec3 position;//our first vertex attribute
 
  VertexFormat(const glm::vec3 &pos)
  {
     position = pos;
   }
};
 
#endif