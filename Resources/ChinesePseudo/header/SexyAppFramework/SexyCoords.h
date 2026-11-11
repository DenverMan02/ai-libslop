#pragma once
#ifndef __SEXYCOORDS_H__
#define __SEXYCOORDS_H__
//****************************************************************************
//**
//**  File     :  SEXYCOORDS.H
//**  Summary  :  Header - 3D coordinate frame classes
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "SexyVector.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
/*
	SexyAxes3 & SexyCoords3

	_____Overview

	These classes represent a three-vector orthonormal coordinate frame,
	used to describe affine transformations involving translation, rotation,
	and scale (very common in 3D graphics).  SexyAxes3 is strictly an axial
	frame for rotation/orientation purposes, and SexyCoords3 adds translation
	and scaling factors.

	They are like a subset of general 4x4 matrices in the sense that they don't
	support arbitrary one-way operations that can be jammed into a matrix (such
	as projection, shearing, etc; if you are in need of these kinds of one-way
	operations then a more conventional matrix class like SexyMatrix4 may be
	more appropriate for you; SexyCoords3 provides convenience conversions to
	SexyMatrix4 if you need them).  However, for common operations involving
	scale-rotate-translate or translate-rotate-scale transformation chains,
	these classes can be used to work with these 3D spaces in a more "visual"
	and intuitive fashion.
	
	The benefit of using these classes is that the three translate/rotate/scale
	elements are kept independent of each other, and thus allow for simpler
	"bi-directional" transformation than a conventional matrix (in other words,
	an inverse transformation can be done without having to compute a separate
	inverse matrix).  The few additional computations required are outweighed
	by this ease of manipulation; once you've got a final coordinate frame and
	are ready for "bulk" transformation, you can convert to a SexyMatrix4 once
	you feel it's appropriate.

	Understanding this bi-directionality is a key part of working with these
	classes.  Whereas one-way transformation with matrices is done via matrix
	multiplication, transformation with these coordinate frame classes is done
	via "entering" and "leaving" different coordinate frames.

	_____Structure

	The coordinate frame is a trio of orthonormal vectors (usually
	unit-length) shaped like this...

	    y
	    |
	    |
	    ------x
	   /
      /
     z

	...but rotated arbitrarily.  SexyCoords3 allows this coordinate frame
	to be translated and scaled as well.
	 
	To picture this, make a coordinate frame shape with your right hand (point your
	thumb to the right, your index finger up, and bend your middle finger out toward
	you; 3D programmers do this kind of thing often).  Now move your hand around you
	and imagine this frame flying through space, translated and rotated arbitrary.
	You can then also imagine that your fingers were longer or shorter, to represent
	scaling.

	This may seem like a silly exercise, but it can help to picture what a coordinate
	frame is in your mind, which can make them much easier to work with.

	_____Enter and Leave

	The key transformation methods of SexyAxes3/SexyCoords3 are the "Enter" and
	"Leave" methods.  Complex hierarchical transformations are performed via these
	methods, allowing individual vectors or entire coordinate frames to enter (become
	relative to) or leave (become peer to) other coordinate frames.

	Let's say we have two coordinate frames A and B (do the exercise from the previous
	section with your hands, but hold out both hands; your left hand represents A and
	your right represents B).  Both are currently in "global" 3D space.

	Now let's say we want to make A relative to B.  We could go:

	A = A.Enter(B);

	and now the values for A would no longer be meaningful in "global" space; they would
	now be in "B space".  Let's say we then take B and rotate it by an angle:

	B.RotateRadX(anAngle);

	All we've done here is change B; A itself is unaffected numerically since it's
	still the same in "B space".  However if we now decide we want A to GO BACK to global
	3D space...

	A = A.Leave(B);

	It will come out as if the entire frame of A was rotated about the center of B,
	by that angle.  Picture this as if B (your right hand) was the center of a wheel,
	and A (your left hand) was on the edge of that wheel; when that wheel rotates,
	the entire contents of A (not just its center, but its axial vectors as well) will
	come along for the ride.

	For another example, let's go back to where B was being rotated (when A was still
	relative to it), and in addition to rotating B, we'll scale it as well.

	B.RotateRadX(anAngle);
	B.Scale(aScale);

	This time, when we go...

	A = A.Leave(B);

	...not only will A have been rotated, but it will have been scaled as well, because
	the space it was in was scaled while it was in it.

	If you're used to working with 2D hierarchical "widgets", these coordinate frames
	allow you to work in 3D space using very similar concepts.  For example, if you had
	a skeletal hierarchy like your arm, each bone could be defined as a space relative
	to its parent bone.  The wrist is in elbow space, the elbow is in shoulder space, etc.
	So if you set up a tree of bones where every bone had a coordinate frame and a link
	to a parent bone (until the root), at any time you could get a coordinate frame for
	a bone in terms of global 3D space just by repeatedly "leaving" the chain of parents
	in sequence, until you finally leave the root.

	Don't worry if it all sounds a little weird at first (especially if you're not used
	to working in 3D); this can take some time to get used to, but hopefully in the end
	you'll find it well worth the effort.

	_____Shift Operators

	For those who are comfortable with operator overloading, these classes also overload
	the shift operators as synonyms with Enter and Leave.  Think of the shifts as "arrows"
	in this case:

	A >>= B; // equivalent to A = A.Enter(B);
	A <<= B; // equivalent to A = A.Leave(B);
	C = A >> B; // equivalent to C = A.Enter(B);
	C = A << B; // equivalent to C = A.Leave(B);

	_____By the way

	Keep in mind that Enter and Leave are const methods that return the results of the
	enter/leave operation.  This is so that the operations can be chained together
	in a single expression, such as...
	
	A = A.Leave(B).Enter(C);
	
	...which is a somewhat common operation.  Keep this in mind so that you don't forget
	to assign the result of the method.  If you are concerned about this issue biting
	you, you could always use the shift-assignment operators mentioned above as an
	alternative.

	Also, by default these classes use a right-handed frame where Y points up
	and Z points out of the screen.  If you are used to working with left-handed
	axial frames you will have to make the necessary adjustments on the calling side.
*/

