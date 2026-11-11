#ifndef ANDROIDGRAPHICSDRIVER_H_INCLUDED
#define ANDROIDGRAPHICSDRIVER_H_INCLUDED

#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"


//#include "drivers/app/android/AndroidAppDriver.h"

#include "drivers/graphics/BaseRenderDevice.h"

namespace Sexy
{
	class SexyAppBase;
	class IAppDriver;
	class AndroidGraphicsDriver;
	
	
	
	
	class AndroidGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		RenderDevice3D* mRenderDeviceES11;
		RenderDevice3D* mRenderDeviceES20;
		
		AndroidGraphicsDriver(AndroidAppDriver*,SexyAppBase*);
		virtual ~AndroidGraphicsDriver();
		
		bool					Is3D();
		
		int						GetVersion();

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
        DeviceImage*                    GetOptimizedImage(ImageLib::Image *image, bool commitBits, bool allowTriReps, bool shouldDeleteSrcImage);
		
		DeviceImage*					GetImageFromResStream(const std::string& theFileName, void* theTextureData, struct ResStreamFileGPULocationInfo* locationInfo);
		
		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);
		
		virtual void					AddMesh(Mesh* theMesh);
		
		virtual void					RemoveMesh(Mesh* theMesh);
		
		virtual void					DetermineScreenImageType();

		void                            ClearBuffers();
		
#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
		void DisableMetrics();
		void EnableMetrics();
#endif
		void Init(UI_ORIENTATION theOrientation);
//		void ReInitForDeviceRotation( UI_ORIENTATION theNewOrientation );
		void ReinitForSurfaceChange( UI_ORIENTATION theOrientation, int iNewWidth, int iNewHeight, bool bForceReinit = false );
		
		void SetRotationForDeviceOrientation( float theRot );
		
		class AndroidAppDriver*	mAppDriver;
		class SexyAppBase*		mApp;
	protected:
		friend class		AndroidAppDriver;
		friend class		GLStateManager;
		
		ERenderMode			mRenderMode;
		uint32				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif
		
		
		int					mWidth;
		int					mHeight;
        
		// QZY added. Although there are many different width and height, but i cannot tell which one is for what. So, i have to make my own one.
		int 				mDeviceWidth;
		int 				mDeviceHeight;
		// QZY end.
        
        int					mScreenWidth;
        int					mScreenHeight;
		
		int					mCursorX;
		int					mCursorY;
		
		CritSect			mCritSect;
		
		HRenderContext		mCurrentContext;
		
		DeviceImage*		mScreenImage;
		
		DeviceImage*		mScreenImageForSwaps;
		
	};
	
	
};

#endif
