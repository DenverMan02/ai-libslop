#ifndef WIIRENDERDEVICE_H_INCLUDED
#define WIIRENDERDEVICE_H_INCLUDED


#include "Graphics.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"

#include "BaseRenderDevice.h"
#include "WiiStateManager.h"

//Wii likes colors packed as RGBA
#define SEXYGX_ARGB(a,r,g,b)	((uint32)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define SEXYGX_RGBA(r,g,b,a)	SEXYGX_ARGB(a,r,g,b)
#define SEXYGX_XRGB(r,g,b)		SEXYGX_ARGB(0xff,r,g,b)

#define SEXYGX_GETRED(color)	((color >> 24) & 0xFF)
#define SEXYGX_GETGREEN(color)	((color >> 16) & 0xFF)
#define SEXYGX_GETBLUE(color)	((color >> 8) & 0xFF)
#define SEXYGX_GETALPHA(color)	((color >> 0) & 0xFF)

namespace Sexy
{
	static GXTexFmt MakeGXFORMAT(PixelFormat theFormat)
	{
		switch (theFormat)
		{
		case PixelFormat_X8R8G8B8:
		case PixelFormat_A8R8G8B8:
			return GX_TF_RGBA8;
//		case PixelFormat_R5G6B5: return GX_TF_RGB565;
		default:
			ASSERT(false);
			 return (GXTexFmt)-1;
		}
	}

	struct WiiVertex : public SexyVertex2D
	{
		WiiVertex()
		{
		}
		
		WiiVertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
		{
			x = theX;
			y = theY;
			z = theZ;
			u = theU;
			v = theV;
			color = theColor;
		}
		
		static inline float GetCoord(const WiiVertex& theVertex, int theCoord)
		{
			switch (theCoord)
			{
				case 0: return theVertex.x;
				case 1: return theVertex.y;
				case 2: return theVertex.z;
				case 3: return theVertex.u;
				case 4: return theVertex.v;
				default: return 0;
			}
		}
		
		static inline WiiVertex Interpolate(const WiiVertex &v1, const WiiVertex &v2, float t)
		{
			WiiVertex aVertex = v1;
			aVertex.x = v1.x + t*(v2.x-v1.x);
			aVertex.y = v1.y + t*(v2.y-v1.y);
			aVertex.u = v1.u + t*(v2.u-v1.u);
			aVertex.v = v1.v + t*(v2.v-v1.v);
			if (v1.color!=v2.color)
			{
				int r = (int)SexyMath::Lerp((float)SEXYGX_GETRED(v1.color), (float)SEXYGX_GETRED(v2.color), t);
				int g = (int)SexyMath::Lerp((float)SEXYGX_GETGREEN(v1.color), (float)SEXYGX_GETGREEN(v2.color), t);
				int b = (int)SexyMath::Lerp((float)SEXYGX_GETBLUE(v1.color), (float)SEXYGX_GETBLUE(v2.color), t);
				int a = (int)SexyMath::Lerp((float)SEXYGX_GETALPHA(v1.color), (float)SEXYGX_GETALPHA(v2.color), t);
				
				aVertex.color = SEXYGX_RGBA(r,g,b,a);
			}
			
			return aVertex;
		}
		
		inline void SetPosition(float theX, float theY, float theZ)
		{
			x = theX;
			y = theY;
			z = theZ;
		}
		
		static inline uint32 PackColor(int theRed, int theGreen, int theBlue, int theAlpha)
		{
			return SEXYGX_RGBA(theRed, theGreen, theBlue, theAlpha);
		}
	};
	
	//looks the same as the D3D version for now,
	class WiiContext
	{
	public:
		Image* mDestImage;
		RenderStateManager::Context mStateContext;
		bool mInitialized;
		mutable WiiContext* mParent; // we track parent/child contexts based on copy-ctor, since state manager contexts have some optimizations for these situations
		mutable std::vector<WiiContext*> mChildren;
		
		WiiContext(Image* inImage)
		: mDestImage(inImage)
		, mInitialized(false)
		, mParent(NULL)
		{}
		
		WiiContext(const WiiContext& inContext)
		: mDestImage(inContext.mDestImage)
		, mStateContext(inContext.mStateContext)
		, mInitialized(true) // because we're copying state from an existing context
		, mParent((WiiContext*)&inContext)
		{
			mParent->mChildren.push_back(this);
		}
		
		~WiiContext()
		{
			// separate from children and parent, if applicable
			
			int aChildCount = mChildren.size();
			for (int iChild=0; iChild<aChildCount; ++iChild)
			{
				assert(mChildren[iChild]->mParent == this);
				mChildren[iChild]->mParent = NULL;
			}
			mChildren.clear();
			
			if (mParent)
			{
				aChildCount = mParent->mChildren.size();
				for (int iChild=0; iChild<aChildCount; ++iChild)
				{
					if (mParent->mChildren[iChild] == this)
					{
						mParent->mChildren.erase(mParent->mChildren.begin()+iChild);
						break;
					}
				}
			}
		}
	};

	
	struct WiiExtraRenderDataInfo
	{
		void *mRenderSurf;
		WiiExtraRenderDataInfo()
		{
			mRenderSurf = NULL;
		}
	};
	
	
	class WiiRenderDevice : public BaseRenderDevice<WiiVertex,GXTexObj*,WiiExtraRenderDataInfo,WiiRenderDevice>
	{
	public:
		static const bool SUPPORT_HW_CLIP = false;
		static const bool SUPPORT_TRI_REP = false;

