// view.cpp

#include "main.h"

void reshape( int w, int h )
{
	// This application does not allow window resize
	glViewport(VPL, VPB, VPW, VPH);

	// 2D Orthographic projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( WORLDL, WORLDR, WORLDB, WORLDT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


// Coordinate system transformation
void world2window(GLdouble worldx, GLdouble worldy, GLdouble& windowx, GLdouble& windowy)
{
	windowx = (worldx - WORLDL)*WINDOWW/(WORLDR-WORLDL);
	windowy = (worldy - WORLDB)*WINDOWH/(WORLDT-WORLDB);
}

void window2world(GLdouble windowx, GLdouble windowy, GLdouble& worldx, GLdouble& worldy)
{
	worldx = WORLDL + (WORLDR-WORLDL)*windowx/WINDOWW;
	worldy = WORLDB + (WORLDT-WORLDB)*windowy/WINDOWH;
}