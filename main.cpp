#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);//optional
    glutInitWindowSize(800, 600); //optional
    glutCreateWindow("Lol not my first window");

    glewInit();
    if (glewIsSupported("GL_VERSION_3_0")) {
        std::cout << " GLEW Version is 3.0\n ";
    }
    else {
        std::cout << "GLEW not supported\n ";
    }

    glEnable(GL_DEPTH_TEST);
 
    // register callbacks
    glClearColor(0.0, 0.3, 0.3, 1.0);
    glutDisplayFunc(renderScene);
    
    glutMainLoop();
    return 0;
}