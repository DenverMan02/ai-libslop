#ifndef __D3DINTERFACE_H__
#define __D3DINTERFACE_H__

#define NOMINMAX
#include <ddraw.h>
#include "Common.h"
#include "Rect.h"
#include "Color.h"
#include "SexyMatrix.h"
#include "DeviceStateConstants.h"
#include "MemoryImage.h"
#include "DeviceImage.h"
#include "SharedImage.h"
#include "TriVertex.h"
#include "RenderDevice.h"
#include "IGraphicsDriver.h"
#include "Mesh.h"
#include <assert.h>

namespace Sexy
{

class DeviceImage;
class SexyMatrix3;
class SexyVertex;
class SexyVertex2D;
class SexyVertex3D;
class Image;
class MemoryImage;
class IDXSurface;
class Graphics;
class D3DStateManager;
class D3DRenderEffectDefInfo;
class D3DRenderEffect;
class WindowsGraphicsDriver;
class D3DInterface;

typedef struct _D3DTLVERTEX
{
	FLOAT    sx, sy, sz, rhw;
	D3DCOLOR color, specular;
	FLOAT    tu, tv;
} D3DTLVERTEX, *LPD3DTLVERTEX;

struct D3DVertexList;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct D3DTextureDataPiece
{
	IUnknown* mTexture; // for normal textures (null for cubemaps/volumemaps)
	IUnknown* mCubeTexture; // for cubemap textures (null for normal textures/volumemaps)
	IUnknown* mVolumeTexture; // for volumemap textures (null for normal textures/cubemaps)
	int mWidth;
	int mHeight;
};

class D3DTextureData
{
public:
	typedef std::vector<D3DTextureDataPiece> TextureVector;

	D3DInterface* mInterface;

	TextureVector mTextures;
	int mPaletteIndex;
	
	int mWidth, mHeight;
	int mTexVecWidth, mTexVecHeight;
	int mTexPieceWidth, mTexPieceHeight;
	int mBitsChangedCount;
	int mTexMemSize;
	int mTexMemOriginalSize;
	ulong mTexMemFlushRevision;
	float mMaxTotalU, mMaxTotalV;
	PixelFormat mPixelFormat;
	ulong mImageFlags;
	bool mFromRSB;
	bool mOptimizedLoad;

	D3DTextureData(D3DInterface* theInterface);
	~D3DTextureData();

	void ReleaseTextures();

	void CreateTextureDimensions(MemoryImage *theImage);
	void CreateTextures(MemoryImage *theImage, D3DInterface* theInterface);
	void CheckCreateTextures(MemoryImage *theImage, D3DInterface* theInterface);
	IUnknown* GetTexture(MemoryImage* theOrigImage, int x, int y, int &width, int &height, float &u1, float &v1, float &u2, float &v2);
	IUnknown* GetTextureF(float x, float y, float &width, float &height, float &u1, float &v1, float &u2, float &v2);
	IUnknown* GetCubeTexture();
	IUnknown* GetVolumeTexture();

