// Lagrange.cpp

#include "main.h"

//             n
// Implements L(t) for n = 3 (4 control points)
//             i
double Lin(int i, double t)
{
	// initialize the running product
	double L = 1.0; 

	// Use equally spaced parameter values
	// (cubic curve: 4 values in [0.0 1.0])
	double tj[4] = { 0.0, 1.0/3.0, 2.0/3.0, 1.0 };

	for(int j=0; j<4; j++)
	{
		if( i != j )
			L *= ( t - tj[j] ) / ( tj[i] - tj[j] );
	}

	return L;
}

//                         n
// Implements Q(t) = SUM( L(t) * Pi
//                         i
// (computes a point on the Lagrange curve)
void LagrangePoint( double t, double& x, double& y )
{
	x = P1[0]*Lin(0,t) + P2[0]*Lin(1,t) + P3[0]*Lin(2,t) + P4[0]*Lin(3,t);
	y = P1[1]*Lin(0,t) + P2[1]*Lin(1,t) + P3[1]*Lin(2,t) + P4[1]*Lin(3,t);
}