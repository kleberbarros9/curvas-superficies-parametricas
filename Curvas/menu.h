// menu.h

#ifndef _MENU_H
#define _MENU_H

// Menu structure (one submenu):
// Hermite
// Bezier
// BSpline
// Cardinal
// Lagrange Interpolation
// ----------------------
// HELP --> LMB drag ...
//          UP/DOWN keys ...
//          LEFT/RIGHT keys ...
// Exit

// Main menu entries
const int HERMITE  = 1;
const int BEZIER   = 2;
const int CARDINAL = 3;
const int BSPLINE  = 4;
const int LAGRANGE = 5;
const int EXIT     = 6;

// menu initialization:
void menu_init( void );

// menu handlers
void main_menu( int val );
void help_menu( int val );

#endif