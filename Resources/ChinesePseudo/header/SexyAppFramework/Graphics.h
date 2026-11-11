 #ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Common.h"
#include "Rect.h"
#include "Color.h"
#include "Image.h"
#include "Font.h"
#include "TriVertex.h"
#include "SexyCoords.h"
#include "SexyMatrix.h"
#include "MemPools.h"

namespace Sexy
{

	class RenderDevice;
	class RenderDevice3D;
	class RenderEffect;
	class RenderEffectDefinition;
	class Mesh;

	// CDH FIXME$$ for cleanliness this should probably be in its own header, but that's overkill for now
	class HRenderContext
	{
	private:
		union
		{
			uint32 mHandleDword;
			void* mHandlePtr;
		};

	public:
		inline HRenderContext(void* inHandlePtr = NULL) : mHandlePtr(inHandlePtr) {}
		inline HRenderContext(uint32 inHandleDword) : mHandlePtr(NULL) { mHandleDword = inHandleDword; }
		inline bool IsValid() const { return mHandlePtr != NULL; }

		inline uint32 GetDword() const { return mHandleDword; }
		inline void* GetPointer() const { return mHandlePtr; }

		inline bool operator == (const HRenderContext& inContext) const { return mHandlePtr == inContext.mHandlePtr; }
		inline bool operator != (const HRenderContext& inContext) const { return mHandlePtr != inContext.mHandlePtr; }
	};

class Font;
class SexyMatrix3;
class Transform;

const int MAX_TEMP_SPANS = 8192;

struct Edge
{
    double mX;
    double mDX;
    int i;
	double b;
};

class Graphics;
class Graphics3D;

typedef std::vector<Color> ColorVector;

class GraphicsState
{
public:
	static Image			mStaticImage;

	Image*					mDestImage;
	MATH_TYPE				mTransX;
	MATH_TYPE				mTransY;
	MATH_TYPE				mScaleX;
	MATH_TYPE				mScaleY;
	MATH_TYPE				mScaleOrigX;
	MATH_TYPE				mScaleOrigY;
	Rect					mClipRect;
	ColorVector				mPushedColorVector;
	Color					mFinalColor;
	Color					mColor;	
	Font*					mFont;
	int						mDrawMode;
	bool					mColorizeImages;
	bool					mFastStretch;
	bool					mWriteColoredString;
	bool					mLinearBlend;
	bool					mIs3D;

public:
	void					CopyStateFrom(const GraphicsState* theState);
	
	
	//This will be used by the graphics state list
	static SimpleMemPool	msGraphicsStatePoolAllocator;
};
	


typedef SimplePooledList<GraphicsState>::Type GraphicsStateList;

class Graphics : public GraphicsState
{
protected:
	RenderDevice*			mRenderDevice;
	HRenderContext			mRenderContext;
	Graphics3D*				mGraphics3D;
	static const Color		mDefaultImageColor;
	
public:	
	enum
	{
		DRAWMODE_NORMAL,
		DRAWMODE_ADDITIVE
	};

	Edge*					mPFActiveEdgeList;
	int						mPFNumActiveEdges;
	static const Point*		mPFPoints;
	int						mPFNumVertices;

	GraphicsStateList		mStateStack;

protected:	
	static int				PFCompareInd(const void* u, const void* v);
	static int				PFCompareActive(const void* u, const void* v);
	void					PFDelete(int i); 
	void					PFInsert(int i, int y);

	void					DrawImageTransformHelper(Image* theImage, const Transform &theTransform, const Rect &theSrcRect, float x, float y, bool useFloat);

	void					InitRenderInfo(const Graphics* theSourceGraphics);

	void					SetAsCurrentContext();
	inline void				CalcFinalColor();
	inline const Color&		GetImageColor();	

public:
	Graphics(Image* theDestImage = NULL);
	Graphics(const Graphics& theGraphics);
	virtual ~Graphics();	

	Graphics3D*				Get3D();
	RenderDevice*			GetRenderDevice() { return mRenderDevice; }
	HRenderContext			GetRenderContext() { return mRenderContext; }

	void					PushState();
	void					PopState();

	void					SetFont(Font* theFont);
	Font*					GetFont();

	void					SetColor(const Color& theColor);
	const Color&			GetColor();

	void					PushColorMult();
	void					PopColorMult();	
	
