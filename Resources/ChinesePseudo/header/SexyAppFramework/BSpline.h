#ifndef __BSPLINE_H__
#define __BSPLINE_H__
#include <vector>
#include <list>

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////	
class BSpline
{
protected:
	typedef std::vector<float> FloatVector;
	FloatVector mXPoints;
	FloatVector mYPoints;
	FloatVector mArcLengths;
	FloatVector mXCoef;
	FloatVector mYCoef;

	float GetPoint(float t, FloatVector &theCoef);
	void CalculateSplinePrv(FloatVector &thePoints, FloatVector &theCoef);
	void CalculateSplinePrvLinear(FloatVector &thePoints, FloatVector &theCoef);
	void CalculateSplinePrvSemiLinear(FloatVector &thePoints, FloatVector &theCoef);
	void CalcArcLengths();

public:
	BSpline();

	void Reset();

	void AddPoint(float x, float y);
	void CalculateSpline(bool linear = false);
	float GetXPoint(float t);
	float GetYPoint(float t);

	bool GetNextPoint(float &x, float &y, float &t, float i_maxStepDistance = 1.f, int i_stepFraction = 1); // goes one arclength
	const std::vector<float>& GetXPoints() const 		{ return mXPoints; }
    const std::vector<float>& GetYPoints() const 		{ return mYPoints; }

	int GetMaxT() { return (int)mXPoints.size() - 1; }
};

} // namespace Sexy;

#endif
