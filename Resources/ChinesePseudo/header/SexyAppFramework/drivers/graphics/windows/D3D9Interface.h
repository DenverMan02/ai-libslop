#ifndef __D3D9INTERFACE_H__
#define __D3D9INTERFACE_H__

#define NOMINMAX
#include <d3d9.h>
#include <ddraw.h>
#include <d3dx9.h>
#include "D3DInterface.h"
#include "SharedImage.h"

namespace Sexy
{

class DXSurface9;
class Buffer;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class D3D9Interface : public D3DInterface
{
protected:
	friend class DXSurface9;
	friend class D3DStateManager9;

	LPDIRECT3D9				mD3D;
	LPDIRECT3DDEVICE9		mD3DDevice;
	D3DPRESENT_PARAMETERS	mD3DPresentParams;
	LPDIRECT3DSURFACE9		mFullscreenZBuffer;

	D3DCAPS9				mDeviceCaps;

	IDirect3DQuery9*		mTexMemResQuery;
	D3DDEVINFO_RESOURCEMANAGER mTexMemResQueryStats;

	// ping-pong surfaces used when lag prevention is active
	LPDIRECT3DSURFACE9		mPingPongRenderTarget[2];
	LPDIRECT3DSURFACE9		mPingPongMemSurface;
	bool					mPingPongToggle;

	static bool				CheckRequiredCaps(const D3DCAPS9& theCaps);

	virtual bool			InitD3D(IGraphicsDriver::EResult* outErrorResult, bool preTestOnly, bool* outIsRecommended);
	virtual void			SetupSupportedRenderTargetFormats();
	virtual void			SetupSupportedTextureFormats(D3DFORMAT theDisplayFormat);

	virtual void			DrawPrimitiveInternal(ulong inPrimType, ulong inPrimCount, const void* inVertData, ulong inVertStride, ulong inVertFormat, bool inDoCommit=true) override;

	virtual bool			CompileEffect(const char* inSrcFile, Buffer& outBuffer, bool inDebug);

public:
	D3D9Interface(void);
	virtual ~D3D9Interface(void);

	/*
		RenderDevice3D implementation
	*/
	virtual bool			InitFromGraphicsDriver(WindowsGraphicsDriver *theDriver, IGraphicsDriver::EResult* outErrorResult, bool preTestOnly, bool* outIsRecommended = NULL) override;
	virtual void			Cleanup() override;

	virtual bool			Flush(ulong inFlushFlags = FLUSHF_CurrentScene) override;
	virtual bool			Present(const Rect* theSrcRect, const Rect* theDestRect) override;

	virtual uint32			GetCapsFlags() override;
	virtual int				GetMaxTextureStages() override;
	virtual std::string		GetInfoString(EInfoString theInfoString) override;
	virtual void			GetBackBufferDimensions(ulong& outWidth, ulong& outHeight) override;

	virtual IUnknown*		CreateSurface(int inWidth, int inHeight, bool inRenderTarget, bool inTexture) override;
	virtual bool			CanBltSurface(bool srcSurfaceIsTexture) override;
	virtual void			BltSurface(IUnknown* theSurface, const Rect& theSrc, const Rect& theDest) override;
	
	virtual void			ClearColorBuffer(const Color& inColor = Color::Black) override;
	virtual void			ClearDepthBuffer() override;

	virtual bool			ReloadEffects() override { return ReloadEffects(false); }
	virtual bool			ReloadEffects(bool inDebug) override;
	
	/*
		Misc methods
	*/
	// CDH FIXME$$ temporary method, intended for use in ResourceGen2; do not use in games.  Remove once effect compilation is moved here into the framework.
	IDirect3DDevice9*		GetRawDevice() { return mD3DDevice; }

