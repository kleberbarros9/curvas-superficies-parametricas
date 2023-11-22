// splines.cpp

#include "main.h"

// globals:
double P1[2], P2[2], P3[2], P4[2];	// geometric constraints: control points
double R1[2], R4[2];				// geometric constraints: Hermite tangents
int method; // Hermite, Bezier, BSpline, Catmull-Rom, Lagrange ?
int n_tval; // # parameter values to evaluate
double tension, tau; // Cardinal spline tension

// Hermite basis functions
double BH0( double t ) { return ( ( 2*t*t*t) - (3*t*t) + 1); }
double BH1( double t ) { return ( (-2*t*t*t) + (3*t*t)    ); }
double BH2( double t ) { return ( (   t*t*t) - (2*t*t) + t); }
double BH3( double t ) { return ( (   t*t*t) - (  t*t)    ); }

// Bezier basis functions
double BB0( double t ) { return ( (1-t)*(1-t)*(1-t) ); }
double BB1( double t ) { return ( (3*t)*(1-t)*(1-t) ); }
double BB2( double t ) { return ( (3*t*t)*(1-t)     ); }
double BB3( double t ) { return ( (t*t*t)           ); }

// BSpline basis functions
double BBS0( double t ) { return ( (1.0/6.0)*(( 1-t)*(1-t)*(1-t)        ) ); }
double BBS1( double t ) { return ( (1.0/6.0)*(( 3*t*t*t)-(6*t*t)+      4) ); }
double BBS2( double t ) { return ( (1.0/6.0)*((-3*t*t*t)+(3*t*t)+(3*t)+1) ); }
double BBS3( double t ) { return ( (1.0/6.0)*((   t*t*t)                ) ); }

// Cardinal basis functions
double BCD0( double t ) { return ( ( -tau)*(t*t*t)+(  2*tau)*(t*t)-tau*(t) ); }
double BCD1( double t ) { return ( (2-tau)*(t*t*t)+(  tau-3)*(t*t)+(1)     ); }
double BCD2( double t ) { return ( (tau-2)*(t*t*t)+(3-2*tau)*(t*t)+tau*(t) ); }
double BCD3( double t ) { return ( (tau  )*(t*t*t)-(tau    )*(t*t)         ); }

// Implements Q(t) = SUM( Bi * Pi )
void HermitePoint( double t, double& x, double& y)
{
	x = BH0(t)*P1[0] + BH1(t)*P4[0] + BH2(t)*R1[0] + BH3(t)*R4[0];
	y = BH0(t)*P1[1] + BH1(t)*P4[1] + BH2(t)*R1[1] + BH3(t)*R4[1];
}

void BezierPoint( double t, double& x, double& y)
{
	x = BB0(t)*P1[0] + BB1(t)*P2[0] + BB2(t)*P3[0] + BB3(t)*P4[0];
	y = BB0(t)*P1[1] + BB1(t)*P2[1] + BB2(t)*P3[1] + BB3(t)*P4[1];
}

void BSplinePoint( double t, double& x, double& y)
{
	x = BBS0(t)*P1[0] + BBS1(t)*P2[0] + BBS2(t)*P3[0] + BBS3(t)*P4[0];
	y = BBS0(t)*P1[1] + BBS1(t)*P2[1] + BBS2(t)*P3[1] + BBS3(t)*P4[1];
}

void CardinalPoint( double t, double& x, double& y)
{
	x = BCD0(t)*P1[0] + BCD1(t)*P2[0] + BCD2(t)*P3[0] + BCD3(t)*P4[0];
	y = BCD0(t)*P1[1] + BCD1(t)*P2[1] + BCD2(t)*P3[1] + BCD3(t)*P4[1];
}