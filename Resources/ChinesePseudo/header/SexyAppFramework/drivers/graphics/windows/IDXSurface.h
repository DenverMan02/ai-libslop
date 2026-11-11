#ifndef IDXSURFACE_H_INCLUDED
#define IDXSURFACE_H_INCLUDED

#include "Common.h"
#include "DeviceSurface.h"

namespace Sexy
{
	class IDXSurface : public DeviceSurface
	{
	public:
		virtual ~IDXSurface() {}

		virtual HDC				GetDC() = 0;
		virtual void			ReleaseDC(HDC theDC) = 0;

		virtual HRESULT			Blt(RECT* theDestRect, void* theSurface, RECT* theSrcRect, DWORD theFlags, DDBLTFX* theBltFx) = 0;
	};
}

#endif // #ifndef IDXSURFACE_H
