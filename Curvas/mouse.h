// mouse.h

#ifndef _MOUSE_H
#define _MOUSE_H

// handle mouse button down/up events
void mouse_btn( int btn, int state, int mx, int my );

// handle mouse move events (motion with a button DOWN)
void mouse_drag( int mx, int my );

// helper function to modify the displayed curve when the
// mouse was used to move a control point or a Hermite tangent
void update_picked( int picked, double wx, double wy );

#endif