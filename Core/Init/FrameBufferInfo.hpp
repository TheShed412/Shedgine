#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
 
namespace Core{
 
  struct FramebufferInfo{
 
    unsigned int flags;
    bool msaa;//to enable or disable it when wee need it
 
    FramebufferInfo()
    {
      //default
      flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
      msaa = false;
    }
 
    FramebufferInfo(bool color, bool depth, bool stencil, bool msaa)
    {
        flags = GLUT_DOUBLE; //this is a must
        if (color)
            flags |= GLUT_RGBA | GLUT_ALPHA;
        if (depth)
            flags |= GLUT_DEPTH;
        if (stencil)
            flags |= GLUT_STENCIL;
        if (msaa)
            flags |= GLUT_MULTISAMPLE;
        
        this->msaa = msaa;
    }

    FramebufferInfo(const FramebufferInfo& framebufferInfo)
    {
       flags = framebufferInfo.flags;
       msaa = framebufferInfo.msaa;
    }

    void operator=(const FramebufferInfo& framebufferInfo)
    {
       flags = framebufferInfo.flags;
       msaa = framebufferInfo.msaa;
    }
 };
}