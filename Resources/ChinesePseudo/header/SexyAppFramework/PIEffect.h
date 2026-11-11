#ifndef __PIREADER_H__
#define __PIREADER_H__

#include "Common.h"
#include "MTRand.h"
#include "Color.h"
#include "Buffer.h"
#include "Point.h"
#include "SexyMatrix.h"
#include "SharedImage.h"
#include "ObjectPool.h"
#include "Bezier.h"
#include "Rect.h"
#include "TriVertex.h"
#include "ResourceTypes.h"
#include "Image.h"

namespace Sexy
{

class DeviceImage;
class Graphics;
class Buffer;
class RenderDevice3D;

typedef std::vector<int> IntVector;
typedef std::map<int, int> IntToIntMap;
typedef std::map<std::string, std::string> StringToStringMap;

class DrawBatcher
{
public:
	RenderDevice3D*			mCurRenderDevice3D;
	SexyVertex2D			mDrawVertexList[1024][3];
	int						mDrawVertexIdx;
	int						mCurDrawMode;
	Image*					mCurImage;
	float					mCurTransX;
	float					mCurTransY;
	bool					mUseDrawPrimitive;

public:
	DrawBatcher();
	void					Setup(Graphics* g);
	void					FlushTriQueue();	
	
    inline void             QueueQuad(Image* theImage, int theDrawMode, SexyVertex2D theQuadPoints[4])
    {
        if ((mCurDrawMode != theDrawMode) || (mCurImage != theImage) || (mDrawVertexIdx >= 1024-2))
        {
            FlushTriQueue();
            mCurDrawMode = theDrawMode;
            mCurImage = theImage;
        }
        
        mDrawVertexList[mDrawVertexIdx][0] = theQuadPoints[0];
        mDrawVertexList[mDrawVertexIdx][1] = theQuadPoints[1];
        mDrawVertexList[mDrawVertexIdx][2] = theQuadPoints[2];
        mDrawVertexIdx++;
        mDrawVertexList[mDrawVertexIdx][0] = theQuadPoints[2];
        mDrawVertexList[mDrawVertexIdx][1] = theQuadPoints[1];
        mDrawVertexList[mDrawVertexIdx][2] = theQuadPoints[3];
        mDrawVertexIdx++;
    }
    
	SexyVertex2D*			StartVertexSection(Image* theImage, int theDrawMode, int theCount);
};

extern DrawBatcher gDrawBatcher;

class PIValuePoint
{
public:
	float					mTime;
	float					mValue;		
};

typedef std::vector<PIValuePoint> PIValuePointVector;

#define PI_QUANT_SIZE 256

class PIValue
{
public:
	std::vector<float>		mQuantTable;

	PIValuePointVector		mValuePointVector;
	Bezier					mBezier;
	float					mLastTime;
	float					mLastValue;

	float					mLastCurveT;
	float					mLastCurveTDelta;
	
public:
	PIValue()
	{
		mLastTime = -1.0f;
		mLastCurveT = 0.0f;
		mLastCurveTDelta = 0.01f; // To help first subdivision
		
	}

	void					QuantizeCurve();

	float					GetValueAt(float theTime, float theDefault = 0); // Frame number or (0.0 - 1.0) for "over life" values
	float					GetLastKeyframe(float theTime);
	float					GetLastKeyframeTime(float theTime);
	float					GetNextKeyframeTime(float theTime);	
	int						GetNextKeyframeIdx(float theTIme);
};

class PIValuePoint2D
{
public:	
	float					mTime;
	FPoint					mValue;		
};

typedef std::vector<PIValuePoint2D> PIValuePoint2DVector;

class PIValue2D
{
public:
	PIValuePoint2DVector	mValuePoint2DVector;
	Bezier					mBezier;
	float					mLastTime;
	FPoint					mLastPoint;
	float					mLastVelocityTime;
	FPoint					mLastVelocity;

public:
	PIValue2D()
	{
		mLastTime = -1;
	}