#include "SexyMath.h"

class SexyAxes3
{
public:
	SexyVector3 vX, vY, vZ;

public:
	SexyAxes3() : vX(1,0,0), vY(0,1,0), vZ(0,0,1) {}
	SexyAxes3(const SexyAxes3& inA) : vX(inA.vX), vY(inA.vY), vZ(inA.vZ) {}
	SexyAxes3(const SexyVector3& inX, const SexyVector3& inY, const SexyVector3& inZ) : vX(inX), vY(inY), vZ(inZ) {}

	SexyAxes3& operator= (const SexyAxes3& inA) { vX = inA.vX; vY = inA.vY; vZ = inA.vZ; return *this; }

	SexyAxes3 Enter(const SexyAxes3& inAxes) const
	{
		return SexyAxes3(vX.Enter(inAxes), vY.Enter(inAxes), vZ.Enter(inAxes));
	}
	SexyAxes3 Leave(const SexyAxes3& inAxes) const
	{
		return SexyAxes3(vX.Leave(inAxes), vY.Leave(inAxes), vZ.Leave(inAxes));
	}

	SexyAxes3& operator>>= (const SexyAxes3& inA) { *this = Enter(inA); return *this; }
	SexyAxes3& operator<<= (const SexyAxes3& inA) { *this = Leave(inA); return *this; }
	SexyAxes3 operator>> (const SexyAxes3& inA) const { return Enter(inA); }
	SexyAxes3 operator<< (const SexyAxes3& inA) const { return Leave(inA); }
	
