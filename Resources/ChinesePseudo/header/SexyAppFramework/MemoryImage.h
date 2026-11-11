#ifndef __MEMORYIMAGE_H__
#define __MEMORYIMAGE_H__

#include "Image.h"
#include "RenderDevice.h"

#define OPTIMIZE_SOFTWARE_DRAWING
#ifdef OPTIMIZE_SOFTWARE_DRAWING
extern bool gOptimizeSoftwareDrawing;
#endif

namespace Sexy
{

const auto MEMORYCHECK_ID = 0x4BEEFADE;

class NativeDisplay;
class SexyAppBase;

class MemoryImage : public Image, public RenderDevice
{
public:
	RT_CLASS_DEFINE(MemoryImage, Image, ResourceClass) {}

public:
	/*
		TriRep
		
		Class representing the image broken up into smaller UV tris, skipping over blocks of pixels
		that have no effect, such as alpha-zero pixels for normal drawing, or color-zero pixels
		for additive drawing.

		This is entirely used as an optimization to reduce overdraw in fillrate-bound situations;
		the intention is based on the idea that the additional CPU/GPU cost of submitting additional
		tris will in many cases be significantly cheaper than the cost of so many otherwise-unused
		pixels passing through the pixel pipeline.
		
		Given that our games are mostly 2D, heavily layered and chock full of alpha blending, overdraw
		tends to be one of the most significant GPU expenses we incur, so this improvement can often be
		quite significant.
	*/
	class TriRep
	{
	public:
		// individual tri, represented as UVs within the image
		struct Tri
		{
			struct Point
			{
				float u, v;
			};
			
			union
			{
				struct
				{
					Point p0, p1, p2;
				} s;
				Point p[3];
			};

			//uint32 mDebugColor;
			
			Tri() {}
			Tri(float inU0, float inV0, float inU1, float inV1, float inU2, float inV2)//, uint32 inDebugColor = 0xffffffff)
			//: mDebugColor(inDebugColor)
			{
				s.p0.u = inU0; s.p0.v = inV0;
				s.p1.u = inU1; s.p1.v = inV1;
				s.p2.u = inU2; s.p2.v = inV2;
			}
		};

		// one mipmap-style level of tris, at a given resolution
		class Level
		{
		public:
			class Region
			{
			public:
				Rect mRect;
				std::vector<Tri> mTris;
			};

			int mDetailX, mDetailY;
			int mRegionWidth, mRegionHeight;
			std::vector<Region> mRegions;

			void GetRegionTris(std::vector<Tri>& outTris, MemoryImage* inImage, const Rect& inSrcRect, bool inAllowRotation);
			
			MemoryImage::TriRep::Tri* GetRegionTrisPtr(int& outTriCount, MemoryImage* inImage, const Rect& inSrcRect, bool inAllowRotation);
		};

		// all levels in the tri representation
		std::vector<Level> mLevels;

		// get accessors for various useful levels
		Level* GetMinLevel() { return mLevels.empty() ? NULL : &mLevels.front(); }
		Level* GetMaxLevel() { return mLevels.empty() ? NULL : &mLevels.back(); }
		Level* GetLevelForScreenSpaceUsage(float inUsageFrac, bool inAllowRotation);
	};

	uint32*					mBits;
	int						mBitsChangedCount;

	uint32*					mColorTable;	
	uchar*					mColorIndices;
	
	bool					mForcedMode;
	bool					mHasTrans;
	bool					mHasAlpha;
	bool					mIsVolatile;
	bool					mPurgeBits;
	bool					mWantPal;
	bool					mDither16;
	
	uint32*					mNativeAlphaData;
	uchar*					mRLAlphaData;
	uchar*					mRLAdditiveData;	

	bool					mBitsChanged;
	SexyAppBase*			mApp;

	// tri representations for normal and additive drawing, respectively
	TriRep					mNormalTriRep;
	TriRep					mAdditiveTriRep;
	
private:
	void					Init();

public:
	virtual void*			GetNativeAlphaData(NativeDisplay *theNative);
	virtual uchar*			GetRLAlphaData();
	virtual uchar*			GetRLAdditiveData(NativeDisplay *theNative);
	virtual void			PurgeBits();
	virtual void			DeleteSWBuffers();
	virtual void			Delete3DBuffers();	
	virtual void			DeleteExtraBuffers();
	virtual void			ReInit();

