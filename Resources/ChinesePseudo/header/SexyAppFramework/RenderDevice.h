#pragma once
#ifndef __RENDERDEVICE_H__
#define __RENDERDEVICE_H__
//****************************************************************************
//**
//**  File     :  RENDERDEVICE.H
//**  Summary  :  Header - Low-level rendering device interfaces
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
#include "Common.h"
#include "Color.h"
#include "Rect.h"
#include "Point.h"
#include "Graphics.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
enum PixelFormat
{
	PixelFormat_Unknown				=			0x0000,
	PixelFormat_A8R8G8B8			=			0x0001,
	PixelFormat_A4R4G4B4			=			0x0002,
	PixelFormat_R5G6B5				=			0x0004,
	PixelFormat_Palette8			=			0x0008,
	PixelFormat_X8R8G8B8			=			0x0010,
	PixelFormat_DXT5				=			0x0020
};

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
class RenderDevice;
class RenderDevice3D;
// forward declarations
class Image;
class SexyMatrix3;
class SexyMatrix4;
class SexyVector3;
class SexyVertex;
class SexyVertex2D;
class Mesh;
class DeviceImage;
class RenderEffect;
class RenderEffectDefinition;

/*
	RenderSurface

	This was changed from an IUnknown to an abstract interface for Prime.
*/
#ifdef HOST_WINDOWS
typedef IUnknown RenderSurface;
#else
//JVW -- this should be an opaque ref... BUT shared render target needs 
// ref counting on it as well (b/c it thinks that this is IUnknown)
//Todo, add "ReleaseRenderSurface" to GraphicsDriver, and let it figure it out
class RenderSurface
{
public:
	int mData;
	void* mPtr;
	RenderSurface()
	{
		mRefCount = 0;
		mData = 0;
		mPtr = NULL;
	}
public:
	
	virtual ~RenderSurface() {} ;
	
	void AddRef()
	{
		mRefCount++;
	}
	
	void Release()
	{
		mRefCount--;
		if (mRefCount <= 0)
		{
			delete this;
		}
	}
	
private:
	uint32 mRefCount;
};
#endif

/*
	RenderDevice

	Abstract low-level rendering device with basic 2D capability, usable with
	both hardware (3D accelerated) and software (non-accelerated) rendering.
*/
class RenderDevice
{
public:
	virtual ~RenderDevice() {}

	///////////////////////////////////////////////////////
	// Capabilities
	///////////////////////////////////////////////////////

	// Get the 3D interface for this device, or NULL if not available (for software rendering implementations)
	virtual RenderDevice3D* Get3D() = 0;

	// Get whether FillPoly is supported by the device
	virtual bool CanFillPoly() = 0;

	///////////////////////////////////////////////////////
	// Context Management
	///////////////////////////////////////////////////////

	// Create a rendering context for this device, using the given destination image to draw to
	virtual HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext = HRenderContext((void*)0)) = 0;

	// Delete a previously created rendering context
	virtual void DeleteContext(const HRenderContext& theContext) = 0;

	// Set the given rendering context as current
	virtual void SetCurrentContext(const HRenderContext& theContext) = 0;

	// Get the current rendering context for the device
	virtual HRenderContext GetCurrentContext() const = 0;

	///////////////////////////////////////////////////////
	// State Stack
	///////////////////////////////////////////////////////

	// Push/pop the state of the current context
	virtual void PushState() = 0;
	virtual void PopState() = 0;

	///////////////////////////////////////////////////////
	// Drawing Methods
	///////////////////////////////////////////////////////

	// span structure used with FillScanLines* methods
	struct Span
	{
		int mY;
		int mX;
		int mWidth;
	};

	// 2D drawing methods (not heavily documented at the moment, since variants of these have been around in the framework for a long time and should be pretty familiar)

	virtual void ClearRect(const Rect& theRect) = 0;
	virtual void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode) = 0;	
	virtual void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const uint8* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight) = 0;
	virtual void FillPoly(const Point theVertices[], int theNumVertices, const Rect *theClipRect, const Color &theColor, int theDrawMode, int tx, int ty) = 0;
	virtual void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode, bool antiAlias = false) = 0;
	virtual void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) = 0;
	virtual void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode) = 0;
	virtual void BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY) = 0;
	virtual void BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend) = 0;
    virtual void BltMatrix2(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend,bool center) = 0;
