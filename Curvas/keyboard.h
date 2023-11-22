// keyboard.h

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

// callbacks to handle keyboard events
void keydown( unsigned char key, int x, int y ); // normal keys
void specialdown( int key, int x, int y ); // FN keys, arrows, ...

#endif