	inline const Color&		GetFinalColor()
	{
		if (mPushedColorVector.size() > 0)	
			return mFinalColor;			
		else	
			return mColor;					
	}
	
	void					SetDrawMode(int theDrawMode);
	int						GetDrawMode();
	
	void					SetColorizeImages(bool colorizeImages);
	bool					GetColorizeImages();

	void					SetFastStretch(bool fastStretch);
	bool					GetFastStretch();

	void					SetLinearBlend(bool linear); // for DrawImageMatrix, DrawImageTransform, etc...
	bool					GetLinearBlend();

	void					FillRect(int theX, int theY, int theWidth, int theHeight);
	void					FillRect(const Rect& theRect);
	void					DrawRect(int theX, int theY, int theWidth, int theHeight);	
	void					DrawRect(const Rect& theRect);
	void					ClearRect(int theX, int theY, int theWidth, int theHeight);	
	void					ClearRect(const Rect& theRect);
	
private:
	bool					DrawLineClipHelper(double* theStartX, double* theStartY, double *theEndX, double* theEndY);
public:
    

	void					DrawLine(float theStartX, float theStartY, float theEndX, float theEndY);
	void					DrawLineAA(float theStartX, float theStartY, float theEndX, float theEndY);
    
	void					PolyFill(const Point *theVertexList, int theNumVertices, bool convex = false);
	void					PolyFillAA(const Point *theVertexList, int theNumVertices, bool convex = false);

	void					DrawImage(Image* theImage, int theX, int theY);
	void					DrawImage(Image* theImage, int theX, int theY, const Rect& theSrcRect);
	void					DrawImage(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect);
	void					DrawImage(Image* theImage, int theX, int theY, int theStretchedWidth, int theStretchedHeight);
	void					DrawImageF(Image* theImage, float theX, float theY);
	void					DrawImageF(Image* theImage, float theX, float theY, const Rect& theSrcRect);

	void					DrawImageMirror(Image* theImage, int theX, int theY, bool mirror = true);
	void					DrawImageMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, bool mirror = true);
	void					DrawImageMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, bool mirror = true);
	
	void					DrawImageRotated(Image* theImage, int theX, int theY, double theRot, const Rect *theSrcRect = NULL);
	void					DrawImageRotated(Image* theImage, int theX, int theY, double theRot, int theRotCenterX, int theRotCenterY, const Rect *theSrcRect = NULL);
	void					DrawImageRotatedF(Image* theImage, float theX, float theY, double theRot, const Rect *theSrcRect = NULL);
	void					DrawImageRotatedF(Image* theImage, float theX, float theY, double theRot, float theRotCenterX, float theRotCenterY, const Rect *theSrcRect = NULL);
	void 					DrawImageRotatedAndStretched(Image* theImage, int theX, int theY, int theStretchedWidth, int theStretchedHeight, double theRot, float theRotCenterX, float theRotCenterY, const Rect *theSrcRect = NULL);

	void					DrawImageMatrix(Image* theImage, const SexyMatrix3 &theMatrix, float x = 0, float y = 0);
	void					DrawImageMatrix(Image* theImage, const SexyMatrix3 &theMatrix, const Rect &theSrcRect, float x = 0, float y = 0);
    void                    DrawImageMatrix2(Image* theImage, const SexyMatrix3 &theMatrix,const Rect &theSrcRect,const Color& color);
    void                    DrawImageMatrix2(Image* theImage, const SexyMatrix3 &theMatrix,const Rect &theSrcRect);
    void                    DrawImageMatrix2(Image* theImage, const SexyMatrix3 &theMatrix);
#if OPTIMIZE_ANIM_DRAW
	void					DrawImageMatrixOptimized(Image* theImage, const SexyMatrix3 &theMatrix, bool bNeedUpdateImage = true);
