// keyboard.cpp

#include "main.h"

void keydown( unsigned char key, int x, int y )
{
	// Quit on ESC key:
	if( key == 27 ) exit(0);

	// Change the method used to draw the curve
	switch( key )
	{
	case 'H': case 'h': method = HERMITE;  break;
	case 'B': case 'b': method = BEZIER;   break;
	case 'C': case 'c': method = CARDINAL; break;
	case 'S': case 's': method = BSPLINE;  break;
	case 'L': case 'l': method = LAGRANGE; break;
	}

	// Show our changes:
	update_window_title();
	glutPostRedisplay();
}

void specialdown( int key, int x, int y )
{
	// Arrows control:
	// UP/DOWN:    number of points on the curve to evaluate
	// LEFT/RIGHT: Catmull-Rom tension
	switch( key )
	{
	case GLUT_KEY_UP:    ++n_tval;
						 break;
	case GLUT_KEY_DOWN:  if( 2 < n_tval ) --n_tval;
					     break;

	case GLUT_KEY_LEFT:  // N/A except for Cardinal spline
		                 if( method != CARDINAL) break;
		                 if( -1.0 < tension )
						 {
							 tension -= 0.05;
							 tau = 0.5*(1.0-tension);
						 }
						 break;

	case GLUT_KEY_RIGHT: // N/A except for Cardinal spline
		                 if( method != CARDINAL) break;
		                 if( tension < +2.0 ) 
						 {
							 tension += 0.05;
							 tau = 0.5*(1.0-tension);
						 }
						 break;
    }

	// Show our changes:
	update_window_title();
	glutPostRedisplay();
}