	FPoint					GetValueAt(float theTime);	
	FPoint					GetVelocityAt(float theTime);
};

typedef std::vector<PIValue2D> PIValue2DVector;

class PIInterpolatorPoint
{
public:
	int						mValue;
	float					mTime;
};

typedef std::vector<PIInterpolatorPoint> PIInterpolatorPointVector;

class PIInterpolator
{
public:
	PIInterpolatorPointVector mInterpolatorPointVector;

public:
	int						GetValueAt(float theTime);
	int						GetKeyframeNum(int theIdx); // Wraps
	float					GetKeyframeTime(int theIdx); // Wraps
};

typedef std::vector<MixedImagePtr> PIImageVector;

class PITexture;

class PITextureChunk
{
public:
	PITexture*				mSrcTexture;
	Image*					mImage;	
	float					mScaleXFactor;
	float					mScaleYFactor;	
	float					mRefOfsX;
	float					mRefOfsY;
	float					mU1;
	float					mV1;
	float					mU2;
	float					mV2;
	float					mScaleRef;
};

class PITexture
{
public:
	std::vector<PITextureChunk> mTextureChunkVector;	
	std::string				mName;
	PIImageVector			mImageVector;	
	ImagePtr				mImageStrip;
	int						mNumCels;
	bool					mPadded;
};

typedef std::vector<PITexture*> PITextureVector;

class PIEmitter;

//#define LIFEVALUE_SAMPLE_SIZE 8
//#define LIFEVALUE_SAMPLE_SHIFT (31-3)  

#define LIFEVALUE_SAMPLE_SIZE 32
#define LIFEVALUE_SAMPLE_SHIFT (31-5)  

class PILifeValueSample
{
public:
	float					mSizeX;
	float					mSizeY;
	float					mVelocity;
	float					mWeight;
	float					mSpin;
	float					mMotionRand;
	ulong					mColor;
};

class PILifeValueTable
{
public:
	enum
	{
		LIFEVALUE_SIZE_X,
		LIFEVALUE_SIZE_Y,
		LIFEVALUE_VELOCITY,
		LIFEVALUE_WEIGHT,
		LIFEVALUE_SPIN,
		LIFEVALUE_MOTION_RAND,
		LIFEVALUE_COLOR,		
		LIFEVALUE_ALPHA,
		NUM_LIFEVALUES
	};

public:
	PILifeValueSample		mLifeValuesSampleTable[LIFEVALUE_SAMPLE_SIZE+1];	
};

typedef std::map<std::string, PILifeValueTable> PILifeValueTableMap;

class PIParticleDefInstance;

class PIParticleDef
{
public:
	enum
	{
		VALUE_LIFE,
		VALUE_NUMBER,
		VALUE_SIZE_X,
		VALUE_VELOCITY,
		VALUE_WEIGHT,
		VALUE_SPIN,
		VALUE_MOTION_RAND,
		VALUE_BOUNCE,
		VALUE_LIFE_VARIATION,
		VALUE_NUMBER_VARIATION,
		VALUE_SIZE_X_VARIATION,
		VALUE_VELOCITY_VARIATION,
		VALUE_WEIGHT_VARIATION,
		VALUE_SPIN_VARIATION,
		VALUE_MOTION_RAND_VARIATION,
		VALUE_BOUNCE_VARIATION,
		VALUE_SIZE_X_OVER_LIFE,
		VALUE_VELOCITY_OVER_LIFE,
		VALUE_WEIGHT_OVER_LIFE,
		VALUE_SPIN_OVER_LIFE,
		VALUE_MOTION_RAND_OVER_LIFE,
		VALUE_BOUNCE_OVER_LIFE,
		VALUE_VISIBILITY,
		VALUE_EMISSION_ANGLE,
		VALUE_EMISSION_RANGE,

