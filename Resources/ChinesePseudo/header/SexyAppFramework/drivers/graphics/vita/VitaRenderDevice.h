#ifndef VITARENDERDEVICE_H_INCLUDED
#define VITARENDERDEVICE_H_INCLUDED

#include "Graphics.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"
#include "MemPools.h"
#include "drivers/misc/Vita/VitaMemory.h"
#include "drivers/graphics/BaseRenderDevice.h"

#include "drivers/graphics/vita/VitaStateManager.h"

#include <gxm.h>



#define SEXYGCM_ARGB(a,r,g,b)	((uint32)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((g)&0xff)<<8)|((r)&0xff)))
#define SEXYGCM_RGBA(r,g,b,a)	SEXYGCM_ARGB(a,r,g,b)
#define SEXYGCM_XRGB(r,g,b)		SEXYGCM_ARGB(0xff,r,g,b)

#define SEXYGCM_GETRED(color)	((color >> 0) & 0xFF)
#define SEXYGCM_GETGREEN(color)	((color >> 8) & 0xFF)
#define SEXYGCM_GETBLUE(color)	((color >> 16) & 0xFF)
#define SEXYGCM_GETALPHA(color)	((color >> 24) & 0xFF)

namespace Sexy
{
	class VitaGraphicsDriver;

	static uint32 MakeGXMFormat(PixelFormat theFormat)
	{
		switch (theFormat)
		{
		case PixelFormat_X8R8G8B8:
		case PixelFormat_A8R8G8B8:
			return SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB;
		default:
			DBG_ASSERTE(false);
			 return 0xFF;
		}
	}

	typedef struct ClearVertex 
	{
		float x;
		float y;
	} ClearVertex;


//keep these power of two so that shifts can be used for divides 
	//(when math is kept strictly in fixed point)
	
#define VERTEX_SCALE 16.0f
#define VERTEX_SHIFT 4

	
#define VERTEX_BOUNDS_FLOAT (32700.0f / VERTEX_SCALE)
#define VERTEX_BOUNDS_FIXED (32700)

#define TEXCOORD_SCALE 4096.0f
#define TEXCOORD_SHIFT 12



	struct VitaVertex
	{
		int16 x,y; //,z,rhw;  //for now, no Z
		uint32 color; 
		int16 u,v;

		enum { FVF = SexyVF_PackedFormat|SexyVF_XYZRHW|SexyVF_Diffuse|SexyVF_Tex1 };

		VitaVertex()
		{
		}
		
		VitaVertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
		{
			x = theX<=-VERTEX_BOUNDS_FLOAT?-VERTEX_BOUNDS_FIXED:theX>=VERTEX_BOUNDS_FLOAT?VERTEX_BOUNDS_FIXED:(int16)(theX * VERTEX_SCALE);
			y = theY<=-VERTEX_BOUNDS_FLOAT?-VERTEX_BOUNDS_FIXED:theY>=VERTEX_BOUNDS_FLOAT?VERTEX_BOUNDS_FIXED:(int16)(theY * VERTEX_SCALE);
			//z = theZ;
			u = (int16)(theU * TEXCOORD_SCALE);
			v = (int16)(theV * TEXCOORD_SCALE);
			color = theColor;
		}
		
		static inline float GetCoord(const VitaVertex& theVertex, int theCoord)
		{
			switch (theCoord)
			{
				case 0: return (float)theVertex.x * 1.0f/VERTEX_SCALE;
				case 1: return (float)theVertex.y * 1.0f/VERTEX_SCALE;
				case 2: return 0.0f; //theVertex.z;
				case 3: return (float)theVertex.u * 1.0f/TEXCOORD_SCALE;
				case 4: return (float)theVertex.v * 1.0f/TEXCOORD_SCALE;
				default: return 0;
			}
		}
		
		static inline VitaVertex Interpolate(const VitaVertex &v1, const VitaVertex &v2, float t)
		{
			VitaVertex aVertex = v1;
			//use the same scale interpolator for everything to only take the fconv hit once.
			//need to eval precision still
			int32 VertPct =    (uint32)(t*VERTEX_SCALE);
			//VertPct = (VertPct<0)?0:(Pct>255)?255:Pct;

			aVertex.x = v1.x + ((VertPct*(v2.x-v1.x)) >> VERTEX_SHIFT);
			aVertex.y = v1.y + ((VertPct*(v2.y-v1.y)) >> VERTEX_SHIFT);
			aVertex.u = v1.u + ((VertPct*(v2.u-v1.u)) >> VERTEX_SHIFT);
			aVertex.v = v1.v + ((VertPct*(v2.v-v1.v)) >> VERTEX_SHIFT);
			if (v1.color!=v2.color)
			{
			
				int32 Pct =    (uint32)(t*255.0f);
				Pct = (Pct<0)?0:(Pct>255)?255:Pct;
				
				int32 InvPct = 255-Pct;
				aVertex.color = (((((v1.color & 0xFF000000) >> 24) * InvPct) + (((v2.color & 0xFF000000) >> 24) * Pct) << 16) & 0xFF000000) | 
								(((((v1.color & 0x00FF0000) >> 16) * InvPct) + (((v2.color & 0x00FF0000) >> 16) * Pct) <<  8) & 0x00FF0000 )| 
								(((((v1.color & 0x0000FF00) >>  8) * InvPct) + (((v2.color & 0x0000FF00) >>  8) * Pct)      ) & 0x0000FF00 )|
								(((((v1.color & 0x000000FF) >>  0) * InvPct) + (((v2.color & 0x000000FF) >>  0) * Pct) >>  8) & 0x000000FF );
			}
			
			return aVertex;
		}
		
