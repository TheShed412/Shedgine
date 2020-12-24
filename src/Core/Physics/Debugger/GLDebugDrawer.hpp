#pragma once
#include <iostream>
#include <LinearMath/btIDebugDraw.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class GLDebugDrawer : public btIDebugDraw
{
   private:
      int m_debugMode;
      GLuint VBO, VAO, projection_location, model_view_location, program;
      glm::mat4 pViewMatrix,  pProjectionMatrix;

   public:
      void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix){
               glUseProgram(0); // Use Fixed-function pipeline (no shaders)
               glMatrixMode(GL_MODELVIEW);
               glLoadMatrixf(&pViewMatrix[0][0]);
               glMatrixMode(GL_PROJECTION);
               glLoadMatrixf(&pProjectionMatrix[0][0]);
      }
      void drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
         //std::cout << "color: " << color.x() << " " << color.y() << " " << color.z() << " " << std::endl;
               glColor3f(color.x(), color.y(), color.z());
               glBegin(GL_LINES);
                        glVertex3f(from.x(), from.y(), from.z());
                        glVertex3f(to.x(), to.y(), to.z());
               glEnd();
      }
      virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &){}
      virtual void reportErrorWarning(const char *){}
      virtual void draw3dText(const btVector3 &,const char *){}
      virtual void setDebugMode(int p){
               m = p;
      }
      int getDebugMode(void) const {return 3;}
      int m;
};
