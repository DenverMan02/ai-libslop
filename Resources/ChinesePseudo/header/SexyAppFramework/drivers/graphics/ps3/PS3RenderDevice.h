#ifndef PS3RENDERDEVICE_H_INCLUDED
#define PS3RENDERDEVICE_H_INCLUDED

#include "Graphics.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"

#include "drivers/misc/ps3/PS3Memory.h"
#include "drivers/graphics/BaseRenderDevice.h"

#include "PS3StateManager.h"

#include <cell/gcm.h>
#include <sysutil/sysutil_sysparam.h>


#define SEXYGCM_ARGB(a,r,g,b)	((uint32)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define SEXYGCM_RGBA(r,g,b,a)	SEXYGCM_ARGB(a,r,g,b)
#define SEXYGCM_XRGB(r,g,b)		SEXYGCM_ARGB(0xff,r,g,b)

#define SEXYGCM_GETRED(color)	((color >> 24) & 0xFF)
#define SEXYGCM_GETGREEN(color)	((color >> 16) & 0xFF)
#define SEXYGCM_GETBLUE(color)	((color >> 8) & 0xFF)
#define SEXYGCM_GETALPHA(color)	((color >> 0) & 0xFF)

enum
{
	PS3_GCM_LABEL_START = 64,
	PS3_GCM_WRITE_LABEL_INDEX = PS3_GCM_LABEL_START,
	PS3_GCM_TRANSFER_FENCE_LABEL_INDEX,
	_NUM_PS3_GCM_LABEL
};

namespace Sexy
{
	static uint8_t MakeGCMFormat(PixelFormat theFormat)
	{
		switch (theFormat)
		{
		case PixelFormat_X8R8G8B8:
		case PixelFormat_A8R8G8B8:
			return CELL_GCM_TEXTURE_A8R8G8B8 | CELL_GCM_TEXTURE_LN;
		default:
			assert(false);
			 return 0xFF;
		}
	}

	struct PS3Vertex : public SexyVertex2D
	{
		PS3Vertex()
		{
		}
		
		PS3Vertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
		{
			x = theX;
			y = theY;
			z = theZ;
			u = theU;
			v = theV;
			color = theColor;
		}
		
		static inline float GetCoord(const PS3Vertex& theVertex, int theCoord)
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
		
		static inline PS3Vertex Interpolate(const PS3Vertex &v1, const PS3Vertex &v2, float t)
		{
			PS3Vertex aVertex = v1;
			aVertex.x = v1.x + t*(v2.x-v1.x);
			aVertex.y = v1.y + t*(v2.y-v1.y);
			aVertex.u = v1.u + t*(v2.u-v1.u);
			aVertex.v = v1.v + t*(v2.v-v1.v);
			if (v1.color!=v2.color)
			{
				int r = (int)SexyMath::Lerp((float)SEXYGCM_GETRED(v1.color), (float)SEXYGCM_GETRED(v2.color), t);
				int g = (int)SexyMath::Lerp((float)SEXYGCM_GETGREEN(v1.color), (float)SEXYGCM_GETGREEN(v2.color), t);
				int b = (int)SexyMath::Lerp((float)SEXYGCM_GETBLUE(v1.color), (float)SEXYGCM_GETBLUE(v2.color), t);
				int a = (int)SexyMath::Lerp((float)SEXYGCM_GETALPHA(v1.color), (float)SEXYGCM_GETALPHA(v2.color), t);
				
				aVertex.color = SEXYGCM_RGBA(r,g,b,a);
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
			return SEXYGCM_RGBA(theRed, theGreen, theBlue, theAlpha);
		}

		static inline uint32 TexCoordOffset()
		{
			return 24;
		}
	};
	
	//looks the same as the D3D version for now,
	class PS3Context
	{
	public:
		Image* mDestImage;
		RenderStateManager::Context mStateContext;
		bool mInitialized;
		mutable PS3Context* mParent; // we track parent/child contexts based on copy-ctor, since state manager contexts have some optimizations for these situations
		mutable std::vector<PS3Context*> mChildren;
		
		PS3Context(Image* inImage)
		: mDestImage(inImage)
		, mInitialized(false)
		, mParent(NULL)
		{}
		
		PS3Context(const PS3Context& inContext)
		: mDestImage(inContext.mDestImage)
		, mStateContext(inContext.mStateContext)
		, mInitialized(true) // because we're copying state from an existing context
		, mParent((PS3Context*)&inContext)
		{
			mParent->mChildren.push_back(this);
		}
		
		~PS3Context()
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

	
	struct PS3ExtraRenderDataInfo
	{
		//this is the pointer to the texture data in local memory
		void *mColorDataLocal;
		void *mDepthDataLocal;

		//for the optimized loader
		bool mLoaded;

		//This is the surface for render targets
		CellGcmSurface *mRenderSurf;

		//this is the id of the current framebuffer (0,1 or -1 if not a display buffer).
		uint8_t	mDisplayBufferId;

		bool mFromRSB;