		VALUE_SIZE_Y,
		VALUE_SIZE_Y_VARIATION,
		VALUE_SIZE_Y_OVER_LIFE,

		NUM_VALUES
	};	

public:	
	static PILifeValueTableMap mPILifeValueTableMap;
	PILifeValueTable*		mLifeValueTable;
	
	PIEmitter*				mParent;
	std::string				mName;
	int						mTextureIdx;
	std::vector<PITextureChunk> mTextureChunkVector;
	PIValue					mValues[NUM_VALUES];
	FPoint					mRefPointOfs;
	bool					mLockAspect;
	bool					mIntense;		
	bool					mSingleParticle;
	bool					mPreserveColor;
	bool					mAttachToEmitter;
	int						mAnimSpeed;
	bool					mAnimStartOnRandomFrame;
	float					mAttachVal;
	bool					mFlipHorz;
	bool					mFlipVert;
	int						mRepeatColor;
	int						mRepeatAlpha;
	bool					mRandomGradientColor;
	bool					mUseNextColorKey;
	bool					mGetColorFromLayer;
	bool					mUpdateColorFromLayer;
	bool					mGetTransparencyFromLayer;
	bool					mUpdateTransparencyFromLayer;
	int						mNumberOfEachColor;
	bool					mLinkTransparencyToColor;
	bool					mUseKeyColorsOnly;
	bool					mUseEmitterAngleAndRange;
	bool					mAngleAlignToMotion;
	bool					mAngleKeepAlignedToMotion;
	bool					mAngleRandomAlign;
	int						mAngleAlignOffset;
	int						mAngleValue;
	int						mAngleRange;
	int						mAngleOffset;	

	bool					mCalcParticleTransformWantsBaseRotTrans;
	
	PIInterpolator			mColor;
	PIInterpolator			mAlpha;

	int						mDrawMode;	

public:
	float					GetValueAt(int theValueIdx, float theTime); // Frame number or (0.0 - 1.0) for "over life" values
};

typedef std::vector<PIParticleDef> PIPaticleDefVector;
typedef std::map<PIParticleDef*, int> PIParticleDefToIdMap;

class PIEmitter
{
public:
	enum
	{
		VALUE_F_LIFE,
		VALUE_F_NUMBER,
		VALUE_F_VELOCITY,		
		VALUE_F_WEIGHT,
		VALUE_F_SPIN,
		VALUE_F_MOTION_RAND,
		VALUE_F_BOUNCE,
		VALUE_F_ZOOM,		
		
		VALUE_LIFE,
		VALUE_NUMBER,
		VALUE_SIZE_X,
		VALUE_SIZE_Y,		
		VALUE_VELOCITY,
		VALUE_WEIGHT,
		VALUE_SPIN,
		VALUE_MOTION_RAND,
		VALUE_BOUNCE,
		VALUE_ZOOM,

		VALUE_VISIBILITY,
		VALUE_UNKNOWN3,
		VALUE_TINT_STRENGTH,
		VALUE_EMISSION_ANGLE,
		VALUE_EMISSION_RANGE,		
		
		VALUE_F_LIFE_VARIATION,
		VALUE_F_NUMBER_VARIATION, // Unused
		VALUE_F_SIZE_X_VARIATION,
		VALUE_F_SIZE_Y_VARIATION,
		VALUE_F_VELOCITY_VARIATION,
		VALUE_F_WEIGHT_VARIATION,
		VALUE_F_SPIN_VARIATION,
		VALUE_F_MOTION_RAND_VARIATION,
		VALUE_F_BOUNCE_VARIATION,
		VALUE_F_ZOOM_VARIATION,

