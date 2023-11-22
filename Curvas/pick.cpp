// pick.cpp

#include "main.h"

int picked; // id of object that was picked

int pick(int pickx, int picky)
{
	// pickx, picky: mouse cursor position in window coordinates

	// Get the current viewport values (left, bottom, etc. ):
	GLint vp[4];
	glGetIntegerv (GL_VIEWPORT, vp);	

	// Allocate memory to hold pick information:
	GLuint pickBuffer[512] = {0};
	glSelectBuffer(512, pickBuffer);

	// Put OpenGL in "selection" mode:
	glRenderMode(GL_SELECT);

	// Initialize the name stack:
	glInitNames();
    glPushName(0);

	// Set up a special "pick" projection matrix.
	// We'll look for what's drawn in a box centered 
	// at the location of the mouse cursor:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity ();
	gluPickMatrix ((double)pickx, (double)picky, 1.0, 1.0, vp);
	gluOrtho2D(WORLDL, WORLDR, WORLDB, WORLDT);
	
	// Draw 'pickable' things in "selection" mode: framebuffer is NOT updated:
	if( method == HERMITE ) draw_net();
	draw_control_pts();

	// Restore the original projection:
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	// Go back to RENDER mode, giving us the number
	// of hits that occurred:
	GLint nhits = glRenderMode(GL_RENDER);

	// Our application only uses glLoadName(n), so there is only
	// ever **one** name on the name stack, and thus only one
	// one name in a hit record. A hit record in our selection
	// buffer will therefore look like this:
	//
	//   1          <-- 1st value in the hit record (pickBuffer[0])
	//   minimum z  <-- 2nd value in the hit record (pickBuffer[1])
	//   maximum z  <-- 3rd value in the hit record (pickBuffer[2])
	//   name       <-- 4th value in the hit record (pickBuffer[3])
	//
	// If there's been a 'hit', just return the name.
	// What gets picked will depend on drawing order, but that's okay for us.
	if( 0 < nhits  ) return pickBuffer[3];
	else			 return 0;
}
