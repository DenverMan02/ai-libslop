#ifndef DXSURFACE9_H
#define DXSURFACE9_H

#define NOMINMAX
#include <d3d9.h>
#include <ddraw.h>
#include "IDXSurface.h"

namespace Sexy
{
	class WindowsGraphicsDriver;
	class D3D9Interface;
	class DXSurface9 : public IDXSurface
	{
		WindowsGraphicsDriver*		mDriver;
		D3D9Interface*				mD3DInterface;
		IDirect3DResource9*			mSurface;
		IDirect3DSurface9*			mTextureSurface;						// _getTexture()->GetSurfaceLevel surface.
		ulong						mSurfaceFormat;
		int							mRedBits, mRedShift, mRedMask;
		int							mGreenBits, mGreenShift, mGreenMask;
		int							mBlueBits, mBlueShift, mBlueMask;
		bool						mIsTexture;

	private:
		inline IDirect3DTexture9* _getTexture() const { return (IDirect3DTexture9*)mSurface; }
		inline IDirect3DSurface9* _getSurface() const { return (IDirect3DSurface9*)mSurface; }

	public:
		DXSurface9(WindowsGraphicsDriver* theDriver);
		virtual ~DXSurface9(void);

		virtual int			GetVersion() const { return 9; }

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

#endif // #ifndef DXSURFACE9_H