		PS3ExtraRenderDataInfo()
		{
			mColorDataLocal = NULL;
			mDepthDataLocal = NULL;

			mLoaded = false;

			mRenderSurf = NULL;

			mDisplayBufferId = 0xFF;

			mFromRSB = false;
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	class PS3MeshPiece : public MeshPiece
	{
	public:
		uint32					mSexyVF;
		int						mVertexSize;
		int						mVertexBufferCount;
		int						mIndexBufferCount;

		//vert/index data as loaded from PPU to main memry
		void*					mVertexData;
		void*					mIndexData;

		//vert/index data in localMemory
		void* mVertexBuffer;
		void* mIndexBuffer;

	public:
		PS3MeshPiece();
		virtual ~PS3MeshPiece();
	};

	class PS3RingBuffer
	{
	public:
		PS3RingBuffer();

		void Init( uint32 size );

		void *Alloc(uint32 size);
		void *WaitAlloc(uint32 size);

		bool Contains( const void *pos );

		//marks the portion of the current allocation that was actually used, possibly freeing up anything left over.
		void* MarkUsed( const void *pos, uint32 size );
		void UpdateTail();

		//this blocks until all pending RSX operations have completed
		void WaitForLabels();

	private:
		uint32 mSize;
		uint8 *mBuffer;

		uint8 *mHead;
		uint8 *mLastHead; //this is mainly for debugging... Should be the location of the current batched triangle buffer.
		uint8 *mTail;

		uint32_t mRSXBackLabel;
	};

	class PS3RenderEffect;
	class PS3RenderDevice : public BaseRenderDevice<PS3Vertex,CellGcmTexture*,PS3ExtraRenderDataInfo,PS3RenderDevice>
	{
	public:
		static const bool SUPPORT_HW_CLIP = false;
		static const bool SUPPORT_TRI_REP = false;

		PS3StateManager*	mStateMgr;
		HRenderContext		mCurrentContext;
		Image*				mCurRenderTargetImage;
		CellGcmSurface*		mCurRenderTargetSurface;

		DeviceImage*				mSysImage;

		//single depth buffer memory
		void*				mDepthDataLocal;

		SexyMatrix4 mWorldViewProj;

		PS3RingBuffer mVertexRingBuffer;

		typedef std::map<RenderEffectDefinition*, PS3RenderEffect*> RenderEffectMap;
		RenderEffectMap	mRenderEffects;


		typedef BaseRenderDevice<PS3Vertex,CellGcmTexture*,PS3ExtraRenderDataInfo,PS3RenderDevice> BasePS3RenderDevice;
		typedef BasePS3RenderDevice super;

		PS3RenderDevice(IGraphicsDriver* theDriver);

		virtual ~PS3RenderDevice();

		void Init( int width, int height );

		HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext = HRenderContext((void*)0) );
		
		void DeleteContext(const HRenderContext& theContext);
		
		void SetCurrentContext(const HRenderContext& theContext);
		
		HRenderContext GetCurrentContext() const;
		
		void SetDefaultState(Image* theImage, bool isInScene);

		CellGcmTexture *CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, class super::TextureData* theTexData, struct super::TextureDataPiece* theTexDataPiece);
		
		void ReleaseExtraRenderDataInfo(super::TextureData* theTexData, PS3ExtraRenderDataInfo& theInfo);
		bool PreDraw();
		
		virtual ulong GetCapsFlags();
		virtual bool Flush(ulong inFlushFlags = RenderDevice3D::FLUSHF_CurrentScene);
		
		
		void PushState();
		
		void PopState();
		
		void SetupDrawMode(int theDrawMode);
		
		float GetBltDepth();
		
		void SetTextureDirect(int theStage, CellGcmTexture* theTexture);
		
		void SetBlendState(uint32 theRenderState, uint32 theValue);
		
		void SetTextureLinearFilter(int theStage, bool hasLinearFilter);
		
		void ReleaseTexture(super::TextureData* theTexData, CellGcmTexture*& theTexture);
		
		
		
		void CopyImageToTexture(CellGcmTexture* theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat);
		
		
		
		void DrawPrimitiveInternal(ulong inPrimType, ulong inPrimCount, const void* inVertData, ulong inVertStride, ulong inVertFormat, bool inDoCommit=true);
		void CheckBatchAndCommit();
		
//		void WaitForFlip();
//		void Flip();

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
		
		virtual void SetColorWriteState( bool, bool, bool, bool ){};
		
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
		virtual Image*	SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags);
		virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags) {};
		
		virtual void DrawPrimitiveEx(ulong theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0);
		
		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition);
		
		virtual bool SetRenderTarget(Image* theImage);

		CellGcmSurface *CreateRenderSurface(uint16_t theWidth, uint16_t theHeight, uint32_t pitch, uint8_t colorLocation, uint32_t colorOffset, uint8_t depthLocation, uint32_t depthOffset );

		bool SetRenderTargetSurface(PS3ExtraRenderDataInfo& info);

		Image* SetupAtlasState(int inTextureIndex, Image* inImage);
		void AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, uint32 inFormat, int inStride, int inTexUVOfs);

		void AdjustVertexUVsEx(ulong theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize);

		bool LoadMesh(Sexy::Mesh *theMesh);
		void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true);
	};
}//end namespace Sexy

#endif
