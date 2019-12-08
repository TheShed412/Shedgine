#include <GL/glew.h>
#include <GL/freeglut.h>


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);//optional
    glutInitWindowSize(800, 600); //optional
    glutCreateWindow("Lol not my first window");
    
    glutMainLoop();
    return 0;
}