#endif

	void					DrawImageTransform(Image* theImage, const Transform &theTransform, float x = 0, float y = 0);
	void					DrawImageTransform(Image* theImage, const Transform &theTransform, const Rect &theSrcRect, float x = 0, float y = 0);
	void					DrawImageTransformF(Image* theImage, const Transform &theTransform, float x = 0, float y = 0);
	void					DrawImageTransformF(Image* theImage, const Transform &theTransform, const Rect &theSrcRect, float x = 0, float y = 0);
	void					DrawTriangleTex(Image *theTexture, const TriVertex &v1, const TriVertex &v2, const TriVertex &v3);
	
	void					DrawTrianglesTex(Image *theTexture, const TriVertex theVertices[][3], int theNumTriangles);
	void					DrawTrianglesTex(Image *theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, const Rect* theClipRect = NULL);
	void					DrawTrianglesTexStrip(Image* theTexture, const TriVertex theVertices[], int theNumTriangles);
	void					DrawTrianglesTexStrip(Image* theTexture, const TriVertex theVertices[], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true);

	void					DrawImageCel(Image* theImageStrip, int theX, int theY, int theCel);
	void					DrawImageCel(Image* theImageStrip, const Rect& theDestRect, int theCel);
	void					DrawImageCel(Image* theImageStrip, int theX, int theY, int theCelCol, int theCelRow);
	void					DrawImageCel(Image* theImageStrip, const Rect& theDestRect, int theCelCol, int theCelRow);

	void					ClearClipRect();
	void					SetClipRect(int theX, int theY, int theWidth, int theHeight);
	void					SetClipRect(const Rect& theRect);
	void					ClipRect(int theX, int theY, int theWidth, int theHeight);
	void					ClipRect(const Rect& theRect);
	void					Translate(int theTransX, int theTransY);
	void					TranslateF(float theTransX, float theTransY);

	// In progress: Only affects DrawImage
	void					SetScale(float theScaleX, float theScaleY, float theOrigX, float theOrigY);

	int						StringWidth(const SexyString& theString);
	void					DrawImageBox(const Rect& theDest, Image* theComponentImage);
	void					DrawImageBox(const Rect& theSrc, const Rect& theDest, Image* theComponentImage);

	void					DrawImageBoxStretch(const Rect& theDest, Image* theComponentImage);
	void					DrawImageBoxStretch(const Rect& theSrc, const Rect& theDest, Image* theComponentImage);

    void                    CopyIntoImage(Image* theTexture, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData);
    
	bool					Is3D() { return mIs3D; }

    static SimpleMemPool msPool;
	
	void *operator new( size_t size )
	{
		return msPool.GetMemory((uint32)size);
	} 
	
	void operator delete( void * addr)
	{
		msPool.ReturnMemory((uint8*)addr);
	}
    
    // Text Rendering Segment
    public:
#ifndef REMOVE_SEXYFONT
        void					DrawString(const SexyString& theString, int theX, int theY);
        int						WriteString(const SexyString& theString, int theX, int theY, int theWidth = -1, int theJustification = 0, bool drawString = true, int theOffset = 0, int theLength = -1, int theOldColor = -1);
        int						WriteWordWrapped(const Rect& theRect, const SexyString& theLine, int theLineSpacing = -1, int theJustification = -1, int *theMaxWidth = NULL, int theMaxChars = -1, int* theLastWidth = NULL, int *theLineCount=NULL, bool drawString = true);
        int						DrawStringColor(const SexyString& theString, int theX, int theY, int theOldColor = -1); //works like DrawString but can have color tags like ^ff0000^.
        int						DrawStringWordWrapped(const SexyString& theLine, int theX, int theY, int theWrapWidth = 10000000, int theLineSpacing = -1, int theJustification = -1, int *theMaxWidth = NULL); //works like DrawString but also word wraps
        int						GetWordWrappedHeight(int theWidth, const SexyString& theLine, int theLineSpacing = -1, int *theMaxWidth = NULL, int* theLineCount = NULL);
#endif
};

class GraphicsAutoState
{
public:
	Graphics*				mG;

public:
	
	GraphicsAutoState(Graphics* theG) : mG(theG)
	{
		mG->PushState();
	}

	~GraphicsAutoState()
	{
		mG->PopState();
	}
};

class Graphics3D
{
public:
	enum EBlendMode
	{
		// specific blend modes
		BLEND_ZERO				= 1,
		BLEND_ONE				= 2,
		BLEND_SRCCOLOR			= 3,
		BLEND_INVSRCCOLOR		= 4,
		BLEND_SRCALPHA			= 5,
		BLEND_INVSRCALPHA		= 6,
		//BLEND_DESTALPHA			= 7, // dest-alpha unsupported at this time
		//BLEND_INVDESTALPHA		= 8, // dest-alpha unsupported at this time
		BLEND_DESTCOLOR			= 9,
		BLEND_INVDESTCOLOR		= 10,
		BLEND_SRCALPHASAT		= 11,
		
		// default blend mode; use whatever is appropriate for the draw mode
		BLEND_DEFAULT			= 0xffff
	};

