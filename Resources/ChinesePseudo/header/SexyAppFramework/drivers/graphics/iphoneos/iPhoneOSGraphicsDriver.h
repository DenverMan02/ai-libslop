#ifndef IPHONEOSGRAPHICSDRIVER_H_INCLUDED
#define IPHONEOSGRAPHICSDRIVER_H_INCLUDED

#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"


#include "drivers/app/iphoneos/iPhoneOSAppDriver.h"
#include "drivers/graphics/iphoneos/iPhoneOSGL20RenderDevice.h"
#include "drivers/graphics/BaseRenderDevice.h"

namespace Sexy
{
	class SexyAppBase;
	class IAppDriver;
	class iPhoneOSGraphicsDriver;

	class iPhoneOSGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		RenderDevice3D* mRenderDeviceES20;

		iPhoneOSGraphicsDriver(){}
		iPhoneOSGraphicsDriver(iPhoneOSAppDriver*,SexyAppBase*);
		virtual ~iPhoneOSGraphicsDriver();

		virtual bool					Is3D();

		virtual int						GetVersion();

		virtual uint32					GetRenderModeFlags();

		virtual void					SetRenderModeFlags(uint32);

		virtual ERenderMode				GetRenderMode();

		virtual void					SetRenderMode(ERenderMode inRenderMode);

		virtual std::string				GetRenderModeString(ERenderMode inRenderMode,
															uint32 inRenderModeFlags,
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

		virtual RenderEffectDefinition*	CreateRenderEffectDefinition(uint32 theDataLen, const void* theData, const char* theSrc);

		virtual DeviceSurface*			CreateDeviceSurface();

		virtual NativeDisplay*			GetNativeDisplayInfo();

		virtual RenderDevice*			GetRenderDevice();

		virtual RenderDevice3D*			GetRenderDevice3D();

		virtual Ratio					GetAspectRatio();

		virtual int						GetDisplayWidth();

		virtual	int						GetDisplayHeight();

		virtual CritSect&				GetCritSect();

		DeviceImage*					GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);

		DeviceImage*					GetOptimizedImage(ImageLib::Image *image, bool commitBits, bool allowTriReps, bool inShouldDeleteSrcImage);

		DeviceImage*					GetImageFromResStream(const std::string& theFileName, void* theTextureRes, void* theTextureResMulti, ResStreamFileGPULocationInfo* locationInfo);

		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);

		virtual void					AddMesh(Mesh* theMesh);

		virtual void					RemoveMesh(Mesh* theMesh);

		virtual void					DetermineScreenImageType();

        void OnDrawStart();


#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
		void DisableMetrics();
		void EnableMetrics();
#endif
		virtual void Init(UI_ORIENTATION theOrientation);
        void ReInitForDeviceRotation(UI_ORIENTATION theNewOrientation);

		void SetRotationForDeviceOrientation( float theRot );

		iPhoneOSAppDriver*	mAppDriver;
		SexyAppBase*		mApp;
	protected:
		friend class		iPhoneOSAppDriver;
		friend class		GLStateManager;

		ERenderMode			mRenderMode;
		uint32				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif


		int					mWidth;
		int					mHeight;

		int					mCursorX;
		int					mCursorY;

		CritSect			mCritSect;

		HRenderContext		mCurrentContext;

		DeviceImage*		mScreenImage;

		DeviceImage*		mScreenImageForSwaps;

	};


};

#endif