		WiiStateManager*	mStateMgr;
		HRenderContext		mCurrentContext;
		Image*				mCurRenderTargetImage;
		GXTexObj*			mCurRenderTargetSurface;
		RenderSurface*		mSysSurface;

		Image*				mSysImage;

		GXFifoObj*			mFifoObj;
		void*				mFifoBuffer;

		
		//just for now since I don't know where these will live yet.
		uint8				mCurrentFrameBuffer;
		void*				mFrameBuffer[2];
		
				
		typedef BaseRenderDevice<WiiVertex,GXTexObj*,WiiExtraRenderDataInfo,WiiRenderDevice> BaseWiiRenderDevice;
		typedef BaseWiiRenderDevice super;

		WiiRenderDevice(IGraphicsDriver* theDriver);

		virtual ~WiiRenderDevice();

		void Init( GXRenderModeObj* renderMode );

		HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext);
		
		void DeleteContext(const HRenderContext& theContext);
		
		void SetCurrentContext(const HRenderContext& theContext);
		
		HRenderContext GetCurrentContext() const;
		
		void SetDefaultState(Image* theImage, bool isInScene);
		
		GXTexObj *CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, class super::TextureData* theTexData, struct super::TextureDataPiece* theTexDataPiece);
		
		void ReleaseExtraRenderDataInfo(super::TextureData* theTexData, WiiExtraRenderDataInfo& theInfo);
		bool PreDraw();
		
		virtual ulong GetCapsFlags();
		virtual bool Flush(ulong inFlushFlags = RenderDevice3D::FLUSHF_CurrentScene);
		
		
		void PushState();
		
		void PopState();
		
		void SetupDrawMode(int theDrawMode);
		
		float GetBltDepth();
		
		void SetTextureDirect(int theStage, GXTexObj* theTexture);
		
		void SetRenderState(uint32 theRenderState, uint32 theValue);
		
		void	SetTextureLinearFilter(int theStage, bool hasLinearFilter);
		
		void ReleaseTexture(super::TextureData* theTexData, GXTexObj*& theTexture);
		
		
		
		void CopyImageToTexture(GXTexObj* theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat);
		
		
		
		void DrawPrimitiveInternal(ulong inPrimType, ulong inPrimCount, const void* inVertData, ulong inVertStride, ulong inVertFormat, bool inDoCommit=true);
		void CheckBatchAndCommit();
		
		
		///////////////////////////////////////////////
		// RenderDevice3D Impl
		//////////////////////////////////////////////
		
		
		virtual bool RecoverImageBitsFromRenderData(MemoryImage* inImage);
		virtual int	GetTextureMemorySize(MemoryImage* theImage);
		virtual PixelFormat GetTextureFormat(MemoryImage* theImage);
		virtual void ClearColorBuffer(const Color& inColor = Color::Black);
		virtual void ClearDepthBuffer();
		virtual void SetBltDepth(float inDepth);
		
		virtual void SetDepthState(Graphics3D::ECompareFunc inDepthTestFunc, bool inDepthWriteEnabled);
		virtual void SetAlphaTest(Graphics3D::ECompareFunc inAlphaTestFunc, int inRefAlpha);
		
		virtual void SetWireframe(bool inWireframe);
		
		virtual void SetBlend(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend);
		virtual void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise);
		virtual void SetLightingEnabled(bool inLightingEnabled);
		virtual void SetLightEnabled(int inLightIndex, bool inEnabled);
		virtual void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation);
		virtual void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors);
		virtual void SetGlobalAmbient(const Color& inColor);
		virtual void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1);
		virtual void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1);
		virtual void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f);
		
		virtual void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1);
		
		virtual void SetWorldTransform(const SexyMatrix4* inMatrix);
		virtual void SetViewTransform(const SexyMatrix4* inMatrix);
		virtual void SetProjectionTransform(const SexyMatrix4* inMatrix);
		virtual void SetTextureTransform(int inTextureIndex, const SexyMatrix4* inMatrix, int inNumDimensions = 2);
		
		virtual bool SetTexture(int inTextureIndex, Image* inImage);
		virtual void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV );
		
		virtual void SetTextureCoordSource(int inTextureIndex, int inUVComponent, Graphics3D::ETexCoordGen inTexGen = Graphics3D::TEXCOORDGEN_NONE);
		virtual void SetTextureFactor(int inTextureFactor);

		virtual void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ);
		virtual std::string GetInfoString(RenderDevice3D::EInfoString inInfoStr);
		virtual Image* SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface);
		
		virtual void DrawPrimitiveEx(ulong theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0);
		
		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition);
		
		virtual bool SetRenderTarget(Image* theImage);
		
		bool SetRenderTargetSurface(WiiExtraRenderDataInfo& info);
	};
}//end namespace Sexy



#endif