	enum ECompareFunc
	{
		COMPARE_NEVER		= 1,
		COMPARE_LESS		= 2,
		COMPARE_EQUAL		= 3,
		COMPARE_LESSEQUAL	= 4,
		COMPARE_GREATER		= 5,
		COMPARE_NOTEQUAL	= 6,
		COMPARE_GREATEREQUAL= 7,
		COMPARE_ALWAYS		= 8
	};

	enum ETexCoordGen
	{
		TEXCOORDGEN_NONE						= 0,
		TEXCOORDGEN_CAMERASPACENORMAL			= 1,
		TEXCOORDGEN_CAMERASPACEPOSITION			= 2,
		TEXCOORDGEN_CAMERASPACEREFLECTIONVECTOR	= 3,
	};

	enum EPrimitiveType
	{
		PT_PointList		= 1,
		PT_LineList			= 2,
		PT_LineStrip		= 3,
		PT_TriangleList		= 4,
		PT_TriangleStrip	= 5,
		PT_TriangleFan		= 6
	};

	enum EDrawPrimitiveFlags
	{
		DPF_NoAdjustUVs			= (1 << 0), // primitive has already had its UVs adjusted for atlasing; do not need to auto-adjust
		DPF_NoHalfPixelOffset	= (1 << 1), // primitive does not need pixel centering
		DPF_DiscardVerts		= (1 << 2), // although verts are const, they can be internally unconst-ed and overwritten instead of using temporary memory for adjustments
	};

	class LightColors
	{
	public:
		Color	mDiffuse;
		Color	mSpecular;
		Color	mAmbient;
		float	mAutoScale; // set this to the scale of your World transform, so the lights will be in sync

		LightColors()
		: mDiffuse(Color::White)
		, mSpecular(Color::Black)
		, mAmbient(Color::Black)
		, mAutoScale(1.f)
		{}
	};

	// mask mode
	enum EMaskMode
	{
		MASKMODE_NONE=0, // no masking (default behavior)
		MASKMODE_WRITE_MASKONLY, // mask write phase: write only to the mask layer; do not draw to color buffer
		MASKMODE_WRITE_MASKANDCOLOR, // mask write phase: write to the mask layer AND draw to color buffer
		MASKMODE_TEST_INSIDE, // mask test phase: only draw "inside" the mask (the area that has been written)
		MASKMODE_TEST_OUTSIDE // mask test phase: only draw "outside" the mask (the area that has not been written)
	};

	class Camera
	{
	protected:
		SexyCoords3 mCoords;
		float mZNear, mZFar;

	public:
		Camera()
		: mCoords()
		, mZNear(1.f)
		, mZFar(10000.f)
		{}

		inline SexyCoords3 GetCoords() const { return mCoords; }
		inline void SetCoords(const SexyCoords3& inCoords) { mCoords = inCoords; }

		inline float GetZNear() const { return mZNear; }
		inline float GetZFar() const { return mZFar; }

		void GetViewMatrix(SexyMatrix4* outM) const
		{
			if (!outM)
				return;
			SexyCoords3 tempCoords(mCoords);
			tempCoords.s.z = -tempCoords.s.z; // view matrix points into screen, not out, so z axis must be flipped
			tempCoords.GetInboundMatrix(outM);
		}

		virtual void GetProjectionMatrix(SexyMatrix4* outM) const = 0;
		virtual bool IsOrtho() const = 0;
		virtual bool IsPerspective() const = 0;

		virtual SexyVector3 EyeToScreen(const SexyVector3& inEyePos) const = 0;
		virtual SexyVector3 ScreenToEye(const SexyVector3& inScreenPos) const = 0;

		inline SexyVector3 WorldToEye(const SexyVector3& inWorldPos) const
		{
			return inWorldPos.Enter(mCoords);
		}
		inline SexyVector3 WorldToScreen(const SexyVector3& inWorldPos) const
		{
			return EyeToScreen(WorldToEye(inWorldPos));
		}
		inline SexyVector3 EyeToWorld(const SexyVector3& inEyePos) const
		{
			return inEyePos.Leave(mCoords);
		}
		inline SexyVector3 ScreenToWorld(const SexyVector3& inScreenPos) const
		{
			return EyeToWorld(ScreenToEye(inScreenPos));
		}

