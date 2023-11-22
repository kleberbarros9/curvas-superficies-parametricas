// splines.h

#ifndef _SPLINES_H
#define _SPLINES_H

// Functions to compute a point on a spline curve
void HermitePoint( double t, double& x, double& y);
void BezierPoint( double t, double& x, double& y);
void BSplinePoint( double t, double& x, double& y);
void CardinalPoint( double t, double& x, double& y);

// Blending functions
double BH0( double t );
double BH1( double t );
double BH2( double t );
double BH3( double t );

double BB0( double t );
double BB1( double t );
double BB2( double t );
double BB3( double t );

double BBS0( double t );
double BBS1( double t );
double BBS2( double t );
double BBS3( double t );

double BCD0( double t );
double BCD1( double t );
double BCD2( double t );
double BCD3( double t );

// globals:
extern double P1[2], P2[2], P3[2], P4[2], R1[2], R4[2]; // geometric constraints
extern int method; // Hermite, Bezier, BSpline, Cardinal, Lagrange ?
extern int n_tval; // # parameter values to evaluate
extern double tension, tau; // Cardinal spline tension

#endif