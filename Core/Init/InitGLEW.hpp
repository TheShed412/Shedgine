#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Core{
       //notice that I added another namespace here(optional)
     namespace Init{ 
 
           class Init_GLEW
          {
             public:
                static void Init();
           };
      }
}