		inline bool LookAt(const SexyVector3& inTargetPos, const SexyVector3& inUpVector)
		{
			SexyCoords3 c = mCoords;
			if (!c.LookAt(inTargetPos, inUpVector))
				return false;
			SetCoords(c);
			return true;
		}
		inline bool LookAt(const SexyVector3& inViewPos, const SexyVector3& inTargetPos, const SexyVector3& inUpVector)
		{
			SexyCoords3 c = mCoords;
			if (!c.LookAt(inViewPos, inTargetPos, inUpVector))
				return false;
			SetCoords(c);
			return true;
		}
	};

	class PerspectiveCamera
	: public Camera
	{
	protected:
		SexyVector3 mProjS;
		float mProjT;

	public:
		PerspectiveCamera()
		: mProjS(0,0,0)
		, mProjT(0)
		{}
		PerspectiveCamera(float inFovDegrees, float inAspectRatio, float inZNear = 1.f, float inZFar = 10000.f)
		{
			Init(inFovDegrees, inAspectRatio, inZNear, inZFar);
		}

		void Init(float inFovDegrees, float inAspectRatio, float inZNear = 1.f, float inZFar = 10000.f)
		{
			float aAngleX = SexyMath::DegToRad(inFovDegrees * 0.5f);
			float aAngleY = aAngleX / inAspectRatio;

			mProjS.y = cosf(aAngleY) / sinf(aAngleY);
			mProjS.x = mProjS.y / inAspectRatio;
			mProjS.z = inZFar / (inZFar - inZNear);
			mProjT = -mProjS.z * inZNear;

			mZNear = inZNear;
			mZFar = inZFar;
		}

		void GetProjectionMatrix(SexyMatrix4* outM) const
		{
			if (!outM)
				return;
			
			memset(&outM->m00,0,16*sizeof(float));

			outM->m00 = mProjS.x;
			outM->m11 = mProjS.y;
			outM->m22 = mProjS.z;
			outM->m23 = 1.f;
			outM->m32 = mProjT;
		}

		bool IsOrtho() const { return false; }
		bool IsPerspective() const { return true; }

		SexyVector3 EyeToScreen(const SexyVector3& inEyePos) const
		{
			SexyVector3 aResult;
			float negZ = -inEyePos.z;
			aResult.x = inEyePos.x * mProjS.x / negZ;
			aResult.y = inEyePos.y * mProjS.y / negZ;
			aResult.z = (negZ * mProjS.z + mProjT) / mZFar;

			// bring x and y back into 0-1 range
			aResult.x = (aResult.x * 0.5f) + 0.5f;
			aResult.y = (aResult.y * -0.5f) + 0.5f;

			return aResult;
		}
		SexyVector3 ScreenToEye(const SexyVector3& inScreenPos) const
		{
			// change screenpos from 0-1 to -1-1
			float x = (inScreenPos.x - 0.5f) * 2.f;
			float y = (inScreenPos.y - 0.5f) * -2.f; // reverse y so it goes up (rather than down like in screenspace)

			// create eyespace line based on projection factors
			SexyVector3 start = SexyVector3(x*mZNear/mProjS.x, y*mZNear/mProjS.y, -mZNear);
			SexyVector3 end = SexyVector3(x*mZFar/mProjS.x, y*mZFar/mProjS.y, -mZFar);

			return start + (end-start)*inScreenPos.z;
		}	
	};