	void Blt(D3DInterface* theInterface, MemoryImage* theImage, int theDrawMode, float theX, float theY, const Rect& theSrcRect, const Color& theColor);
	void BltTransformed(D3DInterface* theInterface, MemoryImage* theImage, int theDrawMode, const SexyMatrix3 &theTrans, const Rect& theSrcRect, const Color& theColor, const Rect *theClipRect = NULL, float theX = 0, float theY = 0, bool center = false);
	void BltTriangles(D3DInterface* theInterface, MemoryImage* theImage, const TriVertex theVertices[][3], int theNumTriangles, DWORD theColor, float tx = 0, float ty = 0, const Rect* theClipRect = NULL);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class D3DMeshPiece : public MeshPiece
{
public:
	DWORD					mSexyVF;
	int						mVertexSize;
	int						mVertexBufferCount;
	int						mIndexBufferCount;
	void*					mVertexData;
	void*					mIndexData;

	IUnknown* mVertexBuffer;
	IUnknown* mIndexBuffer;

public:
	D3DMeshPiece();
	virtual ~D3DMeshPiece();
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class D3DDynamicVertexBuffer
{
protected:
	IUnknown* mVB;
	ulong mVertCount;
	ulong mVertLimit;

public:
	D3DDynamicVertexBuffer(ulong inVertLimit);
	virtual ~D3DDynamicVertexBuffer();

	bool InitBuffer(D3DInterface* inInterface);
	void CleanupBuffer();

	inline ulong GetVertLimit() { return mVertLimit; }
	int Write(D3DInterface* inInterface, ulong inVertCount, const void* inVerts);
	
	void ApplyToDevice(D3DInterface* inInterface, ulong inStreamIndex);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class D3DInterface
	: public RenderDevice3D
{
public:
	friend class D3DRenderEffect;
	friend class D3DTextureData;

	enum
	{
		DEFAULT_VERTEX_FVF = 0x1C4, // D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1
		DEFAULT_VERTEX_SIZE = 32,
		
		MAX_TEXTURE_SIZE = 4096
	};

	typedef std::list<SexyMatrix3> TransformStack;
	typedef std::set<MemoryImage*> ImageSet;
	typedef std::vector<int> IntVector;

	static std::string sErrorString;
	static int sMinTextureWidth;
	static int sMinTextureHeight;
	static int sMaxTextureWidth;
	static int sMaxTextureHeight;
	static int sMaxTextureAspectRatio;
	static DWORD sSupportedTextureFormats;
	static DWORD sSupportedScreenFormats;
	static bool sTextureSizeMustBePow2;
	static bool sCanStretchRectFromTextures;

	TransformStack mTransformStack;	
	FBltFilter				mBltFilter;
	void*					mBltFilterContext;
	FDrawPrimFilter			mDrawPrimFilter;
	void*					mDrawPrimFilterContext;

	HRenderContext			mCurrentContext;

	typedef std::map<RenderEffectDefinition*, D3DRenderEffectDefInfo*> RenderEffectDefInfoMap;
	RenderEffectDefInfoMap	mRenderEffectDefInfo;
	typedef std::map<RenderEffectDefinition*, D3DRenderEffect*> RenderEffectMap;
	RenderEffectMap			mRenderEffects;

	D3DStateManager*		mStateMgr;

	HWND					mHWnd;
	int						mWidth;
	int						mHeight;
	int						mFullscreenBits;	
	float					mFov;
	float					mNearPlane;
	float					mFarPlane;	

	SEXY3DFORMAT			mDisplayFormat;

	bool					mSceneBegun;
	bool					mIsWindowed;
	bool					mNeedClearZBuffer;
	bool					mNeedEvictManagedResources;

	D3DDynamicVertexBuffer* mDynVB;

	IUnknown*				mBackBufferSurface;
	IUnknown*				mTempRenderTargetSurface;
	IUnknown*				mCurRenderTargetSurface;
	Image*					mCurRenderTargetImage;

	ImageSet				mImageSet;

	IntVector				mAvailPalettes;
	
	std::string				mAdapterInfoString;
	std::string				mD3DProductVersionString;

	ulong					mTexMemUsageBytesAlloced;
	ulong					mTexMemUsageBytesOriginal;
	ulong					mTexMemUsageBytesCurFrame;
	ulong					mTexMemUsageFlushRevision;

	D3DTLVERTEX*			mBatchedTriangleBuffer;
	ulong					mBatchedTriangleIndex;
	ulong					mBatchedTriangleSize;

	WindowsGraphicsDriver*	mGraphicsDriver;

	struct
	{
		ulong				mCalls;
		ulong				mPrims;
	}						mDrawPrimMtx;

	D3DInterface();
	virtual ~D3DInterface();

	virtual bool			InitFromGraphicsDriver(WindowsGraphicsDriver *theDriver, IGraphicsDriver::EResult* outErrorResult, bool preTestOnly, bool* outIsRecommended = NULL) = 0;

	/*
		RenderDevice implementation...
	*/
	virtual RenderDevice3D* Get3D() override { return this; }
	virtual bool CanFillPoly() override { return true; }

	virtual HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext = HRenderContext((void*)0)) override;
	virtual void DeleteContext(const HRenderContext& theContext) override;
	virtual void SetCurrentContext(const HRenderContext& theContext) override;
	virtual HRenderContext GetCurrentContext() const override;

	virtual void PushState() override;
	virtual void PopState() override;

	virtual void ClearRect(const Rect& theRect) override;
	virtual void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode) override;
	virtual void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight) override
	{
		int l = theSpans[0].mX, t = theSpans[0].mY;
		int r = l + theSpans[0].mWidth, b = t;
		for (int i = 1; i < theSpanCount; ++i)
		{
			l = min(theSpans[i].mX, l);
			r = max(theSpans[i].mX + theSpans[i].mWidth - 1, r);
			t = min(theSpans[i].mY, t);
			b = max(theSpans[i].mY, b);
		}
		for (int i = 0; i < theSpanCount; ++i)
		{
			theSpans[i].mX -= l;
			theSpans[i].mY -= t;
		}

		MemoryImage aTempImage;
		aTempImage.Create(r-l+1, b-t+1);
		aTempImage.FillScanLinesWithCoverage(theSpans, theSpanCount, theColor, theDrawMode, theCoverage, theCoverX - l, theCoverY - t, theCoverWidth, theCoverHeight);
		Blt(&aTempImage, l, t, Rect(0, 0, r-l+1, b-t+1), Color::White, theDrawMode);
	}
	virtual void FillPoly(const Point theVertices[], int theNumVertices, const Rect *theClipRect, const Color &theColor, int theDrawMode, int tx, int ty) override;
	virtual void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode, bool antiAlias = false) override;
	virtual void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override
	{
		BltNoClipF(theImage, (float)theX, (float)theY, theSrcRect, theColor, theDrawMode);
	}
	virtual void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode) override
	{
		FRect aClipRect((float)theClipRect.mX,(float)theClipRect.mY,(float)theClipRect.mWidth,(float)theClipRect.mHeight);
		FRect aDestRect((float)theX,(float)theY,(float)theSrcRect.mWidth,(float)theSrcRect.mHeight);

		FRect anIntersect = aDestRect.Intersection(aClipRect);
		if (anIntersect.mWidth!=aDestRect.mWidth || anIntersect.mHeight!=aDestRect.mHeight)
		{
			if (anIntersect.mWidth!=0 && anIntersect.mHeight!=0)
				BltClipF(theImage,theX,theY,theSrcRect,&theClipRect,theColor,theDrawMode);
		}
		else
			BltNoClipF(theImage,theX,theY,theSrcRect,theColor,theDrawMode,true);
	}
	virtual void BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY) override
	{
		SexyTransform2D aTransform;

		aTransform.Translate(-theRotCenterX, -theRotCenterY);
		aTransform.RotateRad((float)theRot);
		aTransform.Translate(theX+theRotCenterX,theY+theRotCenterY);

		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,true);
	}
	void BltMatrix2(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend, bool center)
	{
		BltTransformed(theImage, &theClipRect, theColor, theDrawMode, theSrcRect, theMatrix, blend, x, y, center);
	}
	virtual void BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend) override
	{
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,theMatrix,blend,x,y,true);
	}
	virtual void BltTriangles(Image* theImage, const SexyVertex2D theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, const Rect* theClipRect = NULL) override;
	virtual void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override
	{
		SexyTransform2D aTransform;		

		aTransform.Translate(-(float)theSrcRect.mWidth,0);
		aTransform.Scale(-1, 1);
		aTransform.Translate((float)theX, (float)theY);

		BltTransformed(theImage,NULL,theColor,theDrawMode,theSrcRect,aTransform,false);
	}
	virtual void BltStretched(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color &theColor, int theDrawMode, bool fastStretch, bool mirror = false) override
	{
		float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
		float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;

		SexyTransform2D aTransform;
		if (mirror)
		{
			aTransform.Translate(-(float)theSrcRect.mWidth,0);
			aTransform.Scale(-xScale, yScale);
		}
		else
			aTransform.Scale(xScale, yScale);

		aTransform.Translate((float)theDestRect.mX, (float)theDestRect.mY);
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,!fastStretch);
	}

	void BltStretchedSpecial(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirrorX, bool mirrorY)
	{
		float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
		float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;

		SexyTransform2D aTransform;
		if (mirrorX)
		{
			aTransform.Translate(-(float)theSrcRect.mWidth,0);
			aTransform.Scale(-xScale, yScale);
		}
		if (mirrorY)
		{
			aTransform.Translate(0,-(float)theSrcRect.mHeight);
			aTransform.Scale(xScale, -yScale);
		}

		if (!mirrorX && !mirrorY)
			aTransform.Scale(xScale, yScale);

		aTransform.Translate((float)theDestRect.mX, (float)theDestRect.mY);
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,!fastStretch);
	}

	//PVZ2_CHINESE_BEGIN
	//empty implementation
	void CopyIntoImage(Image* theTexture, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData)
	{
		
	}
	//PVZ2_CHINESE_END

	/*
		...RenderDevice implementation
	*/

	/*
		RenderDevice3D implementation... (remaining unimplemented methods are implemented in D3D 8/9 subclasses)
	*/
	virtual void Cleanup();
	
	virtual bool SceneBegun() override;

	virtual bool CreateImageRenderData(MemoryImage* inImage) override;
	virtual void RemoveImageRenderData(MemoryImage* inImage) override;
	virtual bool RecoverImageBitsFromRenderData(MemoryImage* inImage) override;
	virtual int GetTextureMemorySize(MemoryImage* theImage) override;
	virtual PixelFormat GetTextureFormat(MemoryImage* theImage) override;

	virtual IUnknown* GetBackBufferSurface();
	virtual bool SetRenderTargetSurface(IUnknown* inSurface);
	virtual bool SetRenderTarget(Image* theRenderTarget);
	
	virtual Image*	SwapScreenImage(DeviceImage*& ioSrcImage, IUnknown*& ioSrcSurface, uint32 flags);
	virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags) {};

	// Create a surface with the given characteristics
	virtual IUnknown* CreateSurface(int inWidth, int inHeight, bool inRenderTarget, bool inTexture) = 0;

	// Blit a surface to the current render target, if supported (CanBltSurface indicates support for this feature)
	virtual bool CanBltSurface(bool srcSurfaceIsTexture) = 0;
	virtual void BltSurface(IUnknown* theSurface, const Rect& theDest, const Rect& theSrc) = 0;

	virtual void AdjustVertexUVsEx(ulong theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize) override;
	virtual void DrawPrimitiveEx(ulong theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0) override;

	virtual void SetBltDepth(float inDepth) override;
	virtual void PushTransform(const SexyMatrix3 &theTransform, bool concatenate = true) override;
	virtual void PopTransform() override;
	virtual void PopTransform(SexyMatrix3 &theTransform) override;

	virtual void SetDepthState(Graphics3D::ECompareFunc inDepthTestFunc, bool inDepthWriteEnabled) override
	{
		SetRenderState(SEXY3DRS_ZENABLE, inDepthWriteEnabled || (inDepthTestFunc != Graphics3D::COMPARE_ALWAYS));
		SetRenderState(SEXY3DRS_ZWRITEENABLE, inDepthWriteEnabled);
		SetRenderState(SEXY3DRS_ZFUNC, inDepthTestFunc);
	}
	virtual void SetAlphaTest(Graphics3D::ECompareFunc inAlphaTestFunc, int inRefAlpha) override
	{
		SetRenderState(SEXY3DRS_ALPHATESTENABLE, (inAlphaTestFunc != Graphics3D::COMPARE_ALWAYS));
		SetRenderState(SEXY3DRS_ALPHAFUNC, inAlphaTestFunc);
		SetRenderState(SEXY3DRS_ALPHAREF, inRefAlpha);
	}
	virtual void SetColorWriteState(bool inWriteRedEnabled,bool inWriteGreenEnabled,bool inWriteBlueEnabled,bool inWriteAlphaEnabled) override;
	
	virtual void SetWireframe(bool inWireframe) override
	{
		SetRenderState(SEXY3DRS_FILLMODE, inWireframe ? SEXY3DFILL_WIREFRAME : SEXY3DFILL_SOLID);
	}
	virtual void SetBlend(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend) override;
	virtual void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise) override
	{
		if (inCullClockwise)
		{
			if (inCullCounterClockwise)
			{
				assert(false && "SetBackfaceCulling called with both windings culled; was this deliberate?");
			}
			else
			{
				SetRenderState(SEXY3DRS_CULLMODE, SEXY3DCULL_CW);
			}
		}
		else
		{
			SetRenderState(SEXY3DRS_CULLMODE, inCullCounterClockwise ? SEXY3DCULL_CCW : SEXY3DCULL_NONE);
		}
	}

	virtual void SetLightingEnabled(bool inLightingEnabled) override
	{
		SetRenderState(SEXY3DRS_LIGHTING, inLightingEnabled);
	}
	virtual void SetLightEnabled(int inLightIndex, bool inEnabled) override;
	virtual void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation) override;
	virtual void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors) override;
	virtual void SetGlobalAmbient(const Color& inColor) override
	{
		SetRenderState(SEXY3DRS_AMBIENT, inColor.ToInt());
	}
	virtual void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1) override;
	virtual void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1) override;
	virtual void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f) override;
	virtual void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1) override;

	virtual void SetWorldTransform(const SexyMatrix4* inMatrix) override
	{
		SexyMatrix4 aTempMat;
		if (!inMatrix)
		{
			aTempMat.LoadIdentity();
			inMatrix = &aTempMat;
		}
		SetTransform(SEXY3DTS_WORLD, inMatrix);
	}
	virtual void SetViewTransform(const SexyMatrix4* inMatrix) override
	{
		SexyMatrix4 aTempMat;
		if (!inMatrix)
		{
			aTempMat.LoadIdentity();
			inMatrix = &aTempMat;
		}
		SetTransform(SEXY3DTS_VIEW, inMatrix);
	}
	virtual void SetProjectionTransform(const SexyMatrix4* inMatrix) override
	{
		SexyMatrix4 aTempMat;
		if (!inMatrix)
		{
			aTempMat.LoadIdentity();
			inMatrix = &aTempMat;
		}
		SetTransform(SEXY3DTS_PROJECTION, inMatrix);
	}
	virtual void SetTextureTransform(int inTextureIndex, const SexyMatrix4* inMatrix, int inNumDimensions = 2) override
	{
		if (!inMatrix || (inNumDimensions <= 0))
		{
			SetTextureStageState(inTextureIndex, SEXY3DTSS_TEXTURETRANSFORMFLAGS, 0); // disable
		}
		else
		{
			SetTransform(SEXY3DTS_TEXTURE0+inTextureIndex, inMatrix);
			SetTextureStageState(inTextureIndex, SEXY3DTSS_TEXTURETRANSFORMFLAGS, inNumDimensions); // texture transform flags for the counts are the values themselves
		}
	}

	virtual bool SetTexture(int inTextureIndex, Image* inImage) override;
	virtual void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV) override;
	virtual void SetTextureLinearFilter(int inTextureIndex, bool inLinear = true) override;
	virtual void SetTextureCoordSource(int inTextureIndex, int inUVComponent, Graphics3D::ETexCoordGen inTexGen = Graphics3D::TEXCOORDGEN_NONE) override;
	virtual void SetTextureFactor(int inTextureFactor) override
	{
		SetRenderState(SEXY3DRS_TEXTUREFACTOR, inTextureFactor);
	}

	virtual void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ);

	virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition) override;

	virtual void SetBltFilter(FBltFilter inFilter, void* inContext) override
	{
		mBltFilter = inFilter;
		mBltFilterContext = inContext;
	}
	virtual void SetDrawPrimFilter(FDrawPrimFilter inFilter, void* inContext) override
	{
		mDrawPrimFilter = inFilter;
		mDrawPrimFilterContext = inContext;
	}

	virtual bool LoadMesh(Mesh* theMesh) override;
	virtual void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true) override;

	/*
		...RenderDevice3D implementation
	*/

	//////////////////////////////////////////////////////////////////////////////////////////
	// Internal methods - not intended to be called from game code
	//////////////////////////////////////////////////////////////////////////////////////////

