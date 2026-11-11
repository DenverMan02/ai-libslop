#pragma once
#ifndef WINDOWSGRAPHICSDRIVER_H_INCLUDED
#define WINDOWSGRAPHICSDRIVER_H_INCLUDED

///for now the app driver is going to look a lot like sexyappbase
#include "IGraphicsDriver.h"

#include "Common.h"
#include "CritSect.h"
#include "NativeDisplay.h"
#include "Rect.h"
#include "Ratio.h"

#include <d3d9.h>
#include <ddraw.h>


#ifndef RELEASEFINAL
#include "GraphicsMetrics.h"
#endif

namespace Sexy
{

	class SexyAppBase;
	class DeviceImage;
	class Image;
	class MemoryImage;
	class RenderDevice3D;
	class D3DInterface;
	class D3DTester;
	class IDXSurface;
	class RenderEffectDefinition;
	class D3DObject;
	class D3DObjectListener;

	typedef std::set<Mesh*> MeshSet;
	typedef std::set<DeviceImage*> DDImageSet;

	#define MAX_WINDOW_SCALE_BUFFERS 4

	//this extends NativeDisplay only b/c the DDInterface did...
	//there is little reason for other platforms to do the same
	class WindowsGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		WindowsGraphicsDriver(SexyAppBase* base);	
		virtual ~WindowsGraphicsDriver();

		bool InitGraphicsDriver();

		virtual bool					Is3D() override { return mIs3D; };

		virtual	int						GetVersion() override;

		virtual ulong					GetRenderModeFlags() override { return mRenderModeFlags | RENDERMODEF_NoBatching; };

		virtual void					SetRenderModeFlags(ulong flags) override { mRenderModeFlags = flags; };

		virtual ERenderMode				GetRenderMode() override { return mRenderMode; };

		virtual void					SetRenderMode(ERenderMode inRenderMode) override;

		virtual std::string				GetRenderModeString(ERenderMode inRenderMode, 
															ulong inRenderModeFlags, 
															bool inIgnoreMode=false, 
															bool inIgnoreFlags=false) override;
		
		virtual void					AddDeviceImage(DeviceImage* theDDImage) override;

		virtual void					RemoveDeviceImage(DeviceImage* theDDImage) override;

		virtual void					Remove3DData(MemoryImage* theImage) override; 

		virtual DeviceImage*			GetScreenImage() override;

		virtual int						Init(HWND theWindow, bool IsWindowed);	

		virtual void					WindowResize(int theWidth, int theHeight) override;	

		virtual bool					Redraw(Rect* theClipRect = NULL) override;		

		virtual void					RemapMouse(int& theX, int& theY) override;

		virtual bool					SetCursorImage(Image* theImage) override;

		virtual void					SetCursorPos(int theCursorX, int theCursorY) override;
		
		virtual void					RemoveShader(const void* theShader) override { };

		virtual DeviceSurface*			CreateDeviceSurface() override;

		virtual NativeDisplay*			GetNativeDisplayInfo() override;

		virtual CritSect&				GetCritSect() override;

		virtual RenderDevice*			GetRenderDevice() override;

		virtual RenderDevice3D*			GetRenderDevice3D() override;

#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics()	{ return mGraphicsMetrics; };
#endif

		virtual Ratio					GetAspectRatio() { return mAspect; };

		virtual int						GetDisplayWidth() { return mDisplayWidth; };

		virtual	int						GetDisplayHeight() { return mDisplayHeight; };;


		//these are public only for legacy usage, there will be an x-plat solution soon
		bool					IsD3D9() const { return mIsD3D9; }
		bool					IsD3D8() const { return mIsD3D8; }
		bool					IsD3D8Or9() const { return mIsD3D8Or9; }

		CritSect				mCritSect;
	protected:
		SexyAppBase*			mApp;

		ERenderMode				mRenderMode;
		ulong					mRenderModeFlags;

#ifndef RELEASEFINAL
		GraphicsMetrics			mGraphicsMetrics;
#endif
	
		RenderDevice3D*			mRenderDevice3D; // same as mD3DInterface, so only the common render device methods are public
		D3DTester*				mD3DTester;
		bool					mIs3D;
		bool					mWantD3D9;
		bool					mIsD3D9;
		
		bool					mIsD3D8;
		bool					mIsD3D8Or9;

		
		bool					mInRedraw;
		bool					mInRedrawCursor;
		LPDIRECTDRAW			mDD;
		LPDIRECTDRAW7			mDD7;
		LPDIRECTDRAWSURFACE		mPrimarySurface;	
		LPDIRECTDRAWSURFACE		mSecondarySurface;	
		IUnknown*				mDrawSurface;
		IUnknown*				mWindowScaleBuffers[MAX_WINDOW_SCALE_BUFFERS];
		int						mWidth;
		int						mHeight;
		Ratio					mAspect;
		int						mDesktopWidth;
		int						mDesktopHeight;
		Ratio					mDesktopAspect;
		bool					mIsWidescreen;
		int						mDisplayWidth;
		int						mDisplayHeight;
		Ratio					mDisplayAspect;
		float					mFov;
		float					mNearPlane;
		float					mFarPlane;

		Rect					mPresentationRect;
		int						mFullscreenBits;
		DWORD					mRefreshRate;
		DWORD					mMillisecondsPerFrame;
		int						mScanLineFailCount;

		bool					mInitialized;
		HWND					mHWnd;
		bool					mIsWindowed;
		DeviceImage*			mScreenImage;
		DeviceImage*			mSecondarySurfaceImage;
		DDImageSet				mDDImageSet;	
		ulong					mInitCount;

		int						mCursorWidth;
		int						mCursorHeight;
		int						mNextCursorX;
		int						mNextCursorY;
		int						mCursorX;
		int						mCursorY;
		Image*					mCursorImage;
		bool					mHasOldCursorArea;
		LPDIRECTDRAWSURFACE		mOldCursorArea;
		LPDIRECTDRAWSURFACE		mNewCursorArea;
		DeviceImage*			mOldCursorAreaImage;
		DeviceImage*			mNewCursorAreaImage;

		IDXSurface*				mPrimaryDXSurface;		
		
		std::string				mErrorString;
		MeshSet					mMeshSet;

		bool					CopyBitmap(LPDIRECTDRAWSURFACE theSurface, HBITMAP TheBitmap, int theX, int theY, int theWidth, int theHeight);
		ulong					GetColorRef(ulong theRGB);

		void					Cleanup();
		void					CleanupMeshes();
		bool					GotDXError(HRESULT theResult, const char *theContext = "");

		void					RestoreOldCursorAreaFrom(LPDIRECTDRAWSURFACE theSurface, bool adjust);
		void					DrawCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust);
		void					MoveCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust, int theNewCursorX, int theNewCursorY);

		HRESULT					CreateSurface(LPDDSURFACEDESC2 theDesc, IUnknown** theSurface, void*);
		void					ClearSurface(LPDIRECTDRAWSURFACE theSurface);
		bool					Do3DTest(HWND theHWND);	

		Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);
		void					AddMesh(Mesh* theMesh);

		void					RemoveMesh(Mesh* theMesh);

		friend class D3DInterface;
		friend class D3D8Interface;
		friend class D3D9Interface;

		friend class DXSurface7;
		friend class DXSurface8;
		friend class DXSurface9;

		friend class WindowsAppDriver;

		D3DInterface*			mD3DInterface;
	};
};

#endif