		VALUE_F_NUMBER_OVER_LIFE,
		VALUE_F_SIZE_X_OVER_LIFE,
		VALUE_F_SIZE_Y_OVER_LIFE,
		VALUE_F_VELOCITY_OVER_LIFE,
		VALUE_F_WEIGHT_OVER_LIFE,
		VALUE_F_SPIN_OVER_LIFE,
		VALUE_F_MOTION_RAND_OVER_LIFE,
		VALUE_F_BOUNCE_OVER_LIFE,
		VALUE_F_ZOOM_OVER_LIFE,		

		NUM_VALUES
	};

public:
	std::string				mName;
	PIValue					mValues[NUM_VALUES];
	PIPaticleDefVector		mParticleDefVector;	
	bool					mKeepInOrder;
	bool					mOldestInFront; // only set if mKeepInOrder is set
	bool					mIsSuperEmitter;

	float					mCurWeight;
	float					mCurSpin;
	float					mCurMotionRand;

	//float					mCurSizeX;
	//float					mCurSizeY;
};

typedef std::vector<PIEmitter*> PIEmitterPtrVector;
typedef std::map<PIEmitter*, int> PIEmitterToIdMap;

typedef std::vector<std::string> StringVector;

class PIFreeEmitterInstance;

class PIParticleInstance
{
public:
	enum
	{
		VARIATION_MOTION_RAND,
		VARIATION_VELOCITY,
		VARIATION_WEIGHT,
		VARIATION_SPIN,				
		VARIATION_SIZE_X,
		VARIATION_SIZE_Y,						
		VARIATION_BOUNCE,
		VARIATION_LIFE,
		VARIATION_ZOOM,
		NUM_VARIATIONS
	};

public:	
	PIParticleInstance*		mNext;
	PIParticleDef*			mParticleDef;
	PIParticleDefInstance*	mParticleDefInstance;
	FPoint					mPos;
	FPoint					mVel;
	float					mImgAngle;
	int						mImgIdx;	
	int						mLifePctInt;
	int						mLifePctIntInc;	
	float					mVariationValues[NUM_VARIATIONS];		
	uint32					mColorMask;
	uint32					mColorOr;

	//float					mLifeValues[PIParticleDef::NUM_LIFEVALUES];	
	//float					mLifeValuesDelta[PIParticleDef::NUM_LIFEVALUES];	
	//int						mLifeValueActiveLife;
	//int						mLifeValueActiveLifeDelta;	
	
	float					mTicks;	
	float					mLife;
	float					mLifePct;
	float					mLifePctInc;
	int						mLifeValueDeltaIdx;
	PIEmitter*				mEmitterSrc;
	int						mNum;	
	PIParticleInstance*		mPrev;
	PIFreeEmitterInstance*	mParentFreeEmitter;	
	FPoint					mOrigPos;
	FPoint					mEmittedPos;
	FPoint					mLastEmitterPos;			
	float					mZoom;
	float					mSrcSizeXMult;
	float					mSrcSizeYMult;
	float					mGradientRand;
	float					mOrigEmitterAng;	
	int						mAnimFrameRand;

	SimpleMatrix			mTransform;	
	PITextureChunk*			mTextureChunk;
	
	float					mTransformScaleFactor; // Calculated	
	float					mThicknessHitVariation;				
	bool					mHasDrawn;
	ulong					mBkgColor;

	// Old...
	Image*					mImage;
	Rect					mSrcRect;

	static int				mCount;
	bool					mClip;

public:
	PIParticleInstance()
	{
		mPrev = NULL;
		mNext = NULL;

		mTransformScaleFactor = 1.0f;
		mImgIdx = 0;		
		mBkgColor = 0xFFFFFFFF;
		mSrcSizeXMult = 1.0f;
		mSrcSizeYMult = 1.0f;
		mParentFreeEmitter = NULL;
		mHasDrawn = false;

		mCount++;
	}

	~PIParticleInstance()
	{
		mCount--;
	}
};

typedef std::vector<PIParticleInstance*> PIPaticleInstanceVector;

class PIParticleDefInstance
{
public:
	float					mNumberAcc;
	float					mCurNumberVariation;
	int						mParticlesEmitted;
	int						mTicks;

