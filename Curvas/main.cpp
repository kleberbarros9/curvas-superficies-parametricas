// main.cpp

/* 
Make:
g++ main.cpp init.cpp render.cpp keyboard.cpp Lagrange.cpp menu.cpp mouse.cpp pick.cpp splines.cpp view.cpp -o prog -lGL -lGLU -lglut -Llib -lm -g && ./prog
 */

#include "main.h"

int main(int argc, char **argv)
{
	// Initializations:
	initGLUT(&argc, argv); // GLUT
	initOpenGL();          // OpenGL
	initApp();             // This particular application

	glutMainLoop();        // start GLUT event processing ...

	return 0;
}








