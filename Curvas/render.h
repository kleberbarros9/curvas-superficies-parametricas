// render.h

#ifndef _RENDER_H
#define _RENDER_H

// all rendering is done in this callback
void display(void);

// background processing when no events are pending
void idle(void);

// change what's displayed in the window title
void update_window_title(void);

// Render various parts of the curve
void draw_curve();
void draw_net();
void draw_control_pts();
void label_control_pts();
void draw_tangent(int i, double x1, double y1, double x2, double y2, double vx, double vy);

#endif