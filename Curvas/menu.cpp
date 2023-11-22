// menu.cpp

#include "main.h"

void menu_init(void)
{
	// Build the submenu first, to be added to the main menu.
	// Items in this menu are just help text - no action when selected.
	GLuint helpmenu_id = glutCreateMenu(help_menu);
	glutAddMenuEntry("LMB drag = Move control pt or Hermite tangent", 0);
	glutAddMenuEntry("UP/DOWN keys = # of t parameter values", 0);
	glutAddMenuEntry("LEFT/RIGHT keys = Cardinal spline tension", 0);

	// Build the main menu:
	glutCreateMenu(main_menu);
	glutAddMenuEntry("(H) Hermite ", HERMITE  );
	glutAddMenuEntry("(B) Bezier  ", BEZIER   );
	glutAddMenuEntry("(C) Cardinal", CARDINAL );
	glutAddMenuEntry("(S) BSpline ", BSPLINE  );
	glutAddMenuEntry("(L) Lagrange", LAGRANGE );
	glutAddMenuEntry("--------------------", 0);
	glutAddSubMenu("HELP", helpmenu_id);
	glutAddMenuEntry("Exit", EXIT);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main_menu( int val )
{
	if( val == EXIT ) exit(0);
	if( val == 0    ) return;  // ----- separator was selected

	method = val;
	update_window_title();
	glutPostRedisplay();
}

void help_menu( int val )
{
	return; // This menu just displays help text - no action taken
}
