// main.h

#ifndef _MAIN_H
#define _MAIN_H

#ifdef WIN32
#include <windows.h>
// uncomment the next line to keep the console window from opening
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <GL/glut.h>
#include <time.h>
#include <stdio.h>

// include all headers here.
// All src files will include this one.
#include "init.h"		// initialization
#include "menu.h"		// the menu system
#include "view.h"		// window setup
#include "mouse.h"		// mouse handling
#include "render.h"		// display
#include "keyboard.h"	// quit, or modify spline parameters
#include "pick.h"		// dragging control points, Hermite tangents
#include "splines.h"	// calculate points on a spline curve
#include "Lagrange.h"   // Lagrange interpolation

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

#ifndef WIN32
#define Sleep(x) usleep(x*1000)
#endif

#endif