		inline void SetPosition(float theX, float theY, float theZ)
		{
			//x = theX * VERTEX_SCALE;
			//y = theY * VERTEX_SCALE;
			x = theX<=-VERTEX_BOUNDS_FLOAT?-VERTEX_BOUNDS_FIXED:theX>=VERTEX_BOUNDS_FLOAT?VERTEX_BOUNDS_FIXED:(int16)(theX * VERTEX_SCALE);
			y = theY<=-VERTEX_BOUNDS_FLOAT?-VERTEX_BOUNDS_FIXED:theY>=VERTEX_BOUNDS_FLOAT?VERTEX_BOUNDS_FIXED:(int16)(theY * VERTEX_SCALE);
			//z = theZ;
		}
		
		static inline uint32 PackColor(int theRed, int theGreen, int theBlue, int theAlpha)
		{
			return SEXYGCM_RGBA(theRed, theGreen, theBlue, theAlpha);
		}

		static inline uint32 TexCoordOffset()
		{
			return offsetof(VitaVertex,u);
		}
	};
	
	//looks the same as the D3D version for now,
	class VitaContext
	{
	public:
		Image* mDestImage;
		RenderStateManager::Context mStateContext;
		bool mInitialized;
		mutable VitaContext* mParent; // we track parent/child contexts based on copy-ctor, since state manager contexts have some optimizations for these situations
		mutable std::vector<VitaContext*> mChildren;
		
		VitaContext(Image* inImage)
		: mDestImage(inImage)
		, mInitialized(false)
		, mParent(NULL)
		{}
		
		VitaContext(const VitaContext& inContext)
		: mDestImage(inContext.mDestImage)
		, mStateContext(inContext.mStateContext)
		, mInitialized(true) // because we're copying state from an existing context
		, mParent((VitaContext*)&inContext)
		{
			mParent->mChildren.push_back(this);
		}
		
		~VitaContext()
		{
			// separate from children and parent, if applicable
			
			int aChildCount = mChildren.size();
			for (int iChild=0; iChild<aChildCount; ++iChild)
			{
				DBG_ASSERTE(mChildren[iChild]->mParent == this);
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

	public:
		static SimpleMemPool msPool;
	
		void *operator new( size_t size )
		{
			return msPool.GetMemory(size);
		} 
		
		void operator delete( void * addr)
		{
			msPool.ReturnMemory((uint8*)addr);
		}

	};

	
	
	struct VitaExtraRenderDataInfo
	{
		//this is the pointer to the actual texture data in memory
		void*				mMemData;

		uint32				mStride;
		uint32				mWidth; //duplicated for various rendertarget operations
		uint32				mHeight;

		//for the optimized loader
		bool mLoaded;

		//This is the surface for render targets
		int					mUsageCount;
		std::vector<SceGxmRenderTarget*> mRenderTargets;
		SceGxmColorSurface* mRenderSurf;
		SceUID				mDataUID; //not fully sure what this is for
		bool				mFromRSB;

		VitaExtraRenderDataInfo()
		{
			mMemData = NULL;
			mLoaded = false;
			mFromRSB = false;

			mUsageCount = 0;
			//mRenderTarget = NULL;
			mRenderSurf = NULL;
			mStride = 0;
			mWidth = 0;
			mHeight = 0;
		}
	};

	class VitaTexture
	{
		SceGxmTexture mSysTexture;
		void* mRamLocation;
		void* mVRamLocation; //null if not in vram
		uint32 mStride; // or pitch
		uint32 mWidth;
		uint32 mHeight;
		uint32 mLastUsed;  //don't clear until this notification comes from the GPU
		uint32 mUploadedAt; //notification id
		uint32 mUploading;
	};

	//initial design... 64 megs of GPU memory will be set aside for textures
	//256 megs of CPU memory will exist for textures.
	//The Render Device will maintain a list of Textures that exist along each memory "bucket"
	//the buckets will be divided into 128x128 pixel sized regions for now...
	//when a texture has to be uploaded... the texture manager will look for a location and
	// send a message to the uploader thread to begin uploading.
	// it will be added to the waiting on uploads list.

	// just before a scene end is called, the render device should scan the waiting on uploads list
	// and wait for any uploads from this notification period
	
	class VitaRenderEffect;
	class VitaRenderDevice : public BaseRenderDevice<VitaVertex,SceGxmTexture*,VitaExtraRenderDataInfo,VitaRenderDevice>
	{
	public:
		static const bool SUPPORT_HW_CLIP = false;
		static const bool SUPPORT_TRI_REP = false;
		VitaGraphicsDriver* mVitaGraphicsDriver;
		VitaStateManager*	mStateMgr;
		HRenderContext		mCurrentContext;
		Image*				mCurRenderTargetImage;
		SceGxmColorSurface*	mCurRenderTargetSurface;
		VitaExtraRenderDataInfo*	mCurRenderTargetExtraData;
		RenderSurface*		mSysSurface;

		SceUID				mBatchedTriangleBufferUID;

		uint8*				mTriangleRingBuffer;
		SceUID				mTriangleRingBufferUID;
		uint32				mTriangleRingBufferHead;
		uint32				mTriangleRingBufferSize;
		SceGxmNotification	mRingBufferNotification;

		uint16*				mSequentialIndices; //an index buffer with 0,1,2,3,4,etc...
		SceUID				mSequentialIndicesUID;

		Image*				mSysImage;

		uint32_t			mBatchedVertexBufferOffset;

		bool				mSceGxmInScene;

		std::vector<VitaExtraRenderDataInfo*> mRenderTargetInfoList;
		//just for now since I don't know where these will live yet.
//		uint8				mCurrentFrameBuffer;
//		void*				mFrameBuffer[2];
//		uint32_t			mFrameBufferOffset[2];

		SexyMatrix4 mWorldViewProj;


		typedef std::map<RenderEffectDefinition*, VitaRenderEffect*> RenderEffectMap;
		RenderEffectMap	mRenderEffects;


		typedef BaseRenderDevice<VitaVertex,SceGxmTexture*,VitaExtraRenderDataInfo,VitaRenderDevice> BaseVitaRenderDevice;
		typedef BaseVitaRenderDevice super;

		VitaRenderDevice(IGraphicsDriver* theDriver);

		virtual ~VitaRenderDevice();

		void Init(  );

		void FlushBufferedTriangles();

		HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext);
		
		void DeleteContext(const HRenderContext& theContext);
		
		void SetCurrentContext(const HRenderContext& theContext);
		
		HRenderContext GetCurrentContext() const;
		
		void SetDefaultState(Image* theImage, bool isInScene);

		SceGxmTexture* CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, class super::TextureData* theTexData, struct super::TextureDataPiece* theTexDataPiece);
		