	float					mCurWeight;
	float					mCurSpin;
	float					mCurMotionRand;
	int						mAlphaI;

public:
	PIParticleDefInstance()
	{
		Reset();
	}

	void Reset()
	{
		mNumberAcc = 0;
		mCurNumberVariation = 0;
		mParticlesEmitted = 0;
		mTicks = 0;
	}
};

typedef std::vector<PIParticleDefInstance> PIPaticleDefInstanceVector;

class PIParticleGroup
{
public:	
	PIParticleInstance*		mHead;
	PIParticleInstance*		mTail;
	int						mCount;
			
	bool					mIsSuperEmitter;
	bool					mWasEmitted;
	bool					mHasColorSampling;
	bool					mHasVelocityEffectors;
	bool					mHasAlignToMotion;
	bool					mHasIntense;
	bool					mHasPreserveColor;
	bool					mHasSingleParticles;
	bool					mHasAttachToEmitters;
	bool					mHasImageCycle;
	bool					mHasDeferredUpdate;

public:
	PIParticleGroup()
	{						
		mIsSuperEmitter = false;
		mWasEmitted = false;
		mHead = NULL;
		mTail = NULL;
		mCount = 0;
		mHasColorSampling = false;
		mHasVelocityEffectors = false;
		mHasAlignToMotion = false;
		mHasIntense = false;
		mHasPreserveColor = false;
		mHasSingleParticles = false;
		mHasAttachToEmitters = false;
		mHasImageCycle = false;
		mHasDeferredUpdate = false;		
	}
};

typedef std::vector<PIParticleGroup> PIParticleGroupVector;

class PIEmitterBase
{
public:
	PIPaticleDefInstanceVector mParticleDefInstanceVector;
	PIParticleGroup			mParticleGroup;
};

class PIFreeEmitterInstance : public PIParticleInstance
{
public:
	PIEmitterBase			mEmitter;	

public:
	PIFreeEmitterInstance()
	{
		mEmitter.mParticleGroup.mWasEmitted = true;
	}
};

typedef std::vector<PIFreeEmitterInstance> PIFreeEmitterInstanceVector;
//typedef std::map<PIFreeEmitterInstance*, int> PIFreeEmitterToIdMap;

class PIEmitterInstanceDef
{
public:
	enum
	{		
		VALUE_LIFE,
		VALUE_NUMBER,
		VALUE_SIZE_X,
		VALUE_VELOCITY,
		VALUE_WEIGHT,
		VALUE_SPIN,
		VALUE_MOTION_RAND,
		VALUE_BOUNCE,
		VALUE_ZOOM,

		VALUE_VISIBILITY, // verify
		VALUE_TINT_STRENGTH,
		VALUE_EMISSION_ANGLE,
		VALUE_EMISSION_RANGE,
		VALUE_ACTIVE,
		VALUE_ANGLE,

		VALUE_XRADIUS,
		VALUE_YRADIUS,
		VALUE_SIZE_Y,
		VALUE_UNKNOWN4,			

		NUM_VALUES
	};

	enum
	{
		GEOM_POINT,
		GEOM_LINE,
		GEOM_ECLIPSE,		
		GEOM_AREA,
		GEOM_CIRCLE
	};

public:
	std::string				mName;
	
	int						mFramesToPreload;
	int						mEmitterDefIdx;
	int						mEmitterGeom;
	bool					mEmitIn;
	bool					mEmitOut;
	int						mEmitAtPointsNum;
	int						mEmitAtPointsNum2; // Y for area	
	bool					mIsSuperEmitter;
	IntVector				mFreeEmitterIndices;	
	bool					mInvertMask;
	PIValue2D				mPosition;	
	PIValue					mValues[NUM_VALUES];
	PIValue2DVector			mPoints;		
	float					mCurAngle;
};

typedef std::vector<PIEmitterInstanceDef> PIEmitterInstanceDefVector;

class PIEmitterInstance : public PIEmitterBase
{
public:
	PIEmitterInstanceDef*	mEmitterInstanceDef;