protected:
	bool PreDraw();
	void SetDefaultState(Image* inImage, bool inIsInScene);
	void SetupDrawMode(int theDrawMode);
	Image* SetupAtlasState(int inTextureIndex, Image* inImage);
	void AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, int inStride, int inTexUVOfs);
	
	void BltClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect *theClipRect, const Color& theColor, int theDrawMode)
	{
		SexyTransform2D aTransform;
		aTransform.Translate(theX, theY);

		BltTransformed(theImage,theClipRect,theColor,theDrawMode,theSrcRect,aTransform,true);
	}
	void BltNoClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter = false);
	void BltTransformed(Image* theImage, const Rect* theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, const SexyMatrix3 &theTransform, bool linearFilter, float theX = 0, float theY = 0, bool center = false);	

	void BufferedDrawPrimitive(int thePrimType, ulong thePrimCount, const D3DTLVERTEX* theVertices, int theVertexSize, ulong theVertexFormat);
	void FlushBufferedTriangles();

	void CheckBatchAndCommit();
	
	virtual void DrawPrimitiveInternal(ulong inPrimType, ulong inPrimCount, const void* inVertData, ulong inVertStride, ulong inVertFormat, bool inDoCommit=true) = 0;

	IGraphicsDriver::ERenderMode GetEffectiveRenderMode();

