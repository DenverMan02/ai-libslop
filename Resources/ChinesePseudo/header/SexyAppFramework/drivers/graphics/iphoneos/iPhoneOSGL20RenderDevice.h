#ifndef IPHONEOSGL20RENDERDEVICE_H_INCLUDED
#define IPHONEOSGL20RENDERDEVICE_H_INCLUDED


#include "RenderDevice.h"
#include "IGraphicsDriver.h"
#include "ResStreamsFormat.h"

namespace Sexy 
{
	RenderDevice3D* CreateGL20RenderDevice(IGraphicsDriver* theDriver);
	void			SetGL20RenderTargetImage(RenderDevice3D* theDevice, Image* theImage);
	void			SetGL20BackbufferImages(iPhoneOSAppDriver* theAppDriver, RenderDevice3D* theDevice, Image* theImage, Image* theSwappableImage);
	void			SetGL20RenderTargetFBO(RenderDevice3D* theDevice, uint32 theFBO);
	void			SetGL20FramebufferSize(RenderDevice3D* theDevice, int theWidth, int theHeight);
	void			SetGL20RenderModeFlags(RenderDevice3D* theDevice, uint32 theFlags);
#ifndef RELEASEFINAL
	void			SetGL20GraphicsMetrics(RenderDevice3D* theDevice, GraphicsMetrics* theMetrics);
#endif
	DeviceImage*	GetGL20ImageFromResStream(RenderDevice3D* theDevice, const std::string& theFileName, void* theTextureRes, void* theTextureResMulti, ResStreamFileGPULocationInfo* locationInfo);
	DeviceImage*	GetGL20OptimizedImage(RenderDevice3D* theDevice, const std::string& theFilename, bool commitBits, bool allowTriReps);
	DeviceImage*	GetGL20OptimizedImage(RenderDevice3D* theDevice, ImageLib::Image *aSrcImage, bool commitBits, bool allowTriReps, bool inShouldDeleteSrcImage, const std::string* theFilename = NULL);
	DeviceImage*	GetGL20ScreenImage(RenderDevice3D* theDevice);
	
	void	GL20BltSwapScreen(RenderDevice3D* theDevice, DeviceImage* theSwapImage, int x, int y, int width, int height);
    // QZY added.
	void	GL20BltSwapScreenStretch(RenderDevice3D* theDevice, DeviceImage* theSwapImage, int x, int y, int width, int height);
	// QZY end.
}

#endif