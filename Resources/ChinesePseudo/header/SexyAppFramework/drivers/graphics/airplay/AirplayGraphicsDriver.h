#ifndef AIRPLAYGRAPHICSDRIVER_H_INCLUDED
#define AIRPLAYGRAPHICSDRIVER_H_INCLUDED

#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"


#include "drivers/app/Airplay/AirplayAppDriver.h"

#include "drivers/graphics/Airplay/AirplayGL11RenderDevice.h"
//#include "drivers/graphics/Airplay/AirplayGL20RenderDevice.h"


namespace Sexy
{
	class SexyAppBase;
	class IAppDriver;
	class AirplayGraphicsDriver;
	
	
	
	
	class AirplayGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		RenderDevice3D* mRenderDeviceES11;
		RenderDevice3D* mRenderDeviceES20;
		
		AirplayGraphicsDriver(AirplayAppDriver*,SexyAppBase*);
		virtual ~AirplayGraphicsDriver();
		
		bool							Is3D();
		
		int								GetVersion();
		
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
		
		DeviceImage*					GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		
		DeviceImage*					GetImageFromResStream(const std::string& theFileName, void* theTextureBacking,ResStreamFileGPULocationInfo* locationInfo);
		
		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);
		
		virtual void					AddMesh(Mesh* theMesh);
		
		virtual void					RemoveMesh(Mesh* theMesh);

#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
#endif
		void Init();
		
		void SetRotationForDeviceOrientation( float theRot );
		
		AirplayAppDriver*	mAppDriver;
		SexyAppBase*		mApp;
	protected:
		friend class		AirplayAppDriver;
		friend class		GLStateManager;
		
		ERenderMode			mRenderMode;
		ulong				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif
		
		
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
		
	};
	
	
};

#endif

