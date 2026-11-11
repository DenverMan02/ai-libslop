#ifndef __CURVEDVAL_H__
#define __CURVEDVAL_H__

#include "Common.h"
#include "Color.h"
#include "SexyMath.h"

namespace Sexy
{

//This would blow through the stack on PS3 when parsing the curve val definition.
// also seems like a whole lot of points...
//yikes... same problem on VITA... totally unncessary...
#if defined(HOST_PS3) || defined(HOST_VITA) || defined(HOST_IPHONEOS) 
#define CV_NUM_SPLINE_POINTS 64
#else
#define CV_NUM_SPLINE_POINTS 256
#endif
class FastCurve;
class CurvedVal
{
public:
	enum
	{
		MODE_CLAMP,
		MODE_REPEAT,
		MODE_PING_PONG,
	};

	enum
	{
		RAMP_NONE,
		RAMP_LINEAR,	
		RAMP_SLOW_TO_FAST,
		RAMP_FAST_TO_SLOW,
		RAMP_SLOW_FAST_SLOW,
		RAMP_FAST_SLOW_FAST,
		RAMP_CURVEDATA
	};

	enum
	{
		DFLAG_NOCLIP			= 1,
		DFLAG_SINGLETRIGGER		= 2,
		DFLAG_OUTPUTSYNC		= 4,
		DFLAG_HERMITE			= 8,
		DFLAG_AUTOINC			= 16
	};


	class DataPoint 
	{
	public:	
		float					mX;
		float					mY;
		float					mAngleDeg;
	};

	class CurveCacheRecord
	{
	public:
		float					mTable[CV_NUM_SPLINE_POINTS];
		SexyMathHermite			mHermiteCurve;
		std::string				mDataStr;
	};

	typedef std::map<std::string, CurveCacheRecord> CurveCacheMap;
	typedef std::vector<DataPoint> DataPointVector;

public:
	static CurveCacheMap	mCurveCacheMap;

	double					mIncRate;
	double					mOutMin;
	double					mOutMax;

	const char**			mDataP;
	const char*				mCurDataPStr;
    std::string             mDataStr; //jvw- temp until I can rebuild the str in GetCurveStr
	int						mInitAppUpdateCount;	
	int*					mAppUpdateCountSrc;

	CurvedVal*				mLinkedVal;
	CurveCacheRecord*		mCurveCacheRecord;	
	double					mCurOutVal;
	double					mPrevOutVal;
		
	double					mInMin;
	double					mInMax;

    uint8					mMode;
    uint8					mRamp;	
    bool					mNoClip;
    bool					mSingleTrigger;	
    bool					mOutputSync;
    bool					mTriggered;
    bool					mIsHermite;
    bool					mAutoInc;

	double					mPrevInVal;
	double					mInVal;

protected:
	void                    InitVarDefaults();
	bool					CheckCurveChange();
	bool					CheckClamping();
	void					GenerateTable(DataPointVector* theDataPointVector, float* theBuffer, int theSize);
	void					ParseDataString(const std::string& theString);

public:
	CurvedVal();	

	// convenience constructors useful for static CurveVal initialization
	CurvedVal(const std::string& theData, CurvedVal* theLinkedVal = NULL);
    CurvedVal(const char** theDataP, CurvedVal* theLinkedVal = NULL);
    
    std::string             GetCurveStr();
    void                    SetCurveStr(const std::string& theData);

	void					SetCurve(const std::string& theData, CurvedVal* theLinkedVal = NULL);
	void					SetCurve(const char** theDataP, CurvedVal* theLinkedVal = NULL);
	
	void					SetCurveMult(const std::string& theData, CurvedVal* theLinkedVal = NULL);
	void					SetCurveMult(const char** theDataP, CurvedVal* theLinkedVal = NULL);
	void					SetConstant(double theValue);
	bool					IsInitialized();

	void					SetMode(int theMode);
	void					SetRamp(int theRamp);