	class OffCenterPerspectiveCamera
	: public Camera
	{
	protected:
		SexyVector3 mProjS;
		float mProjT;
		float mLeft, mRight, mTop, mBottom;

	public:
		OffCenterPerspectiveCamera()
		: mProjS(0,0,0)
		, mProjT(0)
		{}
		OffCenterPerspectiveCamera(float inFovDegrees, float inAspectRatio, float inOffsetX, float inOffsetY, float inZNear = 1.f, float inZFar = 10000.f)
		{
			Init(inFovDegrees, inAspectRatio, inOffsetX, inOffsetY, inZNear, inZFar);
		}

		void Init(float inFovDegrees, float inAspectRatio, float inOffsetX, float inOffsetY, float inZNear = 1.f, float inZFar = 10000.f)
		{
			float aAngleX = SexyMath::DegToRad(inFovDegrees * 0.5f);
			float aAngleY = aAngleX / inAspectRatio;

			float aScaleY = cosf(aAngleY) / sinf(aAngleY);
			float aScaleX = aScaleY / inAspectRatio;

			float aHalfWidth = inZNear / aScaleX;
			float aHalfHeight = inZNear / aScaleY;

			mLeft = inOffsetX - aHalfWidth;
			mRight = inOffsetX + aHalfWidth;
			mTop = inOffsetY + aHalfHeight;
			mBottom = inOffsetY - aHalfHeight;

			mProjS.y = aScaleY;
			mProjS.x = aScaleX;
			mProjS.z = inZFar / (inZFar - inZNear);
			mProjT = -mProjS.z * inZNear;

			mZNear = inZNear;
			mZFar = inZFar;
		}

		void GetProjectionMatrix(SexyMatrix4* outM) const
		{
			if (!outM)
				return;
			
			memset(&outM->m00,0,16*sizeof(float));

			outM->m00 = mProjS.x;
			outM->m11 = mProjS.y;
			outM->m20 = (mLeft+mRight) / (mLeft-mRight);
			outM->m21 = (mBottom+mTop) / (mBottom-mTop);
			outM->m22 = mProjS.z;
			outM->m23 = 1.f;
			outM->m32 = mProjT;
		}

		bool IsOrtho() const { return false; }
		bool IsPerspective() const { return true; }

		SexyVector3 EyeToScreen(const SexyVector3& inEyePos) const
		{
			SexyVector3 aResult;
			float negZ = -inEyePos.z;
			aResult.x = inEyePos.x * mProjS.x / negZ;
			aResult.y = inEyePos.y * mProjS.y / negZ;
			aResult.z = (negZ * mProjS.z + mProjT) / mZFar;

			// bring x and y back into 0-1 range
			aResult.x = (aResult.x * 0.5f) + 0.5f;
			aResult.y = (aResult.y * -0.5f) + 0.5f;

			return aResult;
		}
		SexyVector3 ScreenToEye(const SexyVector3& inScreenPos) const
		{
			// change screenpos from 0-1 to -1-1
			float x = (inScreenPos.x - 0.5f) * 2.f;
			float y = (inScreenPos.y - 0.5f) * -2.f; // reverse y so it goes up (rather than down like in screenspace)

			// create eyespace line based on projection factors
			SexyVector3 start = SexyVector3(x*mZNear/mProjS.x, y*mZNear/mProjS.y, -mZNear);
			SexyVector3 end = SexyVector3(x*mZFar/mProjS.x, y*mZFar/mProjS.y, -mZFar);

			return start + (end-start)*inScreenPos.z;
		}	
	};

	class OrthoCamera
	: public Camera
	{
	protected:
		SexyVector3 mProjS;
		float mProjT;
		float mWidth, mHeight;

	public:
		OrthoCamera()
		: mProjS(0,0,0)
		, mProjT(0)
		, mWidth(0)
		, mHeight(0)
		{}
		OrthoCamera(float inWidth, float inHeight, float inZNear = 1.f, float inZFar = 10000.f)
		{
			Init(inWidth, inHeight, inZNear, inZFar);
		}

		void Init(float inWidth, float inHeight, float inZNear = 1.f, float inZFar = 10000.f)
		{
			mWidth = inWidth;
			mHeight = inHeight;

			mProjS.y = 2.0f / mHeight;
			mProjS.x = 2.0f / mWidth;
			mProjS.z = 1.0f / (inZFar - inZNear);
			mProjT = -mProjS.z * inZNear;

			mZNear = inZNear;
			mZFar = inZFar;
		}

		void GetProjectionMatrix(SexyMatrix4* outM) const
		{
			if (!outM)
				return;
			
			memset(&outM->m00,0,16*sizeof(float));

			outM->m00 = mProjS.x;
			outM->m11 = mProjS.y;
			outM->m22 = mProjS.z;
			outM->m32 = mProjT;
			outM->m33 = 1.f;
		}

		bool IsOrtho() const { return true; }
		bool IsPerspective() const { return false; }

		SexyVector3 EyeToScreen(const SexyVector3& inEyePos) const
		{
			SexyVector3 aResult;
			aResult.x = inEyePos.x * mProjS.x;
			aResult.y = inEyePos.y * mProjS.y;
			aResult.z = (mProjS.z + mProjT) / mZFar;

			// bring x and y back into 0-1 range
			aResult.x = (aResult.x * 0.5f) + 0.5f;
			aResult.y = (aResult.y * -0.5f) + 0.5f;
			
			return aResult;
		}
		SexyVector3 ScreenToEye(const SexyVector3& inScreenPos) const
		{
			// change screenpos from 0-1 to -1-1
			float x = (inScreenPos.x - 0.5f) * 2.f;
			float y = (inScreenPos.y - 0.5f) * -2.f; // reverse y so it goes up (rather than down like in screenspace)

			// create eyespace line based on projection factors
			SexyVector3 start = SexyVector3(x/mProjS.x, y/mProjS.y, -mZNear);
			SexyVector3 end = SexyVector3(start.x, start.y, -mZFar);
		
			return start + (end-start)*inScreenPos.z;
		}
	};

