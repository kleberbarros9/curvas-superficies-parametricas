// view.h

#ifndef _VIEW_H
#define _VIEW_H

// Window dimensions
const int WINDOWW = 640; // GLUT window width
const int WINDOWH = 640; // GLUT window height

// World coordinates of the window corners
const float WORLDL = -1.0; // 2D orthographic view.
const float WORLDR = +1.0; // Defines the portion of the world
const float WORLDB = -0.5; // that will get mapped to the
const float WORLDT = +1.5; // viewport

// Viewport specification
const int VPL =  0;			// Viewport dimensions:
const int VPB =  0;         // the entire GLUT window
const int VPW =  WINDOWW;
const int VPH =  WINDOWH;

// Sets up the view
void reshape( int w, int h );

// Coordinate system conversion
void world2window(GLdouble worldx, GLdouble worldy, GLdouble& windowx, GLdouble& windowy);
void window2world(GLdouble windowx, GLdouble windowy, GLdouble& worldx, GLdouble& worldy);

#endif