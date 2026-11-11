#include <math.h>
#include "Point.h"

namespace Sexy
{
	class Graphics;
	class MemoryImage;
	class Buffer;
}

namespace Sexy
{

	// Adapted from "Essential Mathematics for Games" by James M. Van Verth/Lars M. Bishop
class Bezier
{
	public:
		float*				mTimes;
		float*				mLengths;
		float				mTotalLength;
		int					mCount;
		FPoint*				mControls;
		FPoint*				mPositions;					
		int					mCurveDetail;	

	protected:
		void SubdivideRender(Graphics* g, const FPoint& P0, const FPoint& P1, const FPoint& P2, const FPoint& P3);
		float SubdivideLength(const FPoint& P0, const FPoint& P1, const FPoint& P2, const FPoint& P3);

		// return length of curve between u1 and u2
		float SegmentArcLength(int i, float u1, float u2);

	public:
		Bezier();
		Bezier(const Bezier& rhs);
		~Bezier();
		Bezier& operator=(const Bezier& rhs);

		// There should be 2*(count - 1) controls specified
		bool				Init(const FPoint* positions, const FPoint* controls, const float* times, int count);
		
		// Will automatically generate control points for you based on positions
		bool				Init(const FPoint* positions, const float* times, int count);

		bool				IsInitialized()						{return mCount>0;}

		void				Serialize(Buffer* b);
		void				Deserialize(Buffer* b);

		FPoint				Evaluate(float t);
				
		FPoint				Velocity(float t, bool clamp = true);
		FPoint				Acceleration(float t);
		float				ArcLength(float t1, float t2);
		float				GetTotalLength() const				{return mTotalLength;}
		int					GetNumPoints() const				{return mCount;}

		void				Clean();
};	

}