	class Spline
	{
	public:
		virtual SexyVector3 Evaluate(float inTime) const = 0;
	};

	/*
		CatmullRomSpline

		Catmull-Rom splines typically use 4 points, where 0 & 3 are outside and used for curvature definition,
		and 1 & 2 are the actual end points between Time=0.0 and Time=1.0.  Catmull-Rom splines have the property
		that the tangent at a point is parallel to the line segment between the point before and the point after.
		Hence points 0 & 3 are needed to define the tangents at points 1 & 2.

		The CatmullRomSpline class allows more than 4 points, and uses Time values beyond 1.0 to represent
		subsequent sections.  For example, in a 5-point spline, points 1 through 3 would define an interior
		between Time=0.0 and Time=2.0, with points 0 & 4 on the outside.  Values beyond the last Time value will
		wrap around to use the two exterior control points as actual points, and then restarting the spline; this
		can be used for looping behavior if desired.
	*/
	class CatmullRomSpline
	: public Spline
	{
	public:
		std::vector<SexyVector3> mPoints;

		CatmullRomSpline() {}
		CatmullRomSpline(const CatmullRomSpline& inSpline) : mPoints(inSpline.mPoints) {}
		CatmullRomSpline(const std::vector<SexyVector3>& inPoints) : mPoints(inPoints) {}

		SexyVector3 Evaluate(float inTime) const
		{
			uint32 aCount = (uint32)mPoints.size();

			uint32 aIntTime = (uint32)inTime;
			const SexyVector3* p[4];
			p[0] = &mPoints[(aIntTime - 1) % aCount];
			p[1] = &mPoints[aIntTime % aCount];
			p[2] = &mPoints[(aIntTime + 1) % aCount];
			p[3] = &mPoints[(aIntTime + 2) % aCount];

			float t = inTime - aIntTime;
			float t2 = t*t;
			float t3 = t2*t;

			/*
				Catmull-Rom solution:
				Q(t) = .5( p1(-t^3 + 2t^2 - t) + p2(3t^3 - 5t^2 + 2) + p3(-3t^3 + 4t^2 + t) + p4(t^3 - t^2))
			*/
			float aOpt[4];
			aOpt[0] = -t3 + 2.f*t2 - t;
			aOpt[1] = 3.f*t3 - 5.f*t2 + 2.f;
			aOpt[2] = -3.f*t3 + 4.f*t2 + t;
			aOpt[3] = t3 - t2;

			return((*p[0]*aOpt[0] + *p[1]*aOpt[1] + *p[2]*aOpt[2] + *p[3]*aOpt[3]) * 0.5f);
		}
	};

protected:
	Graphics*				mGraphics;
	RenderDevice3D*			mRenderDevice;
	HRenderContext			mRenderContext;

	friend class Graphics; // only Graphics objects should be constructing these
	Graphics3D(Graphics* inGraphics, RenderDevice3D* inRenderDevice, const HRenderContext& inRenderContext);

	void					SetAsCurrentContext();

public:
	Graphics* Get2D();
	RenderDevice3D* GetRenderDevice() { return mRenderDevice; }

	/*
		RenderDevice3D stub methods.

		Most of these methods are simple stubs that call down to the RenderDevice3D, after first setting
		our context as current (important, otherwise we might end up drawing in the wrong context and get
		some pretty messed-up results).

		Because the method signatures are mostly the same, you can refer to RenderDevice3D for more documentation.
	*/

	bool SupportsPixelShaders();
	bool SupportsVertexShaders();
	bool SupportsCubeMaps();
	bool SupportsVolumeMaps();
	bool SupportsImageRenderTargets();
	int GetMaxTextureStages();

