#ifndef AIRPLAYGL11RENDERDEVICE_H_INCLUDED
#define AIRPLAYGL11RENDERDEVICE_H_INCLUDED

#include "RenderDevice.h"
#include "IGraphicsDriver.h"
#include "ResStreamsFormat.h"

namespace Sexy 
{
	
	RenderDevice3D* CreateGL11RenderDevice(IGraphicsDriver* theDriver);
	void			SetGL11RenderTargetImage(RenderDevice3D* theDevice, Image* theImage);
	void			SetGL11BackbufferImage(RenderDevice3D* theDevice, Image* theImage);
	void			SetGL11RenderTargetFBO(RenderDevice3D* theDevice, uint32 theFBO);
	void			SetGL11FramebufferSize(RenderDevice3D* theDevice, int theWidth, int theHeight);
	void			SetGL11RenderModeFlags(RenderDevice3D* theDevice, uint32 theFlags);
	DeviceImage*	GetGL11ImageFromResStream(RenderDevice3D* theDevice, const std::string& theFileName, void* theTextureBacking,ResStreamFileGPULocationInfo* locationInfo);
};

#endif