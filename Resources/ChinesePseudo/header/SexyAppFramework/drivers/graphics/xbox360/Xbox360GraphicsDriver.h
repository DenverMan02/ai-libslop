#ifndef XBOX360GRAPHICSDRIVER_H_INCLUDED
#define XBOX360GRAPHICSDRIVER_H_INCLUDED

#include "Mesh.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"
#include <d3d9.h>
#include "ResStreamsFormat.h"

#include "Xbox360RenderDevice.h"
#include "drivers/graphics/BaseRenderDevice.h"



namespace Sexy
{
	class SexyAppBase;
	class Xbox360AppDriver;
	struct SexyVertex2DList;
	
	class Xbox360GraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		Xbox360RenderDevice* mRenderDevice;
		
		Xbox360GraphicsDriver(Xbox360AppDriver*,SexyAppBase*);
		virtual ~Xbox360GraphicsDriver();

		bool					Is3D();

		int						GetVersion();

		virtual ulong					GetRenderModeFlags();

		virtual void					SetRenderModeFlags(ulong);

		virtual ERenderMode				GetRenderMode();

		virtual void					SetRenderMode(ERenderMode inRenderMode);

		virtual std::string				GetRenderModeString(ERenderMode inRenderMode, 
			ulong inRenderModeFlags, 
			bool inIgnoreMode=false, 
			bool inIgnoreFlags=false);

		virtual void					AddDeviceImage(DeviceImage* theDDImage);
		
		virtual void					RemoveDeviceImage(DeviceImage* theDDImage);
		
		virtual void					Remove3DData(MemoryImage* theImage); 
		
		virtual DeviceImage*			GetScreenImage();
				
		virtual void					WindowResize(int theWidth, int theHeight);	
		
		virtual bool					Redraw(Rect* theClipRect = NULL);		
		
		virtual void					RemapMouse(int& theX, int& theY);
		
		virtual bool					SetCursorImage(Image* theImage);
		
		virtual void					SetCursorPos(int theCursorX, int theCursorY);
		
		virtual void					RemoveShader(const void* theShader);
		
		virtual RenderEffectDefinition*	CreateRenderEffectDefinition(ulong theDataLen, const void* theData, const char* theSrc);
		
		virtual DeviceSurface*			CreateDeviceSurface();
		
		virtual NativeDisplay*			GetNativeDisplayInfo();
		
		virtual RenderDevice*			GetRenderDevice();
		
		virtual RenderDevice3D*			GetRenderDevice3D();
		
		virtual Ratio					GetAspectRatio();
		
		virtual int						GetDisplayWidth();
		
		virtual	int						GetDisplayHeight();
		
		virtual CritSect&				GetCritSect();
		
		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);

		virtual void					AddMesh(Mesh* theMesh) {};
		virtual void					RemoveMesh(Mesh* theMesh) {};
		
#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
#endif
		bool Init();

		DeviceImage*		GetOptimizedXboxImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		DeviceImage*		GetOptimizedPNGImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		DeviceImage*		GetOptimizedJPGImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		DeviceImage*		GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);

		//the filename here is mainly for debugging
		DeviceImage*		GetImageFromResStream(const std::string& theFileName, void* theTextureBacking,ResStreamFileGPULocationInfo* locationInfo);

		IDirect3DDevice9*	GetD3DDevice();
	protected:
		void				MakeSysCursor();
	protected:
		friend class		Xbox360AppDriver;
		
		ERenderMode			mRenderMode;
		ulong				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif
		Xbox360AppDriver*	mAppDriver;
		SexyAppBase*		mApp;
		
		int					mWidth;
		int					mHeight;
		Ratio				mAspect;
		int					mDesktopWidth;
		int					mDesktopHeight;
		Ratio				mDesktopAspect;
		int					mDisplayWidth;
		int					mDisplayHeight;
		Ratio				mDisplayAspect;
		bool				mIsWidescreen;
		
		
		int					mCursorX;
		int					mCursorY;
	
		CritSect			mCritSect;
		Rect				mPresentationRect;
		
		HRenderContext		mCurrentContext;
		
		DeviceImage*		mScreenImage;

		IDirect3D9*			mDD;
		IDirect3DDevice9*	mDevice;

		
		IDirect3DTexture9*	mDoubleBufferTexture;
		
		DeviceImage*		mDefaultCursor;
		
		
	};
};

#endif
