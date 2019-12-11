#include "InitGLUT.hpp"
 
using namespace Core::Init;

Core::IListener* InitGLUT::listener = NULL;
Core::WindowInfo InitGLUT::windowInformation;
 
void InitGLUT::init(const Core::WindowInfo& windowInfo,
                     const Core::ContextInfo& contextInfo,
                     const Core::FramebufferInfo& framebufferInfo)
{
   //we need to create these fake arguments
   int fakeargc = 1;
   char *fakeargv[] = { "fake", NULL };
   glutInit(&fakeargc, fakeargv);
   windowInformation = windowInfo;

   if (contextInfo.core){
         glutInitContextVersion(contextInfo.major_version,
                                 contextInfo.minor_version);
         glutInitContextProfile(GLUT_CORE_PROFILE);
   }
   else
   {
         //As I said in part II, version doesn't matter
         // in Compatibility mode
         glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
      }
   
      //these functions were called in the old main.cpp
      //Now we use info from the structures
   glutInitDisplayMode(framebufferInfo.flags);
   glutInitWindowPosition(windowInfo.position_x,
                           windowInfo.position_y);
   glutInitWindowSize(windowInfo.width, windowInfo.height);
   
   glutCreateWindow(windowInfo.name.c_str());
   
      std::cout << "GLUT:initialized" << std::endl;
      //these callbacks are used for rendering
   glutIdleFunc(idleCallback);
   glutCloseFunc(closeCallback);
   glutDisplayFunc(displayCallback);
   glutReshapeFunc(reshapeCallback);
   
   //init GLEW, this can be called in main.cpp
   Init::InitGLEW::Init();
   
   //cleanup
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
   
   //our method to display some info. Needs contextInfo and windowinfo
   printOpenGLInfo(windowInfo, contextInfo);
 
}
 
//starts the rendering Loop
void InitGLUT::run()
{
   std::cout << "GLUT:\t Start Running " << std::endl;
   glutMainLoop();
}

void InitGLUT::close()
{
   std::cout << "GLUT:\t Finished" << std::endl;
   glutLeaveMainLoop();
}
 
void InitGLUT::idleCallback(void)
{
   //do nothing, just redisplay
   glutPostRedisplay();
}
 
void InitGLUT::displayCallback()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0, 0.0, 0.0, 1);
   if (listener){
      listener->notifyBeginFrame();
      listener->notifyDisplayFrame();
   
      glutSwapBuffers();
   
      listener->notifyEndFrame();
   }
}
 
void InitGLUT::reshapeCallback(int width, int height){
   if (windowInformation.isReshapable == true) {
      if (listener){
         listener->notifyReshape(width,
                                 height,
                                 windowInformation.width,
                                 windowInformation.height);
      }
      windowInformation.width = width;
      windowInformation.height = height;
  }
}
 
void InitGLUT::closeCallback()
{
  close();
}
 
void InitGLUT::enterFullscreen()
{
  glutFullScreen();
}
 
void InitGLUT::exitFullscreen()
{
  glutLeaveFullScreen();
}

void InitGLUT::setListener(Core::IListener*& iListener)
{
   listener = iListener;
}

void InitGLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
                                const Core::ContextInfo& contextInfo){
 
    const unsigned char* renderer = glGetString(GL_RENDERER);
    const unsigned char* vendor = glGetString(GL_VENDOR);
    const unsigned char* version = glGetString(GL_VERSION);
    
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "GLUT:Initialise" << std::endl;
    std::cout << "GLUT:\tVendor : " << vendor << std::endl;
    std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
    std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}