		void ReleaseExtraRenderDataInfo(super::TextureData* theTexData, VitaExtraRenderDataInfo& theInfo);
		bool PreDraw();
		bool PreDrawWithRenderDataInfo( VitaExtraRenderDataInfo* theInfo);
		
		virtual ulong GetCapsFlags();
		virtual bool Flush(ulong inFlushFlags = RenderDevice3D::FLUSHF_CurrentScene);
		
		static void BuildOrthoProjection(	SexyMatrix4 &mat, 
										const float top, 
										const float bottom, 
										const float left, 
										const float right, 
										const float near, 
										const float far);
	
		
		void PushState();
		
		void PopState();
		
		void SetupDrawMode(int theDrawMode);
		
		float GetBltDepth();
		
		void SetTextureDirect(int theStage, SceGxmTexture* theTexture);
		
		void SetBlendState(uint32 theRenderState, uint32 theValue);
		
		void SetTextureLinearFilter(int theStage, bool hasLinearFilter);
		
		void ReleaseTexture(super::TextureData* theTexData, SceGxmTexture*& theTexture);
		
		
		
		void CopyImageToTexture(SceGxmTexture* theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat);
		
		
		
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
		
		virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags) {} ;
		virtual Image*	SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags);
		
		virtual void DrawPrimitiveEx(ulong theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0);
		
		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition);
		
		virtual bool SetRenderTarget(Image* theImage);

		SceGxmColorSurface* CreateRenderSurface(uint16_t theWidth, uint16_t theHeight, uint32_t pitch, uint8_t location, uint32_t offset );

		bool SetRenderTargetSurface(VitaExtraRenderDataInfo& info);
		void SetBackbufferImage(Image* image);

		Image* SetupAtlasState(int inTextureIndex, Image* inImage);
		void AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, uint32 inVertFormat, int inStride, int inTexUVOfs);

		void AdjustVertexUVsEx(ulong theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize);

		void ResetRenderTargets();

		bool LoadMesh(Mesh* theMesh);
	protected:
		uint8*	AllocFromRingBuffer(uint32 theSize);
		uint8*	AllocFromRingBufferWaitForRoom(uint32 theSize);
		void	MarkUsedInRingBuffer(uint32 theSize);
		void	WaitForRingBuffer();

	private:
		/*SceGxmShaderPatcherId	mClearVertexProgramId;
		SceGxmShaderPatcherId	mClearFragmentProgramId;
		SceGxmVertexProgram*	mClearVertexProgram;
		SceGxmFragmentProgram*	mClearFragmentProgram;
		SceUID					mClearVerticesUid;
		SceUID					mClearIndicesUid;
		ClearVertex*			mClearVertices;
		uint16*					mClearIndices;*/

		
	};
}//end namespace Sexy

#endif
