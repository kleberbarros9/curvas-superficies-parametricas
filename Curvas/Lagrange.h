// Lagrange.h

#ifndef _LAGRANGE_H
#define _LAGRANGE_H

//             n
// Implements L(t) for n = 3 (4 control points)
//             i
double Lin(int i, double t);

//                         n
// Implements Q(t) = SUM( L(t) * Pi
//                         i
// (computes a point on the Lagrange curve)
void LagrangePoint( double t, double& x, double& y );

#endif