#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Core{
       //notice that I added another namespace here(optional)
     namespace Init{ 
 
           class InitGLEW
          {
             public:
                static void Init();
           };
      }
}