	bool					mWasActive;
	bool					mWithinLifeFrame;
	PIPaticleDefInstanceVector mSuperEmitterParticleDefInstanceVector;
	PIParticleGroup			mSuperEmitterGroup;
	PIPaticleDefInstanceVector mParticleDefInstanceVector;
	PIParticleGroup			mParticleGroup;
	ulong					mTintColorI;
	SimpleMatrix			mTransformSimple;

	// User settings
	Color					mTintColor;
	ImagePtr				mMaskImage;
	SexyTransform2D			mTransform;
	FPoint					mOffset;
	float					mNumberScale;
	bool					mVisible;	

public:
	PIEmitterInstance()
	{		
		mWasActive = false;
		mWithinLifeFrame = true; // Assume that for now		
		mSuperEmitterGroup.mIsSuperEmitter = true;

		mTransform.LoadIdentity();
		mNumberScale = 1.0f;

		mVisible = true;
	}

	void SetVisible(bool isVisible)
	{
		mVisible = isVisible;
	}
};

typedef std::vector<PIEmitterInstance> PIEmitterInstanceVector;

class PIDeflector
{
public:
	std::string				mName;

	float					mBounce;
	float					mHits;
	float					mThickness;
	bool					mVisible;

	PIValue2D				mPos;
	PIValue					mActive;
	PIValue					mAngle;
	PIValue2DVector			mPoints;
	std::vector<FPoint>		mCurPoints;
};

typedef std::vector<PIDeflector> PIDeflectorVector;

class PIBlocker
{
public:
	std::string				mName;
	
	bool					mUseLayersBelowForBg;

	PIValue2D				mPos;
	PIValue					mActive;
	PIValue					mAngle;
	PIValue2DVector			mPoints;	
};

typedef std::vector<PIBlocker> PIBlockerVector;

class PIForce
{
public:
	std::string				mName;
	bool					mVisible;

	PIValue2D				mPos;
	PIValue					mStrength;
	PIValue					mDirection;
	PIValue					mActive;
	PIValue					mAngle;
	PIValue					mWidth;
	PIValue					mHeight;

	FPoint					mCurPoints[5];
};

typedef std::vector<PIForce> PIForceVector;

class PILayerDef
{
public:
	std::string				mName;	
	PIEmitterInstanceDefVector mEmitterInstanceDefVector;
	PIDeflectorVector		mDeflectorVector;
	PIBlockerVector			mBlockerVector;
	PIForceVector			mForceVector;
	PIValue2D				mOffset;
	FPoint					mOrigOffset;
	PIValue					mAngle;	
};

typedef std::vector<PILayerDef> PILayerDefVector;

class PILayer
{
public:
	PILayerDef*				mLayerDef;
	PIEmitterInstanceVector mEmitterInstanceVector;

	FPoint					mCurOffset;
	float					mCurAngle;	

	// User settings:
	bool					mVisible;
	Color					mColor;
	DeviceImage*			mBkgImage;
	Point					mBkgImgDrawOfs; // 0, 0 means you call Draw from upper left hand of image on screen
	SexyMatrix3				mBkgTransform; // To allow smaller (or larger) bkg images for color getting purposes...

public:
	PILayer()
	{
		mVisible = true;
		mColor = Color::White;
		mBkgImage = NULL;
		mBkgTransform.LoadIdentity();
		mEmitterInstanceVector.reserve(10);
	}

	void					SetVisible(bool isVisible);

	PIEmitterInstance*		GetEmitter(int theIdx = 0);
	PIEmitterInstance*		GetEmitter(const std::string& theName);
};

typedef std::vector<PILayer> PILayerVector;

#define PI_BUFSIZE 1024

class PIEffectDef
{
public:
	int						mRefCount;