	SexyAxes3 Inverse() const
	{
		return SexyAxes3().Enter(*this);
	}
	SexyAxes3 OrthoNormalize() const
	{
		SexyAxes3 a(*this);
		a.vX = a.vY.Cross(a.vZ).Normalize();
		a.vY = a.vZ.Cross(a.vX).Normalize();
		a.vZ = a.vX.Cross(a.vY).Normalize();
		return a;
	}
	SexyAxes3 DeltaTo(const SexyAxes3& inAxes) const
	{
		return inAxes.Inverse().Leave(*this);
	}

	/*
		Spherical-linear interpolation to another axial frame.  inAlpha is between 0.0 and 1.0,
		where 0.0 is the current frame and 1.0 is inAxes.  If inFastButLessAccurate is true,
		a slightly quicker computation will be used internally that won't give exactly the same
		arc of interpolation, but may be close enough for most needs, and can save a bit of CPU
		time when a lot of slerps are being done.  Returns the slerped axial frame.
	*/
	SexyAxes3 SlerpTo(const SexyAxes3& inAxes, float inAlpha, bool inFastButLessAccurate = false) const;

	/*
		Rotate about an arbitrary axis.  Should be a unit vector; please make sure any axis
		passed into this function has been normalized before calling.
	*/
	void RotateRadAxis(float inRot, const SexyVector3& inNormalizedAxis);

	void RotateRadX(float inRot)
	{
		MATH_TYPE sinRot = MATH_TYPE(sinf(inRot));
		MATH_TYPE cosRot = MATH_TYPE(cosf(inRot));

		SexyAxes3 a;
		a.vY.y = cosRot;
		a.vZ.y = -sinRot;
		a.vY.z = sinRot;
		a.vZ.z = cosRot;

		*this = Leave(a);
	}
	void RotateRadY(float inRot)
	{
		MATH_TYPE sinRot = MATH_TYPE(sinf(inRot));
		MATH_TYPE cosRot = MATH_TYPE(cosf(inRot));

		SexyAxes3 a;
		a.vX.x = cosRot;
		a.vX.z = -sinRot;
		a.vZ.x = sinRot;
		a.vZ.z = cosRot;

		*this = Leave(a);
	}
	void RotateRadZ(float inRot)
	{
		MATH_TYPE sinRot = MATH_TYPE(sinf(inRot));
		MATH_TYPE cosRot = MATH_TYPE(cosf(inRot));

		SexyAxes3 a;
		a.vX.x = cosRot;
		a.vX.y = sinRot;
		a.vY.x = -sinRot;
		a.vY.y = cosRot;

		*this = Leave(a);
	}
	inline void LookAt(const SexyVector3& inTargetDir, const SexyVector3& inUpVector)
	{		
		SexyVector3 tempZ = inTargetDir.Normalize();
		if (SexyMath::Fabs(float(inUpVector.Dot(tempZ))) > (1.f - SEXYMATH_EPSILON))
			return; // up vector and Z vector are colinear, abort

		SexyAxes3 a;
		a.vZ = tempZ;
		a.vX = inUpVector.Cross(a.vZ).Normalize();
		a.vY = a.vZ.Cross(a.vX).Normalize();
		
		*this = Leave(a);
	}
};

/*
	SexyCoords3
*/
class SexyMatrix4;

class SexyCoords3
{
public:
	SexyVector3 t;
	SexyAxes3 r;
	SexyVector3 s;

public:
	SexyCoords3() : t(0,0,0), r(), s(1,1,1) {}
	SexyCoords3(const SexyCoords3& inC) : t(inC.t), r(inC.r), s(inC.s) {}
	SexyCoords3(const SexyAxes3& inR) : t(0,0,0), r(inR), s(1,1,1) {}
	SexyCoords3(const SexyVector3& inT, const SexyAxes3& inR, const SexyVector3& inS) : t(inT), r(inR), s(inS) {}

	SexyCoords3& operator= (const SexyCoords3& inC) { t = inC.t; r = inC.r; s = inC.s; return *this; }

