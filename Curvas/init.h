// init.h

#ifndef _INIT_H
#define _INIT_H

// initialization routines
void initGLUT(int *argc, char **argv);
void initOpenGL(void);
void initApp(void);

// global
extern GLuint arrow; // Hermite tangent vector

#endif