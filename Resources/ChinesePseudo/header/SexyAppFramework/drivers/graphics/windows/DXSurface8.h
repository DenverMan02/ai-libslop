#ifndef DXSURFACE8_H
#define DXSURFACE8_H
#define NOMINMAX

#include <d3d8.h>
#include <ddraw.h>
#include "IDXSurface.h"

namespace Sexy
{
	class WindowsGraphicsDriver;
	class D3D8Interface;
	class DXSurface8 : public IDXSurface
	{
		WindowsGraphicsDriver*		mDriver;
		D3D8Interface*		mD3DInterface;
		IDirect3DResource8*	mSurface;
		IDirect3DSurface8*	mTextureSurface;						// _getTexture()->GetSurfaceLevel surface.
		ulong				mSurfaceFormat;
		int					mRedBits, mRedShift, mRedMask;
		int					mGreenBits, mGreenShift, mGreenMask;
		int					mBlueBits, mBlueShift, mBlueMask;
		bool				mIsTexture;

	private:
		inline IDirect3DTexture8* _getTexture() const { return (IDirect3DTexture8*)mSurface; }
		inline IDirect3DSurface8* _getSurface() const { return (IDirect3DSurface8*)mSurface; }

	public:
		DXSurface8(WindowsGraphicsDriver* theDriver);
		virtual ~DXSurface8(void);

		virtual int			GetVersion() const { return 8; }

		bool				Lock(DeviceSurfaceDesc* theParam);
		void				Unlock(void*);
		
		bool				GenerateDeviceSurface(DeviceImage* theImage);
		bool				HasSurface() const { return mSurface != NULL; }
		void*				GetSurfacePtr() const { return (void*)mSurface; }

		void				AddRef();
		void				Release();
		
		ulong*				GetBits(DeviceImage* theImage);
		HDC					GetDC();
		void				ReleaseDC(HDC theDC);
		
		void				SetSurface(void* theSurface);
		void				GetDimensions(int* theWidth, int* theHeight);

		HRESULT				Blt(RECT* theDestRect, void* theSurface, RECT* theSrcRect, DWORD theFlags, DDBLTFX* theBltFx);
	};
}

#endif // #ifndef DXSURFACE8_H