	SexyCoords3 Enter(const SexyCoords3& inCoords) const
	{
		return SexyCoords3(t.Enter(inCoords), r.Enter(inCoords.r), s / inCoords.s);
	}
	SexyCoords3 Leave(const SexyCoords3& inCoords) const
	{
		return SexyCoords3(t.Leave(inCoords), r.Leave(inCoords.r), s * inCoords.s);
	}

	SexyCoords3& operator>>= (const SexyCoords3& inC) { *this = Enter(inC); return *this; }
	SexyCoords3& operator<<= (const SexyCoords3& inC) { *this = Leave(inC); return *this; }
	SexyCoords3 operator>> (const SexyCoords3& inC) const { return Enter(inC); }
	SexyCoords3 operator<< (const SexyCoords3& inC) const { return Leave(inC); }

	SexyCoords3 Inverse() const
	{
		return SexyCoords3().Enter(*this);
	}
	SexyCoords3 DeltaTo(const SexyCoords3& inCoords) const
	{
		return inCoords.Inverse().Leave(*this);
	}

	inline void Translate(MATH_TYPE inX, MATH_TYPE inY, MATH_TYPE inZ) { t += SexyVector3(inX, inY, inZ); }
	inline void RotateRadAxis(float inRot, const SexyVector3& inNormalizedAxis) { r.RotateRadAxis(inRot, inNormalizedAxis); }
	inline void RotateRadX(float inRot) { r.RotateRadX(inRot); }
	inline void RotateRadY(float inRot) { r.RotateRadY(inRot); }
	inline void RotateRadZ(float inRot) { r.RotateRadZ(inRot); }
	inline void Scale(MATH_TYPE inX, MATH_TYPE inY, MATH_TYPE inZ) { s *= SexyVector3(inX, inY, inZ); }

	inline bool LookAt(const SexyVector3& inTargetPos, const SexyVector3& inUpVector)
	{
		SexyVector3 tempZ = t - inTargetPos;
		if (tempZ.ApproxZero())
			return false; // need at least some distance from the target
		tempZ = tempZ.Normalize();
		if (SexyMath::Fabs(float(inUpVector.Dot(tempZ))) > (1.f - SEXYMATH_EPSILON))
			return false; // up vector and Z vector are colinear, abort
		r.vZ = tempZ;
		r.vX = inUpVector.Cross(r.vZ).Normalize();
		r.vY = r.vZ.Cross(r.vX).Normalize();
		return true;
	}
	inline bool LookAt(const SexyVector3& inViewPos, const SexyVector3& inTargetPos, const SexyVector3& inUpVector)
	{
		t = inViewPos;
		return LookAt(inTargetPos, inUpVector);
	}

	void GetInboundMatrix(SexyMatrix4* outM) const;
	void GetOutboundMatrix(SexyMatrix4* outM) const;
};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
inline SexyVector3 SexyVector3::Enter(const SexyAxes3& inAxes) const
{
	return SexyVector3(Dot(inAxes.vX), Dot(inAxes.vY), Dot(inAxes.vZ));
}
inline SexyVector3 SexyVector3::Enter(const SexyCoords3& inCoords) const
{
	return ((*this - inCoords.t).Enter(inCoords.r)) / inCoords.s;
}
inline SexyVector3 SexyVector3::Leave(const SexyAxes3& inAxes) const
{
	return SexyVector3(
		x*inAxes.vX.x + y*inAxes.vY.x + z*inAxes.vZ.x,
		x*inAxes.vX.y + y*inAxes.vY.y + z*inAxes.vZ.y,
		x*inAxes.vX.z + y*inAxes.vY.z + z*inAxes.vZ.z
		);
}
inline SexyVector3 SexyVector3::Leave(const SexyCoords3& inCoords) const
{
	return ((*this * inCoords.s).Leave(inCoords.r)) + inCoords.t;
}

//============================================================================
//    TRAILING HEADERS
//============================================================================

}
//****************************************************************************
//**
//**    END HEADER SEXYCOORDS.H
//**
//****************************************************************************
#endif // __SEXYCOORDS_H__
