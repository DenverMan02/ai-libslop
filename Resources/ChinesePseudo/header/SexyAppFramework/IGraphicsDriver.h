#pragma once
#ifndef IGRAPHICSDRIVER_H_INCLUDED
#define IGRAPHICSDRIVER_H_INCLUDED


#include "CritSect.h"
#include "Ratio.h"
#include "Mesh.h"


namespace Sexy
{
	class SexyAppBase;
	class GraphicsMetrics;
	class DeviceImage;
	class DeviceSurface;
	class NativeDisplay;


	/**
	 * I'm intending for this to be a replacement for DDInterface for prime.
	 */
	class IGraphicsDriver 
	{
	public:
		//there is no static create for this, because creation the graphics driver
		//should be done by the AppDriver for the platform

		enum EResult
		{
			RESULT_OK					= 0,
			RESULT_FAIL					= 1,
			RESULT_DD_CREATE_FAIL		= 2,
			RESULT_SURFACE_FAIL			= 3,
			RESULT_EXCLUSIVE_FAIL		= 4,
			RESULT_DISPCHANGE_FAIL		= 5,
			RESULT_INVALID_COLORDEPTH	= 6,
			RESULT_3D_FAIL				= 7,
			RESULT_3D_NOTREADY			= 8,
		};

		enum ERenderMode
		{
			RENDERMODE_Default=0,
			RENDERMODE_Overdraw,
			RENDERMODE_PseudoOverdraw,
			RENDERMODE_BatchSize,
			RENDERMODE_Wireframe,
			RENDERMODE_WastedOverdraw,
			RENDERMODE_TextureHash,
			
			RENDERMODE_OverdrawExact,

			RENDERMODE_COUNT,
			RENDERMODE_CYCLE_END=RENDERMODE_OverdrawExact
		};
		enum ERenderModeFlags
		{
			RENDERMODEF_NoBatching		= (1 << 0), // force batching to be disabled
			RENDERMODEF_HalfTris		= (1 << 1), // draw only half the number of requested tris (used to narrow between batch vs. tri/fill bottlenecks)
			RENDERMODEF_NoDynVB			= (1 << 2), // skip usage of low-level dynamic vertex buffer; use DrawPrimitiveUP instead
			RENDERMODEF_PreventLag		= (1 << 3), // attempt to prevent cursor lag by using a ping-pong rendertarget sync (at the cost of a bit of framerate)
			RENDERMODEF_NoTriRep		= (1 << 4), // don't use the tri-rep optimization (which reduces overdraw at the cost of additional geometry processing)
			RENDERMODEF_NoStretchRectFromTextures = (1 << 5), // don't use StretchRect from textures, even if hardware allows it
			RENDERMODEF_HalfPresent     = (1 << 6), // call D3D Present() with a smaller rectangle; used for tracking down certain driver bugs
		
			
			RENDERMODEF_USEDBITS		= 7
		};


		virtual							~IGraphicsDriver() {};

		virtual bool					Is3D() = 0;

		/**
		 * Returns the current internal version number of the initialized graphics system
		 * For instance DirectX could return 7,8, or 9... 
		 * Don't use the number alone to make any decisions as different platforms will
		 * have arbitrary versioning schemes -- it should only be used to compare against
		 * other versioned graphics systems like DeviceSurfaces
		 */
		virtual	int						GetVersion() = 0;

		virtual uint32					GetRenderModeFlags() = 0;

		virtual void					SetRenderModeFlags(uint32) = 0;

		virtual ERenderMode				GetRenderMode() = 0;

		virtual void					SetRenderMode(ERenderMode inRenderMode) = 0;

		virtual std::string				GetRenderModeString(ERenderMode inRenderMode,
															uint32 inRenderModeFlags,
															bool inIgnoreMode=false,
															bool inIgnoreFlags=false) = 0;
		
		virtual void					AddDeviceImage(DeviceImage* theDDImage) = 0;

		virtual void					RemoveDeviceImage(DeviceImage* theDDImage) = 0;

		virtual void					Remove3DData(MemoryImage* theImage) = 0; 

		virtual DeviceImage*			GetScreenImage() = 0;

		//virtual int						Init(HWND theWindow, bool IsWindowed) = 0;	

		virtual void					WindowResize(int theWidth, int theHeight) = 0;	

		virtual bool					Redraw(Rect* theClipRect = NULL) = 0;		

		virtual void					RemapMouse(int& theX, int& theY) = 0;

		virtual bool					SetCursorImage(Image* theImage) = 0;

		virtual void					SetCursorPos(int theCursorX, int theCursorY) = 0;
		
		virtual void					RemoveShader(const void* theShader) = 0;

		virtual DeviceSurface*			CreateDeviceSurface() = 0;

		virtual NativeDisplay*			GetNativeDisplayInfo() = 0;

		virtual RenderDevice*			GetRenderDevice() = 0;

		virtual RenderDevice3D*			GetRenderDevice3D() = 0;

		virtual Ratio					GetAspectRatio() = 0;

		virtual int						GetDisplayWidth() = 0;

		virtual	int						GetDisplayHeight() = 0;


		/**
		 * JVW - I'm not certain that I like this method existing,
		 * but many different objects throughout the system need to sync
		 * with the graphics system's CritSect to make sure that it's safe 
		 * to delete something. 
		 */
		virtual CritSect&				GetCritSect() = 0;

		/**
		 * 3D Object support is being added in preparation for Bejeweled.
		 * The 3D Object class has been fixed up for Prime and renamed to 
		 * P3D to match the format name. This returns NULL if the platform 
		 * doesn't yet have loading support for 3D objects.
		 */
		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL) = 0;

		virtual void					AddMesh(Mesh* theMesh) = 0;

		virtual void					RemoveMesh(Mesh* theMesh) = 0;

#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics() = 0;
#endif


		static std::string	ResultToString(int theResult)
		{
			switch (theResult)
			{
			case RESULT_OK:
				return "RESULT_OK";
			case RESULT_FAIL:
				return "RESULT_FAIL";
			case RESULT_DD_CREATE_FAIL:
				return "RESULT_DD_CREATE_FAIL";
			case RESULT_SURFACE_FAIL:
				return "RESULT_SURFACE_FAIL";
			case RESULT_EXCLUSIVE_FAIL:
				return "RESULT_EXCLUSIVE_FAIL";
			case RESULT_DISPCHANGE_FAIL:
				return "RESULT_DISPCHANGE_FAIL";		
			case RESULT_INVALID_COLORDEPTH:
				return "RESULT_INVALID_COLORDEPTH";
			default:
				return "RESULT_UNKNOWN";
			}
		};

	};


};
#endif