	void AdjustVertexUVsEx(uint32 theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize);
	template<class T> void AdjustVertexUVs(SexyVertex* theVertices, int theVertexCount)
	{
		AdjustVertexUVsEx(T::FVF, theVertices, theVertexCount, sizeof(T));
	}

	void DrawPrimitiveEx(uint32 theVertexFormat, EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0);
	template<class T> void DrawPrimitive(EPrimitiveType thePrimitiveType, const T* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0)
	{
		DrawPrimitiveEx(T::FVF, thePrimitiveType, theVertices, thePrimitiveCount, theColor, theDrawMode, tx, ty, blend, theFlags);
	}

	void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true);

	void SetBltDepth(float inDepth);
	void PushTransform(const SexyMatrix3 &theTransform, bool concatenate = true);
	void PopTransform();
	void PopTransform(SexyMatrix3 &theTransform);

	void ClearColorBuffer(const Color& inColor = Color::Black);
	void ClearDepthBuffer();

	void SetDepthState(ECompareFunc inDepthTestFunc, bool inDepthWriteEnabled);
	void SetAlphaTest(ECompareFunc inAlphaTestFunc, int inRefAlpha);
	void SetColorWriteState(bool inWriteRedEnabled, bool inWriteGreenEnabled, bool inWriteBlueEnabled, bool inWriteAlphaEnabled);
	void SetWireframe(bool inWireframe);
	void SetBlend(EBlendMode inSrcBlend, EBlendMode inDestBlend);
	void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise);

	void SetLightingEnabled(bool inLightingEnabled, bool inSetDefaultMaterialState = true);
	void SetLightEnabled(int inLightIndex, bool inEnabled);
	void SetPointLight(int inLightIndex, const SexyVector3& inPos, const LightColors& inColors, float inRange, const SexyVector3& inAttenuation);
	void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const LightColors& inColors);
	void SetGlobalAmbient(const Color& inColor);
	void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1);
	void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1);
	void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f);
	void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1);

	void SetWorldTransform(const SexyMatrix4* inMatrix);
	void SetViewTransform(const SexyMatrix4* inMatrix);
	void SetProjectionTransform(const SexyMatrix4* inMatrix);
	void SetTextureTransform(int inTextureIndex, const SexyMatrix4* inMatrix, int inNumDimensions = 2);

	bool SetTexture(int inTextureIndex, Image* inImage);
	void SetTextureWrap(int inTextureIndex, bool inWrap = true);
	void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV);
	void SetTextureLinearFilter(int inTextureIndex, bool inLinear = true);
	void SetTextureCoordSource(int inTextureIndex, int inUVComponent, ETexCoordGen inTexGen = TEXCOORDGEN_NONE);
	void SetTextureFactor(int inTextureFactor);

	void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ = 0.0f, float theMaxZ = 1.0f);

	RenderEffect* GetEffect(RenderEffectDefinition* inDefinition);

	/*
		Convenience method to set up the combined 3D transform state (world/view/projection transforms)
		from a SexyCoords3 (world transform) and Graphics3D::Camera (view/projection).
	*/
	void Set3DTransformState(const SexyCoords3& inWorldCoords, const Camera& inCamera)
	{
		SexyMatrix4 aMat;
		inWorldCoords.GetOutboundMatrix(&aMat);
		SetWorldTransform(&aMat);
		inCamera.GetViewMatrix(&aMat);
		SetViewTransform(&aMat);
		inCamera.GetProjectionMatrix(&aMat);
		SetProjectionTransform(&aMat);
	}

	/*
		Set masking mode.  The write/test modes are described with their respective enums.
		The inAlphaRef value is the alpha reference above which the mask is written to (the
		default is zero).  The inFrontDepth and inBackDepth values are used when drawing,
		depending on which layer is being written to.
	*/
	void SetMasking(EMaskMode inMaskMode, int inAlphaRef = 0, float inFrontDepth = 0.25f, float inBackDepth = 0.5f);
	
	/*
		Clear the mask layer back to default values.  This is currently the same
		as ClearDepthBuffer, but we're keeping it as a separate method for clarification
		of intent or incase we later change the way masking is done internally, etc.
	*/
	void ClearMask();
	
	
	static SimpleMemPool msPool;
	void *operator new( size_t size )
	{
		return msPool.GetMemory((uint32)size);
	} 
	
	void operator delete( void * addr)
	{
		msPool.ReturnMemory((uint8*)addr);
	}
};

}

#endif //__GRAPHICS_H__