	float					mCountScale;
	PIEmitterPtrVector		mEmitterVector;	
	PITextureVector			mTextureVector;
	PILayerDefVector		mLayerDefVector;	
	IntToIntMap				mEmitterRefMap;
	bool					mUsesAtlases;

public:
	PIEffectDef()
	{
		mCountScale = 1.0f;
		mRefCount = 1;
		mUsesAtlases = false;
	}

	~PIEffectDef()
	{
		for (int i = 0; i < (int) mEmitterVector.size(); i++)
			delete mEmitterVector[i];
		for (int i = 0; i < (int) mTextureVector.size(); i++)
			delete mTextureVector[i];
	}
};

namespace ResourceInfoTypes { class PIEffectRes; }

class PIEffect
: public BaseResource
{
public:
	RT_CLASS_DEFINE(PIEffect, BaseResource, ResourceClass);
	typedef ResourceInfoTypes::PIEffectRes InfoClass;

public:
	static float			mGlobalCountScale;
	static bool				mGlobalAllowPreserveColor;

	void*					mReadBuffer;
	unsigned long			mReadBufferLen;
	uint8*					mReadBufferDataPtr;
	FILE*					mWriteFP;
	int						mFileChecksum;
	bool					mIsPPF;
	bool					mAutoPadImages;
	int						mVersion;
	std::string				mSrcFileName;
	std::string				mDestFileName;
	MTRand					mRand;	
	Buffer					mStartupState;
	
	//uchar					mBuf[PI_BUFSIZE];
	int						mBufTemp;
	int						mBufPos;
	int						mChecksumPos;

	std::string				mNotes;	
	int						mFileIdx;
	StringVector			mStringVector;	

	int						mWidth;
	int						mHeight;
	Color					mBkgColor;
	int						mFramerate;
	int						mFirstFrameNum;
	int						mLastFrameNum;
	DeviceImage*			mThumbnail;
	StringToStringMap		mNotesParams;

	PIEffectDef*			mDef;	
	PILayerVector			mLayerVector;

	std::string				mError;
	bool					mLoaded;	

	///

	int						mUpdateCnt;
	float					mFrameNum;	
	bool					mIsNewFrame;	
	ObjectPool<PIParticleInstance> mParticlePool;
	ObjectPool<PIFreeEmitterInstance> mFreeEmitterPool;
	
	bool					mHasEmitterTransform;
	bool					mHasDrawTransform;
	bool					mDrawTransformSimple; // Scale and translate

	// Info
	int						mCurNumParticles;
	int						mCurNumEmitters;
	int						mLastDrawnPixelCount;

	/// User settings
	float					mAnimSpeed;
	Color					mColor;
	bool					mDebug;
	bool					mClip;	
	bool					mDrawBlockers;
	bool					mEmitAfterTimeline;
	IntVector				mRandSeeds;	
	bool					mWantsSRand;
	
	SexyTransform2D			mDrawTransform;
	SexyTransform2D			mEmitterTransform;

	float					mFrameTime;	

public:		
	bool					Fail(const std::string& theError);
	void					Deref();
	
	float					GetRandFloat();
	float					GetRandFloatU();
	float					GetRandSign();
	float					GetVariationScalar();
	float					GetVariationScalarU();

	std::string				ReadString();
	std::string				ReadStringS();
	bool					ExpectCmd(const std::string& theCmdExpected);
	void					ReadValue2D(PIValue2D* theValue2D);	
	void					ReadEPoint(PIValue2D* theValue2D);				
	void					ReadValue(PIValue* theValue);
	void					ReadEmitterType(PIEmitter* theEmitter);

	void					WriteByte(char theByte);
	void					WriteInt(int theInt);
	void					WriteShort(short theShort);
	void					WriteFloat(float theFloat);
	void					WriteBool(bool theValue);
	void					WriteString(const std::string& theString);
	void					WriteValue2D(PIValue2D* theValue2D);
	void					WriteEPoint(PIValue2D* theValue2D);
	void					WriteValue(PIValue* theValue);
	void					WriteEmitterType(PIEmitter* theEmitter);	

	void					SaveParticleDefInstance(Buffer& theBuffer, PIParticleDefInstance* theParticleDefInstance);
	void					SaveParticle(Buffer& theBuffer, PILayer* theLayer, PIParticleInstance* theParticle);
	
	void					LoadParticleDefInstance(const Buffer& theBuffer, PIParticleDefInstance* theParticleDefInstance);
	void					LoadParticle(const Buffer& theBuffer, PILayer* theLayer, PIParticleInstance* theParticle);

	FPoint					GetGeomPos(PIEmitterInstance* theEmitterInstance, PIParticleInstance* theParticleInstance, float* theTravelAngle = NULL, bool* isMaskedOut = NULL);
	FPoint					GetEmitterPos(PIEmitterInstance* theEmitterInstance, bool doTransform);	

	void					DetermineGroupFlags();
	int						CountParticles(PIParticleInstance* theStart);
	void					CalcParticleTransform(PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIEmitter* theEmitter, PIParticleDef* theParticleDef, PIParticleGroup* theParticleGroup, PIParticleInstance* theParticleInstance);
	void					CalcParticleTransformSimple(PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIEmitter* theEmitter, PIParticleDef* theParticleDef, PIParticleGroup* theParticleGroup, PIParticleInstance* theParticleInstance, float theScaleX, float theScaleY);
	void					UpdateParticleDef(PILayer* theLayer, PIEmitter* theEmitter, PIEmitterInstance* theEmitterInstance, PIParticleDef* theParticleDef, PIParticleDefInstance* theParticleDefInstance, PIParticleGroup* theParticleGroup, PIFreeEmitterInstance* theFreeEmitter);
	void					UpdateParticleGroupSuperEmitter(PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIParticleGroup* theParticleGroup);	
	void					UpdateParticleGroupWithSingleParticles(PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIParticleGroup* theParticleGroup);
	void					UpdateParticleGroup(PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIParticleGroup* theParticleGroup);
	void					DrawParticleGroupAccel(Graphics* g, PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIParticleGroup* theParticleGroup, bool isDarkeningPass);
	void					DrawParticleGroup(Graphics* g, PILayer* theLayer, PIEmitterInstance* theEmitterInstance, PIParticleGroup* theParticleGroup, bool isDarkeningPass);

public:	
	PIEffect();
	PIEffect(const PIEffect& rhs);
	~PIEffect();

	PIEffect*				Duplicate();
	
	virtual ImagePtr		GetImage(const std::string& theName, const std::string& theFilename);
	virtual void			SetImageOpts(DeviceImage* theImage);
	virtual std::string		WriteImage(const std::string& theName, int theIdx, DeviceImage* theImage, bool* hasPadding = NULL);

	bool					LoadEffect(const std::string& theFileName);		
	bool					SaveAsPPF(const std::string& theFileName, bool saveInitialState = true);

	bool					LoadState(const Buffer& theBuffer, bool shortened = false);
	bool					SaveState(Buffer& theBuffer, bool shortened = false);

	void					ResetAnim();
	void					Clear();
	PILayer*				GetLayer(int theIdx);	
	PILayer*				GetLayer(const std::string& theName);		
	bool					HasTimelineExpired();
	bool					IsActive();
	std::string				GetNotesParam(const std::string& theName, const std::string& theDefault = "");
	
	void					Update();
	void					DrawLayer(Graphics* g, PILayer* theLayer);
	void					Draw(Graphics* g);	

	// Doesn't actually use cache, this is just for skipping reloading for now
	bool					CheckCache();
	bool					SetCacheUpToDate();
	void					WriteToCache();
};

};

#endif //__PIREADER_H__