private:
	void DrawPolyClipped(const Rect *theClipRect, const D3DVertexList &theList);

	void SetRenderState(ulong theRenderState, ulong theValue);
	void SetSamplerState(ulong theSampler, ulong theState, ulong theValue);
	void SetTextureStageState(ulong theTextureStage, ulong theState, ulong theValue);
	void SetTransform(ulong theTransformState, const SexyMatrix4* theMatrix);
	void SetTextureDirect(ulong theTexture, void* theTexSurface);

public:
	virtual HRESULT InternalValidateDevice(DWORD* outNumPasses) = 0;
	virtual HRESULT InternalCreateVertexShader(const DWORD* inFunction, IUnknown** outShader) = 0;
	virtual HRESULT InternalCreatePixelShader(const DWORD* inFunction, IUnknown** outShader) = 0;
	virtual HRESULT InternalSetPaletteEntries(UINT inPaletteNumber, const PALETTEENTRY* inEntries) = 0;
	virtual HRESULT InternalGetPaletteEntries(UINT inPaletteNumber, PALETTEENTRY* outEntries) = 0;
	virtual HRESULT InternalCreateTexture(UINT inWidth, UINT inHeight, UINT inLevels, bool inRenderTarget, PixelFormat inFormat, ulong inPool, IUnknown** outTexture) = 0;
	virtual HRESULT InternalCreateCubeTexture(UINT inEdgeLength, UINT inLevels, DWORD inUsage, PixelFormat inFormat, ulong inPool, IUnknown** outCubeTexture) = 0;
	virtual HRESULT InternalCreateVolumeTexture(UINT inWidth, UINT inHeight, UINT inDepth, UINT inLevels, DWORD inUsage, PixelFormat inFormat, ulong inPool, IUnknown** outVolumeTexture) = 0;
	virtual HRESULT InternalUpdateTexture(IUnknown* inSourceTexture, IUnknown* inDestTexture) = 0;
	virtual HRESULT InternalCreateImageSurface(UINT inWidth, UINT inHeight, PixelFormat inFormat, IUnknown** outSurface) = 0;
	virtual HRESULT InternalGetRenderTargetData(IUnknown* inRenderTarget, IUnknown* inDestSurface) = 0;
	virtual HRESULT InternalSurfaceLockRect(IUnknown* inSurface, INT& outPitch, void*& outBits) = 0;
	virtual HRESULT InternalSurfaceUnlockRect(IUnknown* inSurface) = 0;
	virtual HRESULT InternalTextureGetSurfaceLevel(IUnknown* inTexture, UINT inLevel, IUnknown** outSurface) = 0;
	virtual HRESULT InternalTextureMakeDirty(IUnknown* inTexture) = 0;
	virtual HRESULT InternalTextureLockRect(IUnknown* inTexture, INT& outPitch, void*& outBits) = 0;
	virtual HRESULT InternalTextureUnlockRect(IUnknown* inTexture) = 0;
	virtual HRESULT InternalCubeTextureLockRect(IUnknown* inCubeTexture, ulong inFace, INT& outPitch, void*& outBits) = 0;
	virtual HRESULT InternalCubeTextureUnlockRect(IUnknown* inCubeTexture, ulong inFace) = 0;
	virtual HRESULT InternalVolumeTextureLockBox(IUnknown* inVolumeTexture, INT& outRowPitch, INT& outSlicePitch, void*& outBits) = 0;
	virtual HRESULT InternalVolumeTextureUnlockBox(IUnknown* inVolumeTexture) = 0;
	virtual HRESULT InternalSetRenderTarget(void* inRenderTargetSurface) = 0;
	virtual HRESULT InternalBeginScene() = 0;
	virtual HRESULT InternalCreateVertexBuffer(UINT inLength, bool inIsDynamic, DWORD inFVF, ulong inPool, IUnknown** outVertexBuffer) = 0;
	virtual HRESULT InternalCreateIndexBuffer(UINT inLength, ulong inPool, IUnknown** outIndexBuffer) = 0;
	virtual HRESULT InternalVertexBufferLock(IUnknown* inVertexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags) = 0;
	virtual HRESULT InternalVertexBufferUnlock(IUnknown* inVertexBuffer) = 0;
	virtual HRESULT InternalIndexBufferLock(IUnknown* inIndexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags) = 0;
	virtual HRESULT InternalIndexBufferUnlock(IUnknown* inIndexBuffer) = 0;
	virtual HRESULT InternalDrawIndexedPrimitive(ulong inPrimType, UINT inMinIndex, UINT inNumVertices, UINT inStartIndex, UINT inPrimCount) = 0;
	virtual HRESULT InternalSetStreamSource(UINT inStreamNumber, IUnknown* inVertexBuffer, UINT inStride) = 0;
	
public:
	struct PtrData
	{
		std::vector<std::string>			mFiles;
		std::vector<int>					mLines;
	}; // ref count is implicit in mFiles.size() and mLines.size()
	typedef std::map<void*, PtrData>		PtrDataMap;

	static PtrDataMap		sPtrData;
	static void				D3DAddRef(void* thePtr, const char* theFile, int theLine);
	static void				D3DDelRef(void* thePtr, const char* theFile, int theLine);
	static void				PrintRefsFor(void* thePtr);
	static void				PrintRemainingRefs();
	static bool				CheckDXError(HRESULT theError, const char *theMsg="");
};

}

#endif //__D3DINTERFACE_H__
