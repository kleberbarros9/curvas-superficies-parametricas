// init.cpp

#include "main.h"

GLuint arrow;  // Hermite tangent vector

void initGLUT(int *argc, char **argv)
{
	// Window creation
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOWW, WINDOWH);
	glutInitWindowPosition(50,50);
	glutCreateWindow("");

	// Rendering callbacks
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutReshapeFunc( reshape );

	// Keyboard input callbacks
	glutKeyboardFunc( keydown );
	glutSpecialFunc( specialdown );

	// Mouse input callbacks
	glutMouseFunc( mouse_btn );
	glutMotionFunc( mouse_drag );

	// User interface setup
	menu_init();
}

void initOpenGL(void)
{
	glClearColor(0.8,0.8,0.8,1);
	glPolygonMode( GL_FRONT, GL_FILL );
	glLineStipple( 1, 0x0f0f );

	// Construct an 'arrow' for drawing Hermite tangent vectors
	GLUquadricObj *obj = gluNewQuadric();
	{
		gluQuadricDrawStyle(obj, GLU_FILL);
		gluQuadricNormals(obj, GLU_SMOOTH);
		gluQuadricOrientation(obj, GLU_OUTSIDE);

		arrow = glGenLists(1);
		glNewList(arrow, GL_COMPILE);
			glBegin(GL_TRIANGLES);
				glVertex2f(+0.125, 0.0);
				glVertex2f(-0.125, +0.0625);
				glVertex2f(-0.125, -0.0625);
			glEnd();
		glEndList();
	}
	gluDeleteQuadric(obj);
}

void initApp(void)
{
	// Initial geometric constraints
	P1[0] = -0.6;  P1[1] =  0.0;
	P2[0] = -0.2;  P2[1] = +1.0;
	P3[0] = +0.2;  P3[1] = +1.0;
	P4[0] = +0.6;  P4[1] =  0.0;

	// Initial Hermite tangent constraints
	R1[0] = 3.0*(P2[0] - P1[0]);
	R1[1] = 3.0*(P2[1] - P1[1]);
    R4[0] = 3.0*(P4[0] - P3[0]);
	R4[1] = 3.0*(P4[1] - P3[1]);

	// Start with four points on a Hermite spline:
	method = HERMITE;
	n_tval = 6; // curve evaluated at this many parameter values

	// Start with this tension for Catmull-Rom spline:
	tension = 0.5;
	tau = 0.5*(1.0 - tension);

	update_window_title();
}