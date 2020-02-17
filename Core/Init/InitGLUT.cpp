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
      glutInitContextVersion(contextInfo.major_version, contextInfo.minor_version);
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
   glEnable(GL_DEBUG_OUTPUT);
   //glutSetCursor(GLUT_CURSOR_NONE);
   glutIdleFunc(idleCallback);
   glutCloseFunc(closeCallback);
   glutDisplayFunc(displayCallback);
   glutReshapeFunc(reshapeCallback);
   glutPassiveMotionFunc(mouseMovementCallback);
   glutKeyboardFunc(keyboardCallback);
   glutKeyboardUpFunc(keyboardUp);
   glutMouseFunc(mouseCallback);
   
   //init GLEW, this can be called in main.cpp
   Init::InitGLEW::Init();
   glDebugMessageCallback(DebugOutput::Callback, NULL);
   glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                      GL_DONT_CARE, 0, NULL, GL_TRUE);
   
   //cleanup
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
   
   //our method to display some info. Needs contextInfo and windowinfo
   printOpenGLInfo(windowInfo, contextInfo);


   //glPolygonMode(GL_FRONT, GL_FILL);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
   if (listener){
      listener->notifyBeginFrame();
      listener->notifyDisplayFrame();
      glutSwapBuffers();
   
      listener->notifyEndFrame();
   }
}

void InitGLUT::keyboardUp(unsigned char key, int x, int y) {
   if(listener) {
      listener->notifyKeyboardUp(key);
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

void InitGLUT::keyboardCallback(unsigned char key, int mousex, int mousey) {
   if(listener) {
      listener->notifyKeyboardInput(key);
   }
}

static int mouseClick = 0;
void InitGLUT::mouseCallback(int button, int state, int x, int y) {
   std::cout << "MOUSE Click: " << mouseClick << std::endl;
   mouseClick++;
   if(listener) {
      listener->notifyMouseInput(button, state, x, y);
   }
}

void InitGLUT::mouseMovementCallback(int x, int y) {
   if(listener) {
      listener->notifyMouseMovementInput(x, y);
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