	//////////////////////////////////////////////////////////////////////////////////////////
	// Internal device methods
	//////////////////////////////////////////////////////////////////////////////////////////

protected:
	virtual HRESULT InternalValidateDevice(DWORD* outNumPasses) override;
	virtual HRESULT InternalCreateVertexShader(const DWORD* inFunction, IUnknown** outShader) override;
	virtual HRESULT InternalCreatePixelShader(const DWORD* inFunction, IUnknown** outShader) override;
	virtual HRESULT InternalSetPaletteEntries(UINT inPaletteNumber, const PALETTEENTRY* inEntries) override;
	virtual HRESULT InternalGetPaletteEntries(UINT inPaletteNumber, PALETTEENTRY* outEntries) override;
	virtual HRESULT InternalCreateTexture(UINT inWidth, UINT inHeight, UINT inLevels, bool inRenderTarget, PixelFormat inFormat, ulong inPool, IUnknown** outTexture) override;
	virtual HRESULT InternalCreateCubeTexture(UINT inEdgeLength, UINT inLevels, DWORD inUsage, PixelFormat inFormat, ulong inPool, IUnknown** outCubeTexture) override;
	virtual HRESULT InternalCreateVolumeTexture(UINT inWidth, UINT inHeight, UINT inDepth, UINT inLevels, DWORD inUsage, PixelFormat inFormat, ulong inPool, IUnknown** outVolumeTexture) override;
	virtual HRESULT InternalUpdateTexture(IUnknown* inSourceTexture, IUnknown* inDestTexture) override;
	virtual HRESULT InternalCreateImageSurface(UINT inWidth, UINT inHeight, PixelFormat inFormat, IUnknown** outSurface) override;
	virtual HRESULT InternalGetRenderTargetData(IUnknown* inRenderTarget, IUnknown* inDestSurface) override;
	virtual HRESULT InternalSurfaceLockRect(IUnknown* inSurface, INT& outPitch, void*& outBits) override;
	virtual HRESULT InternalSurfaceUnlockRect(IUnknown* inSurface) override;
	virtual HRESULT InternalTextureGetSurfaceLevel(IUnknown* inTexture, UINT inLevel, IUnknown** outSurface) override;
	virtual HRESULT InternalTextureMakeDirty(IUnknown* inTexture) override;
	virtual HRESULT InternalTextureLockRect(IUnknown* inTexture, INT& outPitch, void*& outBits) override;
	virtual HRESULT InternalTextureUnlockRect(IUnknown* inTexture) override;
	virtual HRESULT InternalCubeTextureLockRect(IUnknown* inCubeTexture, ulong inFace, INT& outPitch, void*& outBits) override;
	virtual HRESULT InternalCubeTextureUnlockRect(IUnknown* inCubeTexture, ulong inFace) override;
	virtual HRESULT InternalVolumeTextureLockBox(IUnknown* inVolumeTexture, INT& outRowPitch, INT& outSlicePitch, void*& outBits) override;
	virtual HRESULT InternalVolumeTextureUnlockBox(IUnknown* inVolumeTexture) override;
	virtual HRESULT InternalSetRenderTarget(void* inRenderTargetSurface) override;
	virtual HRESULT InternalBeginScene() override;
	virtual HRESULT InternalCreateVertexBuffer(UINT inLength, bool inIsDynamic, DWORD inFVF, ulong inPool, IUnknown** outVertexBuffer) override;
	virtual HRESULT InternalCreateIndexBuffer(UINT inLength, ulong inPool, IUnknown** outIndexBuffer) override;
	virtual HRESULT InternalVertexBufferLock(IUnknown* inVertexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags) override;
	virtual HRESULT InternalVertexBufferUnlock(IUnknown* inVertexBuffer) override;
	virtual HRESULT InternalIndexBufferLock(IUnknown* inIndexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags) override;
	virtual HRESULT InternalIndexBufferUnlock(IUnknown* inIndexBuffer) override;
	virtual HRESULT InternalDrawIndexedPrimitive(ulong inPrimType, UINT inMinIndex, UINT inNumVertices, UINT inStartIndex, UINT inPrimCount) override;
	virtual HRESULT InternalSetStreamSource(UINT inStreamNumber, IUnknown* inVertexBuffer, UINT inStride) override;
};
} // namespace Sexy

#endif // #ifndef D3D9INTERFACE_H