	virtual void			BitsChanged();
	virtual void			CommitBits();
	
	virtual void			DeleteNativeData();	
    
	void					NormalBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
	void					AdditiveBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);

	void					NormalDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
	void					AdditiveDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);

	void					NormalDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
	void					AdditiveDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);

	void					SlowStretchBlt(Image* theImage, const Rect& theDestRect, const FRect& theSrcRect, const Color& theColor, int theDrawMode);
	void					FastStretchBlt(Image* theImage, const Rect& theDestRect, const FRect& theSrcRect, const Color& theColor, int theDrawMode);
	bool					BltRotatedClipHelper(float &theX, float &theY, const Rect &theSrcRect, const Rect &theClipRect, double theRot, FRect &theDestRect, float theRotCenterX, float theRotCenterY);
	bool					StretchBltClipHelper(const Rect &theSrcRect, const Rect &theClipRect, const Rect &theDestRect, FRect &theSrcRectOut, Rect &theDestRectOut);
	bool					StretchBltMirrorClipHelper(const Rect &theSrcRect, const Rect &theClipRect, const Rect &theDestRect, FRect &theSrcRectOut, Rect &theDestRectOut);
	void					BltMatrixHelper(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, void *theSurface, int theBytePitch, int thePixelFormat, bool blend);
	void					BltTrianglesTexHelper(Image *theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect &theClipRect, const Color &theColor, int theDrawMode, void *theSurface, int theBytePitch, int thePixelFormat, float tx, float ty, bool blend);

	void					FillScanLinesWithCoverage(RenderDevice::Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const uint8* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight) override;


public:
	MemoryImage();
	MemoryImage(SexyAppBase* theApp);
	MemoryImage(const MemoryImage& theMemoryImage);	
	virtual ~MemoryImage();

	virtual MemoryImage*	AsMemoryImage() override { return this; }

	virtual void			Clear();
	virtual void			SetBits(uint32* theBits, int theWidth, int theHeight, bool commitBits = true);
	virtual void			Create(int theWidth, int theHeight);
	virtual uint32*			GetBits(int i_x = 0, int i_y = 0, int i_width = 0, int i_height = 0);
	
	virtual void			FillRect(const Rect& theRect, const Color& theColor, int theDrawMode) override;
	virtual void			ClearRect(const Rect& theRect) override;
	virtual void			DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode, bool antiAlias = false) override;
    virtual void BltMatrix2(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend,bool center) override;
	virtual void			Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override;
	virtual void			BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode) override;
	virtual void			BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY) override;
	virtual void			BltStretched(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror = false) override;
	virtual void			BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend) override;
	virtual void			BltTriangles(Image* theImage, const TriVertex theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, const Rect* theClipRect = NULL) override;
	virtual void 			BltStretchedAndRotated(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, bool fastStretch, bool mirror = false) override {}

	virtual void			SetImageMode(bool hasTrans, bool hasAlpha);
	virtual void			SetVolatile(bool isVolatile);	

	virtual bool			Palletize();

	virtual bool			BuildTriRep(TriRep* inTriRep, bool inAdditive, bool inForceRebuild = false);
	virtual bool			BuildTriReps(bool inForceRebuild = false);

	// additional RenderDevice implementation methods

	virtual RenderDevice3D* Get3D() override { return NULL; }
	virtual bool CanFillPoly() override { return false; }

	// MemoryImage doesn't use render contexts or a state stack, as it has no internal state to manage (except the dest image, which is implied)
	virtual HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext = HRenderContext((void*)0)) override { return HRenderContext(1); }
	virtual void DeleteContext(const HRenderContext& theContext) override {}
	virtual void SetCurrentContext(const HRenderContext& theContext) override {}
	virtual HRenderContext GetCurrentContext() const override { return HRenderContext(1); }

	virtual void PushState() override {}
	virtual void PopState() override {}

	virtual void FillPoly(const Point theVertices[], int theNumVertices, const Rect *theClipRect, const Color &theColor, int theDrawMode, int tx, int ty) override {}
	virtual void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override {}
    
    virtual void CopyIntoImage(Image* theTexture, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData) override {}
};

}

#endif //__MEMORYIMAGE_H__
