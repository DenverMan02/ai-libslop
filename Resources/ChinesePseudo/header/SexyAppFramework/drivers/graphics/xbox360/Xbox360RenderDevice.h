#ifndef XBOX360RENDERDEVICE_H_INCLUDED
#define XBOX360RENDERDEVICE_H_INCLUDED

#include "drivers/graphics/BaseRenderDevice.h"

#include "drivers/graphics/xbox360/Xbox360StateManager.h"
#include "PakLib/PakInterface.h"

#include "DeviceStateConstants.h"

namespace Sexy
{
#define SEXYDX_ARGB(a,r,g,b) \
((uint32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define SEXYDX_RGBA(r,g,b,a) SEXYDX_ARGB(a,r,g,b)
#define SEXYDX_XRGB(r,g,b)   SEXYDX_ARGB(0xff,r,g,b)

#define SEXYDX_GETALPHA(color)		((color >> 24) & 0xFF)
#define SEXYDX_GETRED(color)			((color >> 16) & 0xFF)
#define SEXYDX_GETGREEN(color)		((color >>  8) & 0xFF)
#define SEXYDX_GETBLUE(color)			((color) & 0xFF)

	class Xbox360RenderEffectDefInfo;
	class Xbox360RenderEffect;
	
	struct Xbox360Vertex : public SexyVertex2D
	{
		Xbox360Vertex()
		{
		}
		
		Xbox360Vertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
		{
			x = theX;
			y = theY;
			z = theZ;
			u = theU;
			v = theV;
			color = theColor;
		}
		
		static inline float GetCoord(const Xbox360Vertex& theVertex, int theCoord)
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
		
		static inline Xbox360Vertex Interpolate(const Xbox360Vertex &v1, const Xbox360Vertex &v2, float t)
		{
			Xbox360Vertex aVertex = v1;
			aVertex.x = v1.x + t*(v2.x-v1.x);
			aVertex.y = v1.y + t*(v2.y-v1.y);
			aVertex.u = v1.u + t*(v2.u-v1.u);
			aVertex.v = v1.v + t*(v2.v-v1.v);
			if (v1.color!=v2.color)
			{
				int r = (int)SexyMath::Lerp((float)SEXYDX_GETRED(v1.color), (float)SEXYDX_GETRED(v2.color), t);
				int g = (int)SexyMath::Lerp((float)SEXYDX_GETGREEN(v1.color), (float)SEXYDX_GETGREEN(v2.color), t);
				int b = (int)SexyMath::Lerp((float)SEXYDX_GETBLUE(v1.color), (float)SEXYDX_GETBLUE(v2.color), t);
				int a = (int)SexyMath::Lerp((float)SEXYDX_GETALPHA(v1.color), (float)SEXYDX_GETALPHA(v2.color), t);
				
				aVertex.color = SEXYDX_RGBA(r,g,b,a);
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
			return SEXYDX_RGBA(theRed, theGreen, theBlue, theAlpha);
		}
		
		static inline uint32 TexCoordOffset()
		{
			return 24;
		}
	};
	
	//looks the same as the D3D version from now,
	class Xbox360Context
	{
	public:
		Image* mDestImage;
		RenderStateManager::Context mStateContext;
		bool mInitialized;
		mutable Xbox360Context* mParent; // we track parent/child contexts based on copy-ctor, since state manager contexts have some optimizations for these situations
		mutable std::vector<Xbox360Context*> mChildren;
		
		Xbox360Context(Image* inImage)
		: mDestImage(inImage)
		, mInitialized(false)
		, mParent(NULL)
		{}
		
		Xbox360Context(const Xbox360Context& inContext)
		: mDestImage(inContext.mDestImage)
		, mStateContext(inContext.mStateContext)
		, mInitialized(true) // because we're copying state from an existing context
		, mParent((Xbox360Context*)&inContext)
		{
			mParent->mChildren.push_back(this);
		}
		
		~Xbox360Context()
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

	
	struct Xbox360ExtraRenderDataInfo
	{
		Xbox360ExtraRenderDataInfo()
		{
			mRenderSurf = NULL;
			mDepthSurf  = NULL;
			mDirty		= false;
			mNumTiles	= 0;
			mResolvedTo	= false;
			mPFile = NULL;
			mFromRSB	= false;
		}
	
		//on 360, these surfaces are very lightweight. 
		//They only describe how memory is layed out in EDRAM
		IDirect3DSurface9*	mRenderSurf;
		IDirect3DSurface9*	mDepthSurf;
		//the surfaces have to be resolved into textures, the dirty flag
		// will keep track of if anything has to be resolved
		bool				mDirty;
		
		int					mNumTiles;
		D3DRECT				mTiles[10];

		bool				mResolvedTo;

		PFILE*				mPFile;

		bool				mFromRSB;
	};

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	class D3DMeshPiece : public MeshPiece
	{
	public:
		DWORD					mSexyVF;
		int						mVertexSize;
		int						mVertexBufferCount;
		int						mIndexBufferCount;
		void*					mVertexData;
		void*					mIndexData;

		IUnknown* mVertexBuffer;
		IUnknown* mIndexBuffer;

	public:
		D3DMeshPiece();
		virtual ~D3DMeshPiece();
	};

	class Xbox360RenderDevice : public BaseRenderDevice<Xbox360Vertex,IDirect3DBaseTexture9*,Xbox360ExtraRenderDataInfo,Xbox360RenderDevice>
	{
		typedef BaseRenderDevice<Xbox360Vertex,IDirect3DBaseTexture9*,Xbox360ExtraRenderDataInfo,Xbox360RenderDevice> super;

	public:
		static const bool SUPPORT_HW_CLIP = false;
		static const bool SUPPORT_TRI_REP = false;

		Xbox360StateManager*		mStateMgr;
		HRenderContext				mCurrentContext;
		Image*						mCurRenderTargetImage;
		IDirect3DSurface9*			mCurRenderTargetSurface;
		RenderSurface*				mSysSurface;

		Image*						mSysImage;
		IDirect3DDevice9*			mDevice;

		typedef std::map<RenderEffectDefinition*, Xbox360RenderEffectDefInfo*> RenderEffectDefInfoMap;
		RenderEffectDefInfoMap	mRenderEffectDefInfo;
		typedef std::map<RenderEffectDefinition*, Xbox360RenderEffect*> RenderEffectMap;
		RenderEffectMap			mRenderEffects;

		IDirect3DVertexDeclaration9 *FVFToVertexDecl( ulong theFVF, D3DVERTEXELEMENT9 *e = NULL );

		typedef std::pair<uint32,IDirect3DVertexDeclaration9*> FVFMapping;
		typedef std::vector<FVFMapping> VertexDeclList;
		VertexDeclList mVertexDecls;

		SexyMatrix4 mWorldViewProj;

		Xbox360RenderDevice(IGraphicsDriver* theDriver);
		virtual ~Xbox360RenderDevice();

		void Init( int mWidth, int mHeight );

		HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext);
		HRenderContext GetCurrentContext() const;
		void DeleteContext(const HRenderContext& theContext);		
		void SetCurrentContext(const HRenderContext& theContext);

		
		void SetDefaultState(Image* theImage, bool isInScene);

		IDirect3DBaseTexture9* CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, class super::TextureData* theTexData, struct super::TextureDataPiece* theTexDataPiece);
		
		void ReleaseExtraRenderDataInfo(super::TextureData* theTexData, Xbox360ExtraRenderDataInfo& theInfo);
		inline bool Xbox360RenderDevice::PreDraw();

		virtual ulong GetCapsFlags();
		virtual bool Flush(ulong inFlushFlags = RenderDevice3D::FLUSHF_CurrentScene);
		
		void PushState();
		void PopState();
		
		void SetupDrawMode(int theDrawMode);
		float GetBltDepth();
		void SetTextureDirect(int theStage, IDirect3DBaseTexture9* theTexture);
		
		void SetRenderState(SEXY3DRSS theRenderState, uint32 theValue);
		void SetD3DRenderState(D3DRENDERSTATETYPE theRenderState, uint32 theValue);

		void SetTransform(ulong theTransformState, const SexyMatrix4* theMatrix);

		void SetTextureLinearFilter(int theStage, bool hasLinearFilter);
		
		void ReleaseTexture(super::TextureData* theTexData, IDirect3DBaseTexture9*& theTexture);
		void CopyImageToTexture(IDirect3DBaseTexture9* theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat);
		
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
		
		virtual void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV);
		
		virtual void SetTextureCoordSource(int inTextureIndex, int inUVComponent, Graphics3D::ETexCoordGen inTexGen = Graphics3D::TEXCOORDGEN_NONE);
		virtual void SetTextureFactor(int inTextureFactor);
		virtual void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ);
		virtual std::string GetInfoString(RenderDevice3D::EInfoString inInfoStr);
		virtual Image*	SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags);
		virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags) {};


		virtual void DrawPrimitiveEx(ulong theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0);

		
		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition);
		virtual bool SetRenderTarget(Image* theImage);
		
		bool SetRenderTargetSurface(Xbox360ExtraRenderDataInfo& info);
		void SetBackbufferImage(Image* image);


		void SetSamplerState(ulong theSampler, ulong theState, ulong theValue);

		Image* SetupAtlasState(int inTextureIndex, Image* inImage);
		void AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, uint32 inVertFormat, int inStride, int inTexUVOfs);

		void AdjustVertexUVsEx(ulong theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize);


		virtual bool LoadMesh(Mesh* theMesh);
		virtual void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true);

		virtual HRESULT InternalCreateVertexBuffer(UINT inLength, bool inIsDynamic, DWORD inFVF, ulong inPool, IUnknown** outVertexBuffer);
		virtual HRESULT InternalCreateIndexBuffer(UINT inLength, ulong inPool, IUnknown** outIndexBuffer);
		virtual HRESULT InternalVertexBufferLock(IUnknown* inVertexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags);
		virtual HRESULT InternalVertexBufferUnlock(IUnknown* inVertexBuffer);
		virtual HRESULT InternalIndexBufferLock(IUnknown* inIndexBuffer, UINT inOffset, UINT inSize, void** outData, DWORD inLockFlags);
		virtual HRESULT InternalIndexBufferUnlock(IUnknown* inIndexBuffer);
		virtual HRESULT InternalDrawIndexedPrimitive(ulong inPrimType, UINT inMinIndex, UINT inNumVertices, UINT inStartIndex, UINT inPrimCount);
		virtual HRESULT InternalSetStreamSource(UINT inStreamNumber, IUnknown* inVertexBuffer, UINT inStride);

	};

}

#endif