#if OPTIMIZE_ANIM_DRAW
	virtual void BltMatrixOptimized(Image* theImage, MATH_TYPE x, MATH_TYPE y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool blend, bool bNeedUpdateImage){}
#endif
	virtual void BltTriangles(Image* theImage, const SexyVertex2D theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, const Rect* theClipRect = NULL) = 0;
	virtual void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) = 0;
	virtual void BltStretched(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror = false) = 0;
#ifdef PRIME_FOR_BEJBLITZ
	virtual void BltStretchedSpecial(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirrorX, bool mirrorY) {DBG_ASSERT(false);};
#endif // PRIME_FOR_BEJBLITZ
    
    virtual void CopyIntoImage(Image* theTexture, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData) = 0;
    virtual void BltStretchedAndRotated(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, bool fastStretch, bool mirror = false) = 0;
	
	// Methods with default implementations based on other virtual methods

	virtual void DrawRect(const Rect& theRect, const Color& theColor, int theDrawMode)
	{
		FillRect(Rect(theRect.mX, theRect.mY, theRect.mWidth + 1, 1), theColor, theDrawMode);
		FillRect(Rect(theRect.mX, theRect.mY + theRect.mHeight, theRect.mWidth + 1, 1), theColor, theDrawMode);
		FillRect(Rect(theRect.mX, theRect.mY + 1, 1, theRect.mHeight - 1), theColor, theDrawMode);
		FillRect(Rect(theRect.mX + theRect.mWidth, theRect.mY + 1, 1, theRect.mHeight - 1), theColor, theDrawMode);
	}
	virtual void FillScanLines(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode)
	{
		for (int i = 0; i < theSpanCount; i++)
		{
			Span* aSpan = &theSpans[i];		
			FillRect(Rect(aSpan->mX, aSpan->mY, aSpan->mWidth, 1), theColor, theDrawMode);		
		}
	}
};

