#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_
#include "bezier.h"

class bezierCurve : public bezier{
private:
	int numPoints;
	float **controlPoints;
	float **curvePoints;
	void calCurve();
public:
	bezierCurve(int numPoints, float *points[3]);
	void setShowPoints(bool showControlPoints);
	virtual void draw();
    ~bezierCurve();
};
#endif
