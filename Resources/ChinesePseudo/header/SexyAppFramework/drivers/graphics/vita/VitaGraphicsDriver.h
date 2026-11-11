#ifndef VITAGRAPHICSDRIVER_H_INCLUDED
#define VITAGRAPHICSDRIVER_H_INCLUDED

#include "Mesh.h"
#include "Graphics.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"

#include "ResStreamsFormat.h"

#include "VitaRenderDevice.h"

namespace Sexy
{
	class SexyAppBase;
	class VitaAppDriver;

	/* 	Define the number of back buffers to use with this sample.  Most applications
	should use a value of 2 (double buffering) or 3 (triple buffering).
	*/
	#define DISPLAY_BUFFER_COUNT		2

	
	typedef struct DisplayData
	{
		void *address;
	} DisplayData;


	
	class VitaGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		VitaRenderDevice* mRenderDevice;
		
		VitaGraphicsDriver(VitaAppDriver*,SexyAppBase*);
		virtual ~VitaGraphicsDriver();
		
		bool Is3D();
		int GetVersion();

		virtual ulong GetRenderModeFlags();
		virtual void SetRenderModeFlags(ulong);
		virtual ERenderMode GetRenderMode();
		virtual void SetRenderMode(ERenderMode inRenderMode);
		virtual std::string GetRenderModeString(ERenderMode inRenderMode, ulong inRenderModeFlags, bool inIgnoreMode=false, bool inIgnoreFlags=false);
		virtual void AddDeviceImage(DeviceImage* theDDImage);
		virtual void RemoveDeviceImage(DeviceImage* theDDImage);
		virtual void Remove3DData(MemoryImage* theImage);
		virtual DeviceImage* GetScreenImage();
		virtual void WindowResize(int theWidth, int theHeight);
		virtual bool Redraw(Rect* theClipRect = NULL);
		virtual void RemapMouse(int& theX, int& theY);
		virtual bool SetCursorImage(Image* theImage);
		virtual void SetCursorPos(int theCursorX, int theCursorY);
		virtual void RemoveShader(const void* theShader);
		virtual RenderEffectDefinition* CreateRenderEffectDefinition(ulong theDataLen, const void* theData, const char* theSrc);
		virtual DeviceSurface* CreateDeviceSurface();
		virtual NativeDisplay* GetNativeDisplayInfo();
		virtual RenderDevice* GetRenderDevice();
		virtual RenderDevice3D* GetRenderDevice3D();
		virtual Ratio GetAspectRatio();
		virtual int GetDisplayWidth();
		virtual int GetDisplayHeight();
		virtual CritSect& GetCritSect();
		virtual Mesh* LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);
		virtual void AddMesh(Mesh* theMesh){};
		virtual void RemoveMesh(Mesh* theMesh) {};

		DeviceImage* GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		DeviceImage* GetOptimizedPNGImage(const std::string& theFilename, bool commitBits, bool allowTriReps);
		DeviceImage* GetOptimizedJPGImage(const std::string& theFilename, bool commitBits, bool allowTriReps);

		DeviceImage* GetImageFromResStream(	const std::string& theFileName, 
											void* theTextureBacking,
											ResStreamFileGPULocationInfo* theLocationInfo);



#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
#endif
		bool Init();

	protected:
		void MakeSysCursor();

		// Callback function for displaying a buffer
		static void DisplayCallback(const void *callbackData);


	protected:
		friend class VitaAppDriver;
		friend class VitaStateManager;
		friend class VitaRenderDevice;

		ERenderMode mRenderMode;
		ulong mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics	mGraphicsMetrics;
#endif
		VitaAppDriver* mAppDriver;
		SexyAppBase* mApp;

		int mWidth;
		int mHeight;
		Ratio mAspect;
		int mDesktopWidth;
		int mDesktopHeight;
		Ratio mDesktopAspect;
		int mDisplayWidth;
		int mDisplayHeight;
		Ratio mDisplayAspect;
		bool mIsWidescreen;

		int mCursorX;
		int mCursorY;

		CritSect mCritSect;
		Rect mPresentationRect;

		HRenderContext mCurrentContext;

		DeviceImage* mScreenImage;

		VitaRenderDevice::TextureData* mDoubleBufferTextureData;

		DeviceImage* mDefaultCursor;


		SceGxmContext* mContext;
		SceGxmRenderTarget* mRenderTarget;
		void* mDisplayBufferData[DISPLAY_BUFFER_COUNT];
		SceUID mDisplayBufferUid[DISPLAY_BUFFER_COUNT];
		SceGxmColorSurface mDisplaySurface[DISPLAY_BUFFER_COUNT];
		SceGxmSyncObject* mDisplayBufferSync[DISPLAY_BUFFER_COUNT];
		//SceGxmDisplayQueue* mDisplayQueue;
		uint32 mBackBufferIndex;
		uint32 mFrontBufferIndex;

		SceGxmShaderPatcherId mClearVertexShader;
		SceGxmShaderPatcherId mClearFragmentShader;

		VitaVertex* mScratchVerts;

	};	
};

#endif
