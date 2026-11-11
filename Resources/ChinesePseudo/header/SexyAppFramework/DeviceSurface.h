#ifndef DEVICESURFACE_H_INCLUDED
#define DEVICESURFACE_H_INCLUDED

#include "Common.h"

namespace Sexy
{
	class DeviceImage;

typedef struct _DEVICEPIXELFORMAT
{
    uint32       dwSize;                 // size of structure
    uint32       dwFlags;                // pixel format flags
    uint32       dwFourCC;               // (FOURCC code)
    union
    {
        uint32   dwRGBBitCount;          // how many bits per pixel
        uint32   dwYUVBitCount;          // how many bits per pixel
        uint32   dwZBufferBitDepth;      // how many total bits/pixel in z buffer (including any stencil bits)
        uint32   dwAlphaBitDepth;        // how many bits for alpha channels
        uint32   dwLuminanceBitCount;    // how many bits per pixel
        uint32   dwBumpBitCount;         // how many bits per "buxel", total
        uint32   dwPrivateFormatBitCount;// Bits per pixel of private driver formats. Only valid in texture
                                        // format list and if DDPF_D3DFORMAT is set
    };
    union
    {
        uint32   dwRBitMask;             // mask for red bit
        uint32   dwYBitMask;             // mask for Y bits
        uint32   dwStencilBitDepth;      // how many stencil bits (note: dwZBufferBitDepth-dwStencilBitDepth is total Z-only bits)
        uint32   dwLuminanceBitMask;     // mask for luminance bits
        uint32   dwBumpDuBitMask;        // mask for bump map U delta bits
        uint32   dwOperations;           // DDPF_D3DFORMAT Operations
    };
    union
    {
        uint32   dwGBitMask;             // mask for green bits
        uint32   dwUBitMask;             // mask for U bits
        uint32   dwZBitMask;             // mask for Z bits
        uint32   dwBumpDvBitMask;        // mask for bump map V delta bits
        struct
        {
            uint16    wFlipMSTypes;       // Multisample methods supported via flip for this D3DFORMAT
			uint16	  wBltMSTypes;        // Multisample methods supported via blt for this D3DFORMAT
        } MultiSampleCaps;

    };
    union
    {
        uint32   dwBBitMask;             // mask for blue bits
        uint32   dwVBitMask;             // mask for V bits
        uint32   dwStencilBitMask;       // mask for stencil bits
        uint32   dwBumpLuminanceBitMask; // mask for luminance in bump map
    };
    union
    {
        uint32   dwRGBAlphaBitMask;      // mask for alpha channel
        uint32   dwYUVAlphaBitMask;      // mask for alpha channel
        uint32   dwLuminanceAlphaBitMask;// mask for alpha channel
        uint32   dwRGBZBitMask;          // mask for Z channel
        uint32   dwYUVZBitMask;          // mask for Z channel
    };
} DevicePixelFormat;

typedef struct _DEVICESURFACEDESC
{
    ulong               dwFlags;                // determines what fields are valid
    ulong               dwHeight;               // height of surface to be created
    ulong               dwWidth;                // width of input surface
    ulong				lPitch;                 // distance to start of next line (return value only)
    void*				lpSurface;              // pointer to the associated surface memory
    DevicePixelFormat   ddpfPixelFormat;        // pixel format description of the surface
} DeviceSurfaceDesc;



class DeviceSurface
{
public:
	virtual ~DeviceSurface() {}

	virtual bool			Lock(DeviceSurfaceDesc*) = 0;
	virtual void			Unlock(void*) = 0;

	/**
	 * GetVersion refers to the driver version that this was created under.
	 * For instance DirectX can run in version 7,8, or 9.  OpenGL could 
	 * run using p-buffers or fbos which might be denoted by different versions
	 */
	virtual int				GetVersion() const = 0;

	virtual bool			GenerateDeviceSurface(DeviceImage* theImage) = 0;
	virtual bool			HasSurface() const = 0;
	virtual void*			GetSurfacePtr() const = 0;

	virtual void			AddRef() = 0;
	virtual void			Release() = 0;

	virtual uint32*			GetBits(DeviceImage* theImage) = 0;

	virtual void			SetSurface(void* theSurface) = 0;
	virtual void			GetDimensions(int* theWidth, int* theHeight) = 0;


public:
	uint32					mImageFlags;
};
}

#endif // #ifndef IDXSURFACE_H
