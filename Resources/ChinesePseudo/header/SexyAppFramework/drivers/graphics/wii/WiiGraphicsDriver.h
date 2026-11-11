#ifndef WIIGRAPHICSDRIVER_H_INCLUDED
#define WIIGRAPHICSDRIVER_H_INCLUDED

#include "Mesh.h"
#include "Graphics.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"

#include "ResStreamsFormat.h"

#include "WiiRenderDevice.h"
#include "WiiDebug.h"

namespace Sexy
{
	class SexyAppBase;
	class WiiAppDriver;
	
	class WiiGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		WiiRenderDevice* mRenderDevice;
		
		WiiGraphicsDriver(WiiAppDriver*,SexyAppBase*);
		virtual ~WiiGraphicsDriver();
		
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

		DeviceImage*		GetOptimizedWiiImage(const std::string& theFileName, bool commitBits);
		DeviceImage*		GetOptimizedPNGImage(const std::string& theFileName, bool commitBits);
		DeviceImage*		GetOptimizedJPGImage(const std::string& theFileName, bool commitBits);
		DeviceImage*		GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);

	protected:
		void				MakeSysCursor();
	protected:
		friend class		WiiAppDriver;
		friend class		WiiStateManager;
		friend class		WiiRenderDevice;
		
		ERenderMode			mRenderMode;
		ulong				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif
		WiiAppDriver*		mAppDriver;
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
		DeviceImage*		mDefaultCursor;

		GXRenderModeObj*	mRenderModeObj;

#if defined(WII_SCREENSHOT_ENABLED)	&& !defined(RELEASEFINAL)	
		void *mScreenshotWorkingBuffer;
#endif
	};
	
	
};

#endif
