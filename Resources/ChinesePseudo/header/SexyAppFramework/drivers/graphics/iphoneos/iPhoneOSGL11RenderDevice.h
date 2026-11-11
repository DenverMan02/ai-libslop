#ifndef IPHONEOSGL11RENDERDEVICE_H_INCLUDED
#define IPHONEOSGL11RENDERDEVICE_H_INCLUDED

#include "RenderDevice.h"
#include "IGraphicsDriver.h"
#include "ResStreamsFormat.h"
#include "GraphicsMetrics.h"

#ifdef PRIME_FOR_BEJBLITZ
    class ImageLib::Image;
#endif

namespace Sexy
{
		
RenderDevice3D* CreateGL11RenderDevice(IGraphicsDriver* theDriver);
void			SetGL11RenderTargetImage(RenderDevice3D* theDevice, Image* theImage);
void			SetGL11BackbufferImage(iPhoneOSAppDriver* theAppDriver, RenderDevice3D* theDevice, Image* theImage);
void			SetGL11RenderTargetFBO(RenderDevice3D* theDevice, uint32 theFBO);
void			SetGL11FramebufferSize(RenderDevice3D* theDevice, int theWidth, int theHeight);
void			SetGL11RenderModeFlags(RenderDevice3D* theDevice, uint32 theFlags);
#ifndef RELEASEFINAL
void			SetGL11GraphicsMetrics(RenderDevice3D* theDevice, GraphicsMetrics* theMetrics);
#endif
DeviceImage*	GetGL11ImageFromResStream(RenderDevice3D* theDevice, const std::string& theFileName, void* theTextureBacking,ResStreamFileGPULocationInfo* locationInfo);
DeviceImage*	GetGL11OptimizedImage(RenderDevice3D* theDevice, const std::string& theFilename, bool commitBits, bool allowTriReps);
    DeviceImage*	GetGL11OptimizedImage(RenderDevice3D* theDevice, ImageLib::Image *image, bool commitBits, bool allowTriReps, bool inShouldDeleteSrcImage, const std::string* theFilename = NULL);
};

#endif