/*
	RenderDevice3D

	Abstract low-level rendering device with both 2D and 3D capability.
	Requires hardware (3D accelerated) rendering.
*/
class RenderDevice3D
: public RenderDevice
{
public:
	///////////////////////////////////////////////////////
	// Initialization / Cleanup
	///////////////////////////////////////////////////////
	//these were moved up to D3Dinterface in Prime, 
	// other plats will have different init params
	//virtual bool InitFromDDInterface(DDInterface *theInterface, DDInterface::EResult* outErrorResult, bool preTestOnly, bool* outIsRecommended = NULL) = 0;
	//virtual void Cleanup() = 0;

	///////////////////////////////////////////////////////
	// Flush / Present
	///////////////////////////////////////////////////////
	enum EFlushFlags
	{
		FLUSHF_BufferedTris					= (1 << 0), // flush any triangles currently buffered up for drawing
		FLUSHF_CurrentScene					= (1 << 1), // flush the current scene, usually only done right before presenting a frame
		FLUSHF_ManagedResources_Immediate	= (1 << 2), // flush out any managed resources (like textures) from video memory
		FLUSHF_ManagedResources_OnPresent	= (1 << 3), // flush out any managed resources, but wait until the frame is presented to do so
        FLUSHF_BufferedState                = (1 << 4), // flush any triangles dependent on current hardware state, then commit newly buffered state to hardware
	};

	// Flush the graphics state; see individual flags for details
	virtual bool Flush(uint32 inFlushFlags = FLUSHF_CurrentScene) = 0; // EFlushFlags

	// Present the back buffer to the window
	virtual bool Present(const Rect* theSrcRect, const Rect* theDestRect) = 0;
	
	///////////////////////////////////////////////////////
	// Capabilities / Status / Diagnostics
	///////////////////////////////////////////////////////
	enum ECapsFlags
	{
		CAPF_SingleImageTexture			= (1 << 0), // Images occupy a single image
		CAPF_PixelShaders				= (1 << 1),
		CAPF_VertexShaders				= (1 << 2),
		CAPF_ImageRenderTargets			= (1 << 3),
		CAPF_AutoWindowedVSync			= (1 << 4),
		CAPF_CubeMaps					= (1 << 5),
		CAPF_VolumeMaps					= (1 << 6),
		CAPF_CopyScreenImage			= (1 << 7),
		CAPF_LastLockScreenImage		= (1 << 8),  //has special handling for the SharedRenderTarget hint on last lock screen image
	};

	enum EInfoString
	{
		INFOSTRING_Adapter,
		INFOSTRING_DrvProductVersion,
		INFOSTRING_DisplayMode,
		INFOSTRING_BackBuffer,
		INFOSTRING_TextureMemory,
		INFOSTRING_DrvResourceManager,
		INFOSTRING_DrvProductFeatures,  //on GL extensions we care about. on DX its caps we care about
	};

	// Get capabilities flags; the most commonly used ones have inline convenience accessors
	virtual uint32 GetCapsFlags() = 0;
	inline bool SupportsPixelShaders() { return (GetCapsFlags() & CAPF_PixelShaders) != 0; }
	inline bool SupportsVertexShaders() { return (GetCapsFlags() & CAPF_VertexShaders) != 0; }
	inline bool SupportsCubeMaps() { return (GetCapsFlags() & CAPF_CubeMaps) != 0; }
	inline bool SupportsVolumeMaps() { return (GetCapsFlags() & CAPF_VolumeMaps) != 0; }
	inline bool SupportsImageRenderTargets() { return (GetCapsFlags() & CAPF_ImageRenderTargets) != 0; }

	// Get the maximum number of available texture stages
	virtual int GetMaxTextureStages() = 0;

	// Get a general information string, for diagnostics
	virtual std::string GetInfoString(EInfoString inInfoStr) = 0;

	// Get the dimensions of the internally-created back buffer
	virtual void GetBackBufferDimensions(uint32& outWidth, uint32& outHeight) = 0;

	// Get whether we are in a BeginScene/EndScene block
	virtual bool SceneBegun() = 0;

	///////////////////////////////////////////////////////
	// Image RenderData Management
	///////////////////////////////////////////////////////
	
	// Create hardware render data (textures etc) for a memory image
	virtual bool CreateImageRenderData(MemoryImage* inImage) = 0;

	// Remove any hardware render data previously created for the given image
	virtual void RemoveImageRenderData(MemoryImage* inImage) = 0;

	// Recover the bits of a memory image from the hardware render data, or as close an approximation as possible
	virtual bool RecoverImageBitsFromRenderData(MemoryImage* inImage, int i_x, int i_y, int i_width, int i_height, int fbo) = 0;
	
	// Get the current size or pixel format of a memory image's texture render data (will be zero if no render data is present)
	virtual int	GetTextureMemorySize(MemoryImage* theImage) = 0;
	virtual PixelFormat GetTextureFormat(MemoryImage* theImage) = 0;

	///////////////////////////////////////////////////////
	// Surface Management
	///////////////////////////////////////////////////////

	//JVW -- I'm not sure that the following surface functions are need in Prime,
	// other plats have different concepts when it comes to these and as far as I can tell, these methods
	// all get called from inside of the "driver wall" 
	// for now I am moving them into D3D

	// Get the surface for the hardware backbuffer
	/*virtual RenderSurface* GetBackBufferSurface() = 0;

	// Create a surface with the given characteristics
	virtual RenderSurface* CreateSurface(int inWidth, int inHeight, bool inRenderTarget, bool inTexture) = 0;

	// Blit a surface to the current render target, if supported (CanBltSurface indicates support for this feature)
	virtual bool CanBltSurface(bool srcSurfaceIsTexture) = 0;
	virtual void BltSurface(RenderSurface* theSurface, const Rect& theDest, const Rect& theSrc) = 0;

	// Set the current render target, as a surface or an image (the image must have the render target image flag enabled)
	virtual bool SetRenderTargetSurface(RenderSurface* inSurface) = 0;
	virtual bool SetRenderTarget(Image* theRenderTarget) = 0;*/

	// Swap the given image with the screen image (low-level and only intended for use by SharedRenderTarget implementation; do not call from game code)
	virtual Image*	SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags) = 0;
	virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags) = 0;

	///////////////////////////////////////////////////////
	// Drawing Methods
	///////////////////////////////////////////////////////

	// Adjust UVs for texture atlasing etc (optimization for repeated calls to DrawPrimitive with same vertex data; call DrawPrimitive with DPF_NoAdjustUVs flag set afterwards)
	virtual void AdjustVertexUVsEx(uint32 theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize) = 0;
	template<class T> void AdjustVertexUVs(SexyVertex* theVertices, int theVertexCount)
	{
		AdjustVertexUVsEx(T::FVF, theVertices, theVertexCount, sizeof(T));
	}

	// Draw primitive
	virtual void DrawPrimitiveEx(uint32 theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0) = 0;
	template<class T> void DrawPrimitive(Graphics3D::EPrimitiveType thePrimitiveType, const T* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0)
	{
		DrawPrimitiveEx(T::FVF, thePrimitiveType, theVertices, thePrimitiveCount, theColor, theDrawMode, tx, ty, blend, theFlags);
	}

	///////////////////////////////////////////////////////
	// Enhanced 2D Support (affects 2D drawing methods in the basic RenderDevice)
	///////////////////////////////////////////////////////
	
	// Set the depth buffer depth (between 0.0 and 1.0) that the 2D Blt-related functions use when drawing
	virtual void SetBltDepth(float inDepth) = 0;

	// Push/pop a transform to use with 2D Blt-related functions
	virtual void PushTransform(const SexyMatrix3 &theTransform, bool concatenate = true) = 0;
	virtual void PopTransform() = 0;
	virtual void PopTransform(SexyMatrix3 &theTransform) = 0;

	///////////////////////////////////////////////////////
	// Clearing
	///////////////////////////////////////////////////////

	// Clear the color buffer to a given color
	virtual void ClearColorBuffer(const Color& inColor = Color::Black) = 0;

	// Clear the depth buffer to the maximum depth (1.0)
	virtual void ClearDepthBuffer() = 0;

	///////////////////////////////////////////////////////
	// Common Render State
	///////////////////////////////////////////////////////

	// Set the depth-test and depth-write states
	virtual void SetDepthState(Graphics3D::ECompareFunc inDepthTestFunc, bool inDepthWriteEnabled) = 0;

	// Set the alpha-test states
	virtual void SetAlphaTest(Graphics3D::ECompareFunc inAlphaTestFunc, int inRefAlpha) = 0;

	// Sets the color write mask states
	virtual void SetColorWriteState(bool inWriteRedEnabled,bool inWriteGreenEnabled,bool inWriteBlueEnabled,bool inWriteAlphaEnabled) = 0;
	
	// Set whether or not wireframe rendering is enabled
	virtual void SetWireframe(bool inWireframe) = 0;

	// Set the source and destination blend modes; use BLEND_DEFAULT to use whatever is normally appropriate based on the current draw mode
	virtual void SetBlend(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend) = 0;

	// Set culling mode; either both of these can be false, or one can be true (don't set both to true, or nothing will draw)
	virtual void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise) = 0;

	///////////////////////////////////////////////////////
	// Lighting State
	///////////////////////////////////////////////////////

	// Enable lighting (all lights are ignored unless this is enabled)
	virtual void SetLightingEnabled(bool inLightingEnabled) = 0;

	// Enable a given light by index
	virtual void SetLightEnabled(int inLightIndex, bool inEnabled) = 0;

	// Set up light state by index
	virtual void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation) = 0;
	virtual void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors) = 0;

	// Set global ambient lighting color
	virtual void SetGlobalAmbient(const Color& inColor) = 0;

	// Set material lighting state; if the vertex color component is zero or greater, the inColor parameter is ignored and the given per-vertex color is used instead
	virtual void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1) = 0;
	virtual void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1) = 0;
	virtual void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f) = 0;
	virtual void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1) = 0;

	///////////////////////////////////////////////////////
	// 3D Transform State
	///////////////////////////////////////////////////////
	
	// Set the world/view/projection transform.  If NULL is passed in, the identity transform will be used
	virtual void SetWorldTransform(const SexyMatrix4* inMatrix) = 0; // transform; NULL is identity
	virtual void SetViewTransform(const SexyMatrix4* inMatrix) = 0; // transform; NULL is identity
	virtual void SetProjectionTransform(const SexyMatrix4* inMatrix) = 0; // transform; NULL is identity

	// Set a given texture transform.  If NULL is passed in, texture-transform will be disabled (the default) for that texture stage
	virtual void SetTextureTransform(int inTextureIndex, const SexyMatrix4* inMatrix, int inNumDimensions = 2) = 0;

	virtual void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ) = 0;
	///////////////////////////////////////////////////////
	// Texture State
	///////////////////////////////////////////////////////

	// Set a given image as a texture
	virtual bool SetTexture(int inTextureIndex, Image* inImage) = 0;

	// Enable/disable wrapping for a texture.  Note that this feature should only be used with textures that have power-of-two dimensions, for compatibility
	virtual void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV) = 0;

	// Enable/disable filtering for a texture.  Primarily used by Render3DObject; most other drawing methods have a parameter for this
	virtual void SetTextureLinearFilter(int inTextureIndex, bool inLinear = true) = 0;

	// Set the texture coordinate source (vertex UV component pair) used by a texture, or the tex-coord generation feature to use instead
	virtual void SetTextureCoordSource(int inTextureIndex, int inUVComponent, Graphics3D::ETexCoordGen inTexGen = Graphics3D::TEXCOORDGEN_NONE) = 0;

	// Set the constant-color "texture factor" state, used primarily with fixed-function combiners in effects
	virtual void SetTextureFactor(int inTextureFactor) = 0;

	///////////////////////////////////////////////////////
	// Effects
	///////////////////////////////////////////////////////

	// Get a render effect interface for the given effect definition; see RenderEffect.h for more details
	virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition) = 0;

	// Reload effects from their source data.  Default implementation does nothing; this is strictly for debugging purposes.
	virtual bool ReloadEffects() { return false; } // deprecated original method; kept for driver compatibility
	virtual bool ReloadEffects(bool inDebug) { return ReloadEffects(); }

	///////////////////////////////////////////////////////
	// Filters (default implementation does nothing; these are purely for optimization)
	///////////////////////////////////////////////////////

	typedef bool (*FBltFilter)(void* theContext, int thePrimType, uint32 thePrimCount, const SexyVertex2D* theVertices, int theVertexSize, const Rect** theClipRect);
	typedef bool (*FDrawPrimFilter)(void* theContext, int thePrimType, uint32 thePrimCount, const SexyVertex2D* theVertices, int theVertexSize);

	// Set a custom filter callback function used by certain 2D functions
	virtual void SetBltFilter(FBltFilter inFilter, void* inContext) {}
	virtual void SetDrawPrimFilter(FDrawPrimFilter inFilter, void* inContext) {}

	///////////////////////////////////////////////////////
	// Static 3D Object Loading / Rendering
	//
	// Placeholder; will need further refactoring at some point since D3DObject is still implemented in a very D3D-specific manner
	//
	///////////////////////////////////////////////////////
	virtual bool LoadMesh(Mesh* theMesh) = 0;	
	virtual void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true) = 0;

#if SEXY_IS_PLATFORM_ANDROID
	virtual void * CreateTextureData( struct ResStreamFileGPULocationInfo* theLocationInfo, void * theTextureBacking, void * theTextureMulti ) { DBG_ASSERT(0); return NULL; }
	virtual void DestroyTextureData( void * textureDatas ) { DBG_ASSERT(0); }
	virtual void SetTextureInfoIntoTextureData( void * pTextureData, void * pTextureInfo, void * pTextureInfoMulti ) { DBG_ASSERT(0); }
#endif // SEXY_IS_PLATFORM_ANDROID

	virtual void LostFocus() { return; }
	virtual void GotFocus() { return; }
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
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER RENDERDEVICE.H
//**
//****************************************************************************
#endif // __RENDERDEVICE_H__
