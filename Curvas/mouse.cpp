// mouse.cpp

#include "main.h"

void mouse_btn( int btn, int state, int mx, int my )
{
	// Convert GLUT's window coordinate system to OpenGL's
	my = WINDOWH - my;

	// Pick with the left mouse button
	if( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		if( picked = pick(mx, my) ) // a control point was picked
		{
			// convert mouse cursor coordinates to world coordinates
			double wx, wy;
			window2world(mx, my, wx, wy );

			// Now move the picked item: center it at the mouse cursor
			update_picked( picked, wx, wy );

			// Show our changes
			glutPostRedisplay();
		}
	}
}

void mouse_drag( int mx, int my )
{
	// Convert GLUT's window coordinate system to OpenGL's
	my = WINDOWH - my;

	// convert mouse cursor coordinates to world coordinates
	double wx, wy;
	window2world(mx, my, wx, wy );

	// Mouse drag => keep moving the picked item,
	// centering it at the mouse cursor
	update_picked( picked, wx, wy );

	// Show our changes
	glutPostRedisplay();
}

void update_picked( int picked, double wx, double wy )
{
	// Set control point coordinates to mouse cursor coordinates
	switch( picked )
	{
	case 1: P1[0] = wx; P1[1] = wy; break;
	case 2: P2[0] = wx; P2[1] = wy; break;
	case 3: P3[0] = wx; P3[1] = wy; break;
	case 4: P4[0] = wx; P4[1] = wy; break;
	}

	// Re-calculate Hermite contraints
	R1[0] = 3.0*(P2[0] - P1[0]);
	R1[1] = 3.0*(P2[1] - P1[1]);
	R4[0] = 3.0*(P4[0] - P3[0]);
	R4[1] = 3.0*(P4[1] - P3[1]);
}