	void					SetOutRange(double theMin, double theMax);
	void					SetInRange(double theMin, double theMax);

	double					GetOutVal();
	double					GetOutVal(double theInVal);
	double					GetOutValDelta();
	double                  GetOutFinalVal()           { return GetOutVal( mInMax ); }
	
	double					GetInVal();
	bool					SetInVal(double theVal, bool theRealignAutoInc = false);
	bool					IncInVal(double theInc);	
	bool					IncInVal();
	
	void                    Intercept( const char** theDataP, CurvedVal* theInterceptCv = NULL, double theCheckInIncrPct = 0.01, bool theStopAtLocalMin = false );
	void					Intercept( const std::string& theData, CurvedVal* theInterceptCv = NULL, double theCheckInIncrPct = 0.01, bool theStopAtLocalMin = false );

    // theStopAtLocalMin is a quick optimization to stop the search when the next value is a larger value than the previous. This optimization should only be used on 1-to-1 CurveVals.
    double                  FindClosestInToOutVal( double theTargetOutVal, double theCheckInIncrPct = 0.01, double theCheckInRangeMinPct = 0.0, double theCheckInRangeMaxPct = 1.0, bool theStopAtLocalMin = false );

	double					GetInValAtUpdate(int theUpdateCount);
	int						GetLengthInUpdates();
	bool					CheckInThreshold(double theInVal);	
	bool					CheckUpdatesFromEndThreshold(int theUpdateCount);

	bool					HasBeenTriggered();	
	void					ClearTrigger();
	bool					IsDoingCurve();

	operator				double() { return GetOutVal(); }
	operator				Color() { return Color(255, 255, 255, (int) (255 * GetOutVal())); }

	RA_METAMETHOD_TOSTRING(ToString)
	{
		return StrFormat("CV(%f -> %f)", GetInVal(), GetOutVal());
	}
};


//jvw-- experimental code to create a faster resampled version of curvevals. 
// use these for effects alpha/scale channels or places where detailed spline 
// interpolation is unnecessary
// the math is in floats to speed it up as well (on lower-power processors)

// Lots of features are removed... so don't count on them
// repeat modes, anything other than auto-inc, linking, fancy triggers...
class FastCurve
{
public:
	float					mOutMin;
	float					mOutMax;
	float					mInMin;
	float					mInMax;
	float					mIncRate;
	float					mInVal;
	//jvw.. todo. move some bools into flags
	bool					mTriggered;
	bool					mSingleTrigger;
	bool					mOutputSync;
protected:
	void					InitFromCurveData();
public:
	FastCurve();
	FastCurve(const std::string& theData, CurvedVal* theLinkedVal = NULL);
    FastCurve(const char** theDataP, CurvedVal* theLinkedVal = NULL);


	void					SetCurve(const std::string& theData, CurvedVal* theLinkedVal = NULL);
	void					SetCurve(const char** theDataP, CurvedVal* theLinkedVal = NULL);
	void					SetConstant(float theValue);

	float					GetOutVal() 
	{
		return GetOutVal(mInVal); 
	}

	float					GetOutVal(float theInVal);
	//float					GetOutValDelta();
	float                   GetOutFinalVal()           
	{ 
		return GetOutVal( mInMax ); 
	}

	void					SetOutRange(float theMin, float theMax);
	void					SetInRange(float theMin, float theMax);
	
	float					GetInVal() 
	{ 
		return mInVal; 
	}

	bool					SetInVal(float theVal, bool theRealignAutoInc = false);
	
	bool					IncInVal(float theInc);	
	bool					IncInVal() 
	{ 
		return IncInVal(mIncRate); 
	}

	bool					HasBeenTriggered();
	void					ClearTrigger();

	operator				float() 
	{ 
		return GetOutVal(); 
	}

	operator				Color() 
	{
		return Color(255, 255, 255, (int) (255 * GetOutVal())); 
	}
};

}

#endif //__CURVEDVAL_H__
