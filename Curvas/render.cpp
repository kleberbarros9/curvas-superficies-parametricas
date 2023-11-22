// render.cpp

#include "main.h"

// Background processing when no other GLUT events to handle
// (just keep the display updated, with a little pause for better interactivity)
void idle(void)
{
	Sleep(50);
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw_net();				// draw the curve's control net,
	draw_control_pts();		// its control points,
	draw_curve();			// and draw the curve itself.
	label_control_pts();	// (1, 2, 3 or 4)
	
	glutSwapBuffers();
}

void draw_curve()
{
	double t = 0.0; // parametric curves in t
	double x, y;	// cartesian coordinates

	glLineWidth(3);
	glDisable( GL_LINE_STIPPLE ); // curve is solid, control net is dashed

	// Evaluate Q(t) for the given number of parameter values,
	// producing 'n_tval' points on the curve. Draw an OpenGL
	// LINE_STRIP from point to point:

	glBegin(GL_LINE_STRIP);
	for(int i = 1; i <= n_tval; ++i)
	{
		switch( method )
		{              // type of curve         // curve's color
		case HERMITE:  HermitePoint(t, x, y );  glColor3f(1.0,0.0,0.0); break;
		case BEZIER:   BezierPoint(t, x, y );   glColor3f(0.0,0.5,0.0); break;
		case BSPLINE:  BSplinePoint(t, x, y );  glColor3f(0.0,0.0,1.0); break;
		case CARDINAL: CardinalPoint(t, x, y ); glColor3f(0.8,0.0,0.8); break;
		case LAGRANGE: LagrangePoint(t, x, y ); glColor3f(0.0,0.0,0.0); break;
		}
		glVertex2d(x,y);
		t += 1.0/(n_tval-1); // next parameter value
	}
	glEnd();

	glLineWidth(1);
}

// =====================================
void draw_net()
{
	// Not drawing a spline with this method:
	if( method == LAGRANGE ) return;

	glEnable( GL_LINE_STIPPLE ); // curve is solid, control net is dashed

	switch( method )
	{              // curve's color
	case HERMITE:  glColor3f(1.0,0.0,0.0); break;
	case BEZIER:   glColor3f(0.0,0.5,0.0); break;
	case BSPLINE:  glColor3f(0.0,0.0,1.0); break;
	case CARDINAL: glColor3f(0.8,0.0,0.8); break;
	}

	// Not really a control net for a cubic Hermite curve,
	// but we can draw the endpoint tangent vectors:
	if( method == HERMITE )
	{
		draw_tangent(2, P1[0],P1[1], P2[0],P2[1], R1[0],R1[1]);
		draw_tangent(3, P4[0],P4[1], P3[0],P3[1], -R4[0],-R4[1]);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
			glVertex2dv( P1 );
			glVertex2dv( P2 );
			glVertex2dv( P3 );
			glVertex2dv( P4 );
		glEnd();
	}
}

// Draw a Hermite tangent vector as an 'arrow'
void draw_tangent(int i, double x1, double y1, double x2, double y2, double vx, double vy)
{
	// 'i' is the arrow head's pick id
	// x1,y1 are coordinates of the arrow tail
	// x2,y2 are coordinates of the arrow head
	// vx,vy are the tangent's vector components

	// Draw the line
	glBegin(GL_LINES);
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
	glEnd();

	// Draw the arrow head
	glPushMatrix();
		// translate to the arrow head position
		glTranslatef(x2, y2, 0);
		// rotate to the proper orientation (in 2D: about the Z-axis)
		glRotatef((180/3.14159)*atan2(vy,vx), 0.0, 0.0, 1.0);
		// scale large enough to pick, but not too big:
		glScalef(0.4, 0.4, 0.4);
		// pick id
		glLoadName(i);
		// Now actually draw it
		glCallList(arrow);
	glPopMatrix();
}

void draw_control_pts()
{
	double x, y;

	// Control points get drawn in slightly different
	// colors in case they are dragged to overlap.
	// They are drawn as 'cubes' for convenience.

	// Draw control point #1
	glColor3f(0,0,0);
	glPushMatrix();
		x = P1[0]; y = P1[1];
		glTranslatef(x,y, 0.0);
		glScaled( 0.05, 0.05, 1.0 );
		glLoadName(1);
		glutSolidCube(1.0);
	glPopMatrix();

	// Hermite curve does not have the middle 2 control points 
	if( method != HERMITE )
	{
		// Draw control point #2
		glColor3f(0.15,0.15,0.15);
		glPushMatrix();
			x = P2[0]; y = P2[1];
			glTranslatef(x,y, 0.0);
			glScaled( 0.05, 0.05, 1.0 );
			glLoadName(2);
			glutSolidCube(1.0);
		glPopMatrix();
		// Draw control point #3
		glColor3f(0.3,0.3,0.3);
		glPushMatrix();
			x = P3[0]; y = P3[1];
			glTranslatef(x,y, 0.0);
			glScaled( 0.05, 0.05, 1.0 );
			glLoadName(3);
			glutSolidCube(1.0);
		glPopMatrix();
	}
	// Draw control point #4
	glColor3f(0.45,0.45,0.45);
	glPushMatrix();
		x = P4[0]; y = P4[1];
		glTranslatef(x,y, 0.0);
		glScaled( 0.05, 0.05, 1.0 );
		glLoadName(4);
		glutSolidCube(1.0);
	glPopMatrix();
}

// Label each control point with it's number: 1, 2, 3, or 4
void label_control_pts()
{
	double x, y;
	glColor3f(0,0,0);

	x = P1[0]; y = P1[1];
	glRasterPos2d( x-0.025, y-0.12 );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, '1' );

	if( method != HERMITE )
	{
		x = P2[0]; y = P2[1];
		glRasterPos2d( x-0.025, y-0.12 );
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, '2' );

		x = P3[0]; y = P3[1];
		glRasterPos2d( x-0.025, y-0.12 );
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, '3' );
	}

	x = P4[0]; y = P4[1];
	glRasterPos2d( x-0.025, y-0.12 );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, '4' );

}

void update_window_title( void )
{
	char title[128];
	switch( method )
	{
	case HERMITE:  sprintf( title, "%s, evaluated at %i t parameter values", "Hermite spline", n_tval); break;
	case BEZIER:   sprintf( title, "%s, evaluated at %i t parameter values", "Bezier spline", n_tval);  break;
	case BSPLINE:  sprintf( title, "%s, evaluated at %i t parameter values", "BSpline spline", n_tval); break;
	case CARDINAL:
		if( fabs(tension) < 0.001 ) // special case of Cardinal spline
			sprintf( title, "%s, evaluated at %i t parameter values, tension = %.2f", "Catmull-Rom spline", n_tval, tension);
		else
			sprintf( title, "%s, evaluated at %i t parameter values, tension = %.2f", "Cardinal spline", n_tval, tension); break;

	case LAGRANGE: sprintf( title, "%s, evaluated at %i t parameter values", "Lagrange interpolation", n_tval); break;
	}
	strcat( title, " (RMB = menu)" );
	glutSetWindowTitle(title);
}
