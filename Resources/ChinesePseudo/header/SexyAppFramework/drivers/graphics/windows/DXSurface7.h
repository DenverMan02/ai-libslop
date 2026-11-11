#ifndef DXSURFACE7_H
#define DXSURFACE7_H
#define NOMINMAX

#include <ddraw.h>
#include <d3d.h>
#include "Common.h"
#include "IDXSurface.h"

namespace Sexy
{
	class D3D7Interface;
	class DeviceImage;
	class WindowsGraphicsDriver;
	class DXSurface7 : public IDXSurface
	{
		WindowsGraphicsDriver*		mDriver;
		//D3D7Interface*		mD3DInterface;
		LPDIRECTDRAWSURFACE mSurface;
	public:
		DXSurface7(WindowsGraphicsDriver* theDriver);
		virtual ~DXSurface7();

		virtual int				GetVersion() const { return 7; }

		virtual bool			Lock(DeviceSurfaceDesc* theParam) override;
		virtual void			Unlock(void* theParam);

		virtual bool			GenerateDeviceSurface(DeviceImage* theImage);
		virtual bool			HasSurface() const { return mSurface != NULL; }
		virtual void*			GetSurfacePtr() const { return (void*)mSurface; }

		virtual void			AddRef();
		virtual void			Release();

		virtual ulong*			GetBits(DeviceImage* theImage);
		virtual HDC				GetDC();
		virtual void			ReleaseDC(HDC theDC);

		virtual void			SetSurface(void* theSurface);
		virtual void			GetDimensions(int* theWidth, int* theHeight);

		virtual HRESULT			Blt(RECT* theDestRect, void* theSurface, RECT* theSrcRect, DWORD theFlags, DDBLTFX* theBltFx);
	};
}

#endif // #ifndef DXSURFACE7_H
