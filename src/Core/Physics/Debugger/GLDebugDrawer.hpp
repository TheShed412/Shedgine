#pragma once
#include <LinearMath/btIDebugDraw.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class GLDebugDrawer : public btIDebugDraw
{
   private:
      int m_debugMode;
      GLuint VBO, VAO, projection_location, model_view_location, program;
      glm::mat4 pViewMatrix,  pProjectionMatrix;

public:

   GLDebugDrawer();
   virtual ~GLDebugDrawer();
   virtual void   setMatrix(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix, GLuint program);
   virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
   virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
   virtual void   drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
   virtual void   drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);
   virtual void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
   virtual void   reportErrorWarning(const char* warningString);
   virtual void   draw3dText(const btVector3& location, const char* textString);
   virtual void   setDebugMode(int debugMode);
   virtual int    getDebugMode() const { return m_debugMode; }

};