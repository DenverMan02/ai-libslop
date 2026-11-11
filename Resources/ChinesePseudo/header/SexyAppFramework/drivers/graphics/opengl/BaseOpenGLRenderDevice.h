#ifndef BASEOPENGLRENDERDEVICE_H_INCLUDED
#define BASEOPENGLRENDERDEVICE_H_INCLUDED

/**
 * It's assumed that system OpenGL headers will be
 * included before this header.
 */
#include "SexyAppBase.h"

#include "DeviceStateConstants.h"
#include "drivers/graphics/BaseRenderDevice.h"
#include "RenderStateManager.h"
#include "SexyTime.h"
#include "ResourceManager.h"
#include "GLContext.h"

#include "OpenGlIdRegistry.h"

namespace Sexy
{

	class GLMeshPiece : public MeshPiece
	{
	public:
		uint32					mSexyVF;
		int						mVertexSize;
		int						mVertexBufferCount;
		int						mIndexBufferCount;
		uint8*					mVertexData;
		uint8*					mIndexData;

	public:
		GLMeshPiece() : mSexyVF(0),
						mVertexSize(0),
						mVertexBufferCount(0),
						mIndexBufferCount(0),
						mVertexData(NULL),
						mIndexData(NULL)
		{
		}

		virtual ~GLMeshPiece()
		{
			delete[] mVertexData;
			delete[] mIndexData;
			mVertexData = NULL;
			mIndexData = NULL;
		}
	};

	struct GLExtraRenderDataInfo
	{
		GLExtraRenderDataInfo()
		{
			mFBO = 0;
			mDepth = 0;
			mDeleteFBO = true;
			mFromRSB = false;
		}

		GLuint mFBO;
		GLuint mDepth;
		bool   mDeleteFBO;
		bool   mFromRSB;
	};

	struct GLTexHolder
	{
		GLTexHolder()
		{
			tex = 0;
			src = GL_TEXTURE_2D;
		}

		GLTexHolder(int i)
		{
			tex = i;
			src = GL_TEXTURE_2D;
		}

		GLuint tex;
		GLuint src;

		friend bool operator== (const GLTexHolder&,GLuint i);
		friend bool operator!= (const GLTexHolder&,GLuint i);
	};

	inline bool operator==(const GLTexHolder& tex,GLuint i)
	{
		return tex.tex == i;
	}

	inline bool operator!=(const GLTexHolder& tex,GLuint i)
	{
		return tex.tex != i;
	}


	template <typename VertexT, typename StateMgrT, typename PlatformImplT>
	class BaseOpenGLRenderDevice : public BaseRenderDevice<VertexT,GLTexHolder,GLExtraRenderDataInfo,PlatformImplT>
	{
	public:
		uint8						msTempVertexData[0x8000];

		StateMgrT*					mStateMgr;
		HRenderContext				mCurrentContext;
		Image*						mCurRenderTargetImage;
		GLuint						mCurRenderTargetFBO;
		RenderSurface*				mSysSurface;

		Image*						mSysImage;

		bool						mFlipYCoords;

		uint64						mStartHWCommitId;

		OpenGLIdRegistry	* mTextureRegistry;

		typedef BaseRenderDevice<VertexT,GLTexHolder,GLExtraRenderDataInfo, PlatformImplT> super;

		BaseOpenGLRenderDevice(IGraphicsDriver* theDriver) 
			: super(theDriver)
		{
			super::mPixelOffset = 0.0f;
			super::mDefaultVertexSize = sizeof(VertexT);
			super::mDefaultVertexFVF = VertexT::FVF;
			super::mBatchedTriangleIndex = 0;
			super::mBatchedTriangleSize = 1024;		// 100 = number of sprites that could potentially get sent in a single DrawPrim
			super::mBatchedTriangleBuffer = new VertexT[super::mBatchedTriangleSize];

			//This will probably be a parameter so that we can have different
			//state managers for different GL impls


			mCurRenderTargetImage = NULL;
			mCurRenderTargetFBO = 0;
			mSysImage = NULL;
			mSysSurface = new RenderSurface();
			mSysSurface->mData = 0;

			mFlipYCoords = false;

			mStartHWCommitId = 0; //mStateMgr->GetHardwareCommitId();

#ifdef HOST_ANDROID
			OpenGLIdRegistry::StaticStartup();
#endif
		}

		virtual ~BaseOpenGLRenderDevice()
		{
			delete[] super::mBatchedTriangleBuffer;
#ifdef HOST_ANDROID
			OpenGLIdRegistry::StaticShutdown();
#endif
		}

		/**
		 * The backbuffer image is the image that is used as a render target backdrop
		 * for the whole scene.
		 * This may be disabled on some platforms where it's almost pointless (OpenGL ES 1.1)
		 */
		void SetBackbufferImage(Image* image)
		{
			mSysImage = image;

            if (mSysImage)
			{
				class super::TextureData* aTexData = (class super::TextureData*)mSysImage->GetRenderData();
				mSysSurface->mData = aTexData->mExtraData.mFBO;
			}
			else
			{
				mSysSurface->mData = 0;
			}
		}


		HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext)
		{
			DeviceImage *anImage = theDestImage->AsDeviceImage();
			if (anImage!=NULL)
			{
				if (anImage->HasImageFlag(ImageFlag_RenderTarget))
				{
					GLContext* aContext;
					if (theSourceContext.IsValid())
					{
						// we can't do a useful parent/child relationship unless the parent is the current context
						SetCurrentContext(theSourceContext);

						GLContext* aSourceContext = (GLContext*)theSourceContext.GetPointer();
						aContext = new GLContext(*aSourceContext);
					}
					else
					{
						aContext = new GLContext(anImage);
					}

					return HRenderContext(aContext);
				}
			}

			return HRenderContext();
		}

		void DeleteContext(const HRenderContext& theContext)
		{
			if (!theContext.IsValid())
				return;

			GLContext* aContext = (GLContext*)theContext.GetPointer();

			if (theContext == mCurrentContext)
			{
				// this is the primary reason we track parent/children here; when we delete a child that is the current context,
				// we want to switch to the parent context if available, since there are perf benefits to this (the alternative
				// is going to the null context, which works fine but is wasteful if we only end up then indirectly going to
				// the parent context again shortly after; better to skip a step if we can).

				SetCurrentContext(HRenderContext(aContext->mParent));
			}

			delete aContext;
		}

		void SetCurrentContext(const HRenderContext& theContext)
		{
			if (theContext == mCurrentContext)
			{
#ifdef _DEBUG
				/*GLContext* aDesiredContext = (GLContext*)theContext.GetPointer();
				 GLContext* aCurContext = (GLContext*)mCurrentContext.GetPointer();

				 if (mStateMgr->GetContext() != &aDesiredContext->mStateContext)
				 {
				 assert(false && "we shouldn't be able to reach here");
				 //FlushBufferedTriangles();
				 //mStateMgr->SetContext(&aDesiredContext->mStateContext);
				 }*/
#endif

				return; // no change
			}

			FlushBufferedTriangles(true);

			mCurrentContext = theContext;

			if (!theContext.IsValid())
			{
				SetRenderTarget(NULL);
				mStateMgr->SetContext(NULL);
				return;
			}



			 GLContext* aContext = (GLContext*)theContext.GetPointer();


			 Image* anImage = aContext->mDestImage;
			 MemoryImage* aMemoryImage = anImage ? anImage->AsMemoryImage() : NULL;
			 if (aMemoryImage)
			 SetRenderTarget(aMemoryImage);

			 mStateMgr->SetContext(&aContext->mStateContext);

			static_cast<PlatformImplT*>(this)->SetOrthoMatrix(aMemoryImage);

			 if (!aContext->mInitialized)
			 {
				 SetDefaultState(aMemoryImage, true);
				 mStateMgr->CommitState();

				 aContext->mInitialized = true;
			 }

		}

		HRenderContext GetCurrentContext() const
		{
			return mCurrentContext;
		}

		virtual void SetDefaultState(Image* theImage, bool isInScene)
		{

			//JVW - will use the new Res-independent stuff here soon
			mStateMgr->SetVertexFormat(VertexT::FVF,static_cast<PlatformImplT*>(this)->GetVertexSize(VertexT::FVF));

			int aWidth, aHeight;

			if (theImage)
			{
				aWidth = theImage->mWidth;
				aHeight = theImage->mHeight;
			}
			else
			{
				aWidth = super::mWidth;
				aHeight = super::mHeight;
			}
			//setup default mats...
			//mStateMgr->SetViewport(0,0,aWidth,aHeight,0.0f,1.0f);
			static_cast<PlatformImplT*>(this)->SetOrthoMatrix(theImage);




		}

		bool PreDraw()
		{
			//JVW - I guess I'll have to get this info to the RenderDevice somehow
			//if (mApp->mPhysMinimized)
			//	return false;


			if (!super::mSceneBegun)
			{
				super::mSceneBegun = true;

				//set up an ortho projection?



				glLineWidth(1.0f);

#ifndef	OPENGLES2
				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();

				//glDisable(GL_ALPHA_TEST);
#endif


#ifndef OPENGLES2
				glDisable(GL_NORMALIZE);
				glDisable(GL_LIGHTING);
				glShadeModel(GL_SMOOTH);
				glDisable(GL_COLOR_MATERIAL);
#endif

				//glDepthMask(GL_FALSE);





				RenderStateManager::Context* aStateContext = mStateMgr->GetContext();
				mStateMgr->SetContext(NULL);

				mStateMgr->RevertState();
				mStateMgr->ApplyContextDefaults();

				SetDefaultState(NULL, true);

				mStateMgr->PushState();

				if (!mStateMgr->CommitState())
				{
					mStateMgr->SetContext(aStateContext);
					return false;
				}
			}



			return true;
		}

		virtual uint32 GetCapsFlags()
		{
			return RenderDevice3D::CAPF_ImageRenderTargets;
		}

		virtual bool Flush(uint32 inFlushFlags = RenderDevice3D::FLUSHF_CurrentScene)
		{
			if (inFlushFlags & RenderDevice3D::FLUSHF_CurrentScene)
				inFlushFlags |= RenderDevice3D::FLUSHF_BufferedTris; // implied

			if (inFlushFlags & RenderDevice3D::FLUSHF_BufferedTris)
			{
				FlushBufferedTriangles(true);
			}

            if (inFlushFlags & RenderDevice3D::FLUSHF_BufferedState)
            {
                CheckBatchAndCommit();
            }

			if (inFlushFlags & RenderDevice3D::FLUSHF_CurrentScene)
			{
				if (super::mSceneBegun)
				{
					RenderStateManager::Context* aStateContext = mStateMgr->GetContext();
					mStateMgr->SetContext(NULL);

					mStateMgr->PopState();
					super::mSceneBegun = false;
					mStateMgr->SetContext(aStateContext);
				}
			}
			return true;
		}


		void PushState()
		{
			//super::FlushBufferedTriangles();

			mStateMgr->PushState();
		}

		void PopState()
		{
			//FlushBufferedTriangles();
			mStateMgr->PopState();
		}

		void FlushBufferedTriangles()
		{
			//if (mStartHWCommitId != mStateMgr->GetHardwareCommitId())
			{
				super::FlushBufferedTriangles();
				//mStartHWCommitId = mStateMgr->GetHardwareCommitId();
			}
		}

		void FlushBufferedTriangles(bool force)
		{
			if (force)
			{
				super::FlushBufferedTriangles();
				//mStartHWCommitId = mStateMgr->GetHardwareCommitId();
			}
		}
        
        inline void	SetTextureDirect(int theStage, GLTexHolder theTexture, SexyVector2 theUVScale = SexyVector2(1, 1))
        {
            DBG_ASSERTE(theStage >= 0 && theStage < 8);
            //if (mStateMgr->GetTexture(theStage) != theTexture.tex)
            {
                //	FlushBufferedTriangles();
                mStateMgr->SetTexture(theStage, theTexture.tex, theTexture.src);
                
                //this will go away to a seperate call when the atlas code is merged in
                mStateMgr->SetTextureScale(theStage,theUVScale);
            }
        }

		inline void SetupDrawMode(int theDrawMode)
		{
			Graphics3D::EBlendMode aSrcBlend, aDestBlend;
			mStateMgr->GetBlendOverride(aSrcBlend, aDestBlend);

			if (aSrcBlend == Graphics3D::BLEND_DEFAULT)
				aSrcBlend = Graphics3D::BLEND_SRCALPHA;
			if (aDestBlend == Graphics3D::BLEND_DEFAULT)
				aDestBlend = (theDrawMode == Graphics::DRAWMODE_NORMAL) ? Graphics3D::BLEND_INVSRCALPHA : Graphics3D::BLEND_ONE;

			SetRenderState(SEXY3DRS_SRCBLEND, aSrcBlend);
			SetRenderState(SEXY3DRS_DESTBLEND, aDestBlend);
		}

		Image* SetupAtlasState(int inTextureIndex, Image* inImage)
		{
			if (!inImage)
				return NULL;
#if OPTIMIZE_ANIM_DRAW
			Image::CachedImageAtlasUVInfo & info = inImage->GetCachedAtlasUVInfo();
			Image* atlasImage;
			if(info.IsDirty())
			{
				atlasImage = inImage->mAtlasImage;
			}
			else
			{
				atlasImage = info.GetResult().pAtlasImage;
			}
#else
			Image* atlasImage = inImage->mAtlasImage;
#endif
			if (atlasImage)
			{
#if OPTIMIZE_ANIM_DRAW
				Image::TestValue testvalue;
				testvalue.w = atlasImage->mWidth;
				testvalue.h = atlasImage->mHeight;
				testvalue.asx = inImage->mAtlasStartX;
				testvalue.asy = inImage->mAtlasStartY;
				testvalue.aex = inImage->mAtlasEndX;
				testvalue.aey = inImage->mAtlasEndY;
				info.UpdateData(testvalue);
				if(info.IsDirty())
				{
	                float atlasMaxX = (float)(atlasImage->mWidth);
	                float atlasMaxY = (float)(atlasImage->mHeight);

					// enable atlas state
					float asu = (((float) inImage->mAtlasStartX)) / atlasMaxX;
					float asv = (((float) inImage->mAtlasStartY)) / atlasMaxY;
					float aeu = (((float) inImage->mAtlasEndX)) / atlasMaxX;
					float aev = (((float) inImage->mAtlasEndY)) / atlasMaxY;

					SexyVector2 aBase(asu, asv);
					SexyVector2 aU, aV;
					if (aev < asv)
					{
						// rotated
						aU = SexyVector2(asu, aev) - aBase;
						aV = SexyVector2(aeu, asv) - aBase;
					}
					else
					{
						// normal
						aU = SexyVector2(aeu, asv) - aBase;
						aV = SexyVector2(asu, aev) - aBase;
					}
					mStateMgr->SetAtlasState(inTextureIndex, true, &aBase, &aU, &aV);
					Image::CachedAtlasUVResult result;
					result.aBase = aBase;
					result.aU = aU;
					result.aV = aV;
					result.pAtlasImage = atlasImage;
					info.SaveResult(result);
				}
				else
				{
					const Image::CachedAtlasUVResult & result = info.GetResult();
					mStateMgr->SetAtlasState(inTextureIndex, true, &result.aBase, &result.aU, &result.aV);
				}

#else //#if OPTIMIZE_ANIM_DRAW

                float atlasMaxX = (float)(atlasImage->mWidth);
                float atlasMaxY = (float)(atlasImage->mHeight);
                
				// enable atlas state
				float asu = (((float) inImage->mAtlasStartX)) / atlasMaxX;
				float asv = (((float) inImage->mAtlasStartY)) / atlasMaxY;
				float aeu = (((float) inImage->mAtlasEndX)) / atlasMaxX;
				float aev = (((float) inImage->mAtlasEndY)) / atlasMaxY;

				SexyVector2 aBase(asu, asv);
				SexyVector2 aU, aV;
				if (aev < asv)
				{
					// rotated
					aU = SexyVector2(asu, aev) - aBase;
					aV = SexyVector2(aeu, asv) - aBase;
				}
				else
				{
					// normal
					aU = SexyVector2(aeu, asv) - aBase;
					aV = SexyVector2(asu, aev) - aBase;
				}
				mStateMgr->SetAtlasState(inTextureIndex, true, &aBase, &aU, &aV);
#endif //#if OPTIMIZE_ANIM_DRAW

				return atlasImage;
			}
			else
			{
				// disable atlas state
				mStateMgr->SetAtlasState(inTextureIndex, false);

				return inImage;
			}
		}


		inline float GetBltDepth()
		{
			return mStateMgr->GetBltDepth();
		}

        // Applies a "texture stack".
        //
        // NOTE: This is one step away from implementing a material (or similar metaphor)
        // which contains multiple textures & additional render info.  The primary problem
        // is that effects wrap all drawing code and may (or may not) be overriding the
        // shaders.  With the advent of multitextures we no longer have one default shader.
        //
        void SetTextureStack(GLTexHolder texture0, GLTexHolder texture1, SexyVector2 theUVScale = SexyVector2(1,1))
        {
            SetTextureImmediate(0, texture0, theUVScale);
            
            if (texture1 == NULL)
            {
                // Set Texture slot 1 to be the same.  This is done to maintain compatibility with FX shaders, as
                // they do not currently know how to switch between single/multi.
                texture1 = texture0;
                
                if (mStateMgr->IsDefaultShader())
                    mStateMgr->SetDefaultShader();
            }
            else
            {
                if (mStateMgr->IsDefaultShader())
                    mStateMgr->SetDefaultMultiShader();
            }
            
            SetTextureImmediate(1, texture1, theUVScale);
        }
        
        void SetTextureSingle(int theStage, GLTexHolder texture0, SexyVector2 theUVScale = SexyVector2(1,1))
        {
            SetTextureImmediate(theStage, texture0, theUVScale);

            // Note: Function would need to be updated to work with multi textures
            if (mStateMgr->IsDefaultShader())
                mStateMgr->SetDefaultShader();
        }
        
		inline void	SetTextureImmediate(int theStage, GLTexHolder theTexture, SexyVector2& theUVScale)
		{
			DBG_ASSERTE(theStage >= 0 && theStage < 8);
			//if (mStateMgr->GetTexture(theStage) != theTexture.tex)
			{
				mStateMgr->SetTexture(theStage, theTexture.tex, theTexture.src);
                
				//this will go away to a seperate call when the atlas code is merged in
				mStateMgr->SetTextureScale(theStage,theUVScale);
			}
		}

		inline void SetRenderState(uint32 theRenderState, uint32 theValue)
		{
			//if (mStateMgr->GetRenderState(theRenderState) != theValue)
			{
			//	FlushBufferedTriangles();
				mStateMgr->SetRenderState(theRenderState,theValue);
			}
		}

		void	SetTextureLinearFilter(int theStage, bool hasLinearFilter)
		{
			//if (mStateMgr->GetTextureMagFilter(theStage) != hasLinearFilter ||
			//	mStateMgr->GetTextureMinFilter(theStage) != hasLinearFilter)
			{
			//	FlushBufferedTriangles();
				mStateMgr->SetTextureMinFilter(theStage,hasLinearFilter);
				mStateMgr->SetTextureMagFilter(theStage,hasLinearFilter);
			}
		}



		void ReleaseTexture(class super::TextureData* theTextureData, GLTexHolder& theTexture)
		{
			if (!theTextureData->mExtraData.mFromRSB)
			{
				if (OpenGLIdRegistry::StaticIsTextureIdValid( theTexture.tex ) )
				{
					glDeleteTextures(1, &theTexture.tex);
				}
				OpenGLIdRegistry::StaticUnregisterIds( 1, &theTexture.tex );
				theTexture.tex = 0;

			}
		}

        // (JCE) This was added in order to modify a texture currently rendered.  I didn't see any way to do this
        // using existing code, however there may be some combination of things that allows access to the texture.
        virtual void CopyIntoImage(Image* image, int offsetX, int offsetY, int widthX, int widthY, void* sourceTextureData)
        {
            FlushBufferedTriangles();   // Push the previous triangles as they will reference a texture that is about to change.  CheckBatchAndCommit was skipping these.
			SetTexture(0, NULL);    // Wipe state data
            
			class super::TextureData* aData = (class super::TextureData*)image->GetRenderData();
            
            if (aData == NULL)
                return;
            
            class super::TextureDataPiece* aPiece = &aData->mTextures[0];
            
            glActiveTexture(GL_TEXTURE0);
            glPixelStorei(GL_UNPACK_ALIGNMENT,4);
            glBindTexture(aPiece->mTexture.src, aPiece->mTexture.tex);
#ifdef HOST_ANDROID // HVS_JJK GL_BGRA not available on Android
			glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, widthX, widthY, GL_RGBA, GL_UNSIGNED_BYTE, sourceTextureData);
#else
			glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, widthX, widthY, GL_BGRA, GL_UNSIGNED_BYTE, sourceTextureData);
#endif		
        }


		void CopyImageToTexture(GLTexHolder theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat)
		{
			if (theTexture==0)
				return;

			//strategy here is to alloc  on the stack a chunk of mem that looks like a locked texture
			//(maybe larger sized textures will have to be malloc'd... but I believe that macosx has
			// no fixed stack sizes like windows)



			//in some cases (same format as texture, full size, etc... ) it should
			// be possible to optimize this to just glCopyTexImage2D and not do the CopyImageToLockedRect stuff

			CheckBatchAndCommit();
			SetTexture(0, NULL);
			glBindTexture(theTexture.src, theTexture.tex);

			bool aFormatsMatch = offx==0 && offy==0 && texWidth==theImage->mWidth && texHeight==theImage->mHeight;
			if (!aFormatsMatch)
			{
				int aFormatSize = 4;
				if (theFormat==PixelFormat_Palette8)
					aFormatSize = 1;
				else if (theFormat==PixelFormat_R5G6B5)
					aFormatSize = 2;
				else if (theFormat==PixelFormat_A4R4G4B4)
					aFormatSize = 2;

				int aLockedPitch = texWidth * aFormatSize;

				assert(aFormatSize==4);
				//temp alloc this chunk on the stack...
				//TODO: protections to make sure this doesn't get absurdly big
				void* aLockedBits = malloc(texHeight*aLockedPitch);//alloca(texHeight*aLockedPitch);

				super::CopyImageToLockedRect(aLockedBits, aLockedPitch, theImage, offx, offy, texWidth, texHeight, theFormat);
				glPixelStorei(GL_UNPACK_ALIGNMENT,1);
				GLuint format = GL_RGBA;
#if defined HOST_IPHONEOS || defined HOST_MACOSX
				format = GL_BGRA;
#endif
				glTexImage2D(theTexture.src,0, theTextureFormat,texWidth,texHeight,0,format,GL_UNSIGNED_BYTE,aLockedBits);
				//int err = glGetError();
				//DBG_ASSERT(err==0);

				free(aLockedBits);
			}
			else
			{
				//now upload it to the tex
				//glTexSubImage2D(GL_TEXTURE_2D,0,0,0,offx,offy,texWidth,texHeight);
				//int err = glGetError();
				GLuint format = GL_RGBA;
#if defined HOST_IPHONEOS || defined HOST_MACOSX
				format = GL_BGRA;
#endif

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(theTexture.src, 0, theTextureFormat, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, theImage->GetBits());
				//err = glGetError();
				//DBG_ASSERT(err==0);
			}




		}



		void	DrawPrimitiveInternal(uint32 inPrimType, uint32 inPrimCount, const void* inVertData, uint32 inVertStride, uint32 inVertFormat, bool inDoCommit=true)
		{


			uint8* byte_ptr = (uint8*)inVertData;

#ifndef RELEASEFINAL
			uint64 startTime = SexyPerfTime();
#endif

			if (inDoCommit)
				CheckBatchAndCommit();

#ifndef RELEASEFINAL
			if (super::mMetrics!=NULL)
			{
				super::mMetrics->GetCounter(GraphicsMetrics::CT_TimeSpentInGraphicsAPI).Add(SexyPerfTime()-startTime);
			}
#endif

			DBG_ASSERT(inVertFormat==mStateMgr->GetVertexFormat());
			DBG_ASSERT(inVertStride==mStateMgr->GetVertexSize());



			static_cast<PlatformImplT*>(this)->BindVertexStream(byte_ptr);

			uint32 vertCount = 0;
			if (inPrimType == Graphics3D::PT_TriangleList)
				vertCount = inPrimCount * 3;
			else if ((inPrimType == Graphics3D::PT_TriangleStrip) || (inPrimType == Graphics3D::PT_TriangleFan))
				vertCount = inPrimCount + 2;
			else if (inPrimType == Graphics3D::PT_LineStrip)
				vertCount = inPrimCount + 1;

			if (vertCount!=0)
			{
				GLuint primType = GL_TRIANGLES;
				if (inPrimType == Graphics3D::PT_TriangleList)
				{
					primType = GL_TRIANGLES;
#ifndef RELEASEFINAL
					if (super::mMetrics!=NULL)
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListPrims).Add(inPrimCount);
					}
#endif
				}
				else if (inPrimType == Graphics3D::PT_TriangleStrip)
				{
					primType = GL_TRIANGLE_STRIP;
#ifndef RELEASEFINAL
					if (super::mMetrics!=NULL)
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripPrims).Add(inPrimCount);
					}
#endif
				}
				else if (inPrimType == Graphics3D::PT_TriangleFan)
				{
					primType = GL_TRIANGLE_FAN;
#ifndef RELEASEFINAL
					if (super::mMetrics!=NULL)
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanPrims).Add(inPrimCount);
					}
#endif
				}
				else if (inPrimType == Graphics3D::PT_LineStrip)
				{
					primType = GL_LINE_STRIP;
#ifndef RELEASEFINAL
					if (super::mMetrics!=NULL)
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripPrims).Add(inPrimCount);
					}
#endif
				}

#ifndef RELEASEFINAL
				startTime = SexyPerfTime();
#ifndef OPENGLES2
				//debugging to highlight the textures being drawn with linear
				/*if (mStateMgr->GetTextureMagFilter(0) && mStateMgr->GetTexture(0)!=0)
				{
					glDisableClientState(GL_COLOR_ARRAY);
					glColor4f(1.0f,0.0f,0.0f,1.0f);

				}*/
#endif
#endif
				glDrawArrays(primType, 0, vertCount);

#ifndef RELEASEFINAL
				if (super::mMetrics!=NULL)
				{
					super::mMetrics->GetCounter(GraphicsMetrics::CT_TimeSpentInGraphicsAPI).Add(SexyPerfTime()-startTime);
				}
#endif
			}

			static_cast<PlatformImplT*>(this)->UnbindVertexStream();

		}

		void CheckBatchAndCommit()
		{
			if (super::mSceneBegun && super::mBatchedTriangleIndex > 0)
			{
				if (mStateMgr->WouldCommitState())
					FlushBufferedTriangles();
			}
			mStateMgr->CommitState();
		}

		///////////////////////////////////////////////
		// RenderDevice3D Impl
		//////////////////////////////////////////////


		virtual bool RecoverImageBitsFromRenderData(MemoryImage* inImage, int i_x, int i_y, int i_width, int i_height, int fbo)
		{
			//jvw: may not work on iphone
			//maybe I should bring this up to the mac level
#ifdef HOST_MACOSX
			if (inImage->GetRenderData()==NULL)
				return false;

			if (inImage->HasImageFlag(ImageFlag_CubeMap |ImageFlag_VolumeMap))
				return false;

			class super::TextureData* aData = (class super::TextureData*)inImage->GetRenderData();
			if (aData->mBitsChangedCount != inImage->mBitsChangedCount) //bits have changed since texture was created
				return false;

			SetTexture(0, NULL);

			for (int aPieceRow = 0; aPieceRow < aData->mTexVecHeight; aPieceRow++)
			{
				for (int aPieceCol = 0; aPieceCol < aData->mTexVecWidth; aPieceCol++)
				{
					class super::TextureDataPiece* aPiece = &aData->mTextures[aPieceRow*aData->mTexVecWidth + aPieceCol];

					int offx = aPieceCol*aData->mTexPieceWidth;
					int offy = aPieceRow*aData->mTexPieceHeight;
					int aWidth = min(inImage->mWidth-offx,aPiece->mWidth);
					int aHeight = min(inImage->mHeight-offy,aPiece->mHeight);
//					if (aData->mImageFlags & ImageFlag_RenderTarget)
//					{
//						//this may not actually be different with GL & FBOs
//					}
//					else
					{
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(aPiece->mTexture.src, aPiece->mTexture.tex);

						glPixelStorei(GL_UNPACK_ALIGNMENT,1);
						//glPixelStorei(GL_UNPACK_ROW_LENGTH,inImage->mWidth);
						uint32* anImagePtr = inImage->mBits + offy * inImage->mWidth + offx;

						bool createdTemp = false;
						if (inImage->mWidth != aPiece->mWidth || inImage->mHeight != aPiece->mHeight)
						{
							//have to create a temp, because gl can't deal with this
							createdTemp = true;
							anImagePtr = new uint32[aPiece->mWidth*aPiece->mHeight];
							//glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
						}

						//glReadPixels( offx, offy, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, anImagePtr);
						glGetTexImage(aPiece->mTexture.src, 0, GL_BGRA, GL_UNSIGNED_BYTE,anImagePtr);

						if (createdTemp)
						{
							uint32* imageScan = anImagePtr;
							for (int i=0; i<aHeight; i++)
							{
								uint32* linePtr = inImage->mBits + (offy + i) * inImage->mWidth + offx;
								memcpy(linePtr,imageScan,aWidth*4);
								imageScan += aPiece->mWidth;
							}
							delete[] anImagePtr;

						}



						glPixelStorei(GL_UNPACK_ALIGNMENT,1);
						glBindTexture(aPiece->mTexture.src, 0);
						glDisable(GL_TEXTURE_2D);
					}

				}
			}


			return true;
#else
			if (inImage->GetRenderData()==NULL)
				return false;

			if (inImage->HasImageFlag(ImageFlag_CubeMap |ImageFlag_VolumeMap))
				return false;

			class super::TextureData* aData = (class super::TextureData*)inImage->GetRenderData();
			if (aData->mBitsChangedCount != inImage->mBitsChangedCount) //bits have changed since texture was created
				return false;

			for (int aPieceRow = 0; aPieceRow < aData->mTexVecHeight; aPieceRow++)
			{
				for (int aPieceCol = 0; aPieceCol < aData->mTexVecWidth; aPieceCol++)
				{
					class super::TextureDataPiece* aPiece = &aData->mTextures[aPieceRow*aData->mTexVecWidth + aPieceCol];

					int offx = i_x;//aPieceCol*aData->mTexPieceWidth;
					int offy = i_y;//aPieceRow*aData->mTexPieceHeight;
					int aWidth = i_width;//min(inImage->mWidth-offx,aPiece->mWidth);
					int aHeight = i_height;//min(inImage->mHeight-offy,aPiece->mHeight);

					GLenum err1 = glGetError();

					uint32 * outputBuffer = new uint32[ aWidth * aHeight * 4 ];

					err1 = glGetError();

					glPixelStorei(GL_UNPACK_ALIGNMENT,4);

					err1 = glGetError();

					GLuint tmpFBO = 0;
					glGenFramebuffers( 1, &tmpFBO );

					err1 = glGetError();

//					GLuint colorBuffer = 0;
//					glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, aWidth, aHeight );

					//err1 = glGetError();

					GLenum fbComplete = glCheckFramebufferStatus( GL_FRAMEBUFFER );

					err1 = glGetError();

					glBindTexture( aPiece->mTexture.src, aPiece->mTexture.tex );
					err1 = glGetError();
					glBindFramebuffer(GL_FRAMEBUFFER, tmpFBO );
					err1 = glGetError();

//					GLuint colorBuffer = 0;
//					glGenRenderbuffers(1, &colorBuffer);
//					err1 = glGetError();
//					glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
//					err1 = glGetError();
//					glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, aWidth, aHeight );
//					err1 = glGetError();
//					glBindRenderbuffer(GL_RENDERBUFFER, 0);
//					err1 = glGetError();
//					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);
//					err1 = glGetError();

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, aPiece->mTexture.src, aPiece->mTexture.tex, 0);
					err1 = glGetError();
					fbComplete = glCheckFramebufferStatus( GL_FRAMEBUFFER );

					glReadPixels( offx, offy, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, outputBuffer);
					err1 = glGetError();

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
					err1 = glGetError();

					glBindFramebuffer( GL_FRAMEBUFFER, fbo );

					glDeleteFramebuffers( 1, &tmpFBO );

					inImage->mBits = outputBuffer;
				}
			}



			return true;
#endif
		}

		virtual int	GetTextureMemorySize(MemoryImage* theImage)
		{
			return 0;
		}

		virtual PixelFormat GetTextureFormat(MemoryImage* theImage)
		{
			return PixelFormat_A8R8G8B8;
		}

		virtual void ClearColorBuffer(const Color& inColor = Color::Black)
		{
			FlushBufferedTriangles();
			mStateMgr->PushState();

			uint32_t vX,vY,vWidth,vHeight;
			mStateMgr->GetViewport(vX,vY,vWidth,vHeight);
			if ((vX != 0) ||
				(vY != 0) ||
				(mCurRenderTargetImage!=NULL && ((vWidth!=mCurRenderTargetImage->mWidth) || (vHeight!=mCurRenderTargetImage->mHeight))) ||
				(mCurRenderTargetImage==NULL && ((vWidth!=super::mWidth) || (vHeight != super::mHeight))))
			{
				mStateMgr->SetScissorRectToViewportRect();
			}
			mStateMgr->CommitState(); //b/c of viewport
			glClearColor((float)inColor.GetRed()/255.0f, (float)inColor.GetGreen()/255.0f, (float)inColor.GetBlue()/255.0f, (float)inColor.GetAlpha()/255.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			mStateMgr->PopState();

#ifndef RELEASEFINAL
			if (super::mMetrics!=NULL)
			{
				super::mMetrics->GetCounter(GraphicsMetrics::CT_ClearCalls)++;
			}
#endif
		}

		virtual void ClearDepthBuffer()
		{
			FlushBufferedTriangles();
			mStateMgr->PushState();
			uint32_t vX,vY,vWidth,vHeight;
			mStateMgr->GetViewport(vX,vY,vWidth,vHeight);
			if ((vX != 0) ||
				(vY != 0) ||
				(mCurRenderTargetImage!=NULL && ((vWidth!=mCurRenderTargetImage->mWidth) || (vHeight!=mCurRenderTargetImage->mHeight))) ||
				(mCurRenderTargetImage==NULL && ((vWidth!=super::mWidth) || (vHeight != super::mHeight))))
			{
				mStateMgr->SetScissorRectToViewportRect();
			}
			mStateMgr->SetRenderState(SEXY3DRS_ZWRITEENABLE,1); //OpenGL needs this to clear the depth buffer!!
			mStateMgr->CommitState(); //b/c of viewport
			glClearDepthf(1.0f);
			glClear(GL_DEPTH_BUFFER_BIT);
			mStateMgr->PopState();

#ifndef RELEASEFINAL
			if (super::mMetrics!=NULL)
			{
				super::mMetrics->GetCounter(GraphicsMetrics::CT_ClearCalls)++;
			}
#endif
		}

		virtual void SetBltDepth(float inDepth)
		{
			mStateMgr->SetBltDepth(inDepth);
		}

		virtual void SetDepthState(Graphics3D::ECompareFunc inDepthTestFunc, bool inDepthWriteEnabled)
		{
			SetRenderState(SEXY3DRS_ZENABLE, inDepthWriteEnabled || (inDepthTestFunc != Graphics3D::COMPARE_ALWAYS));
			SetRenderState(SEXY3DRS_ZWRITEENABLE, inDepthWriteEnabled);
			SetRenderState(SEXY3DRS_ZFUNC, inDepthTestFunc);
		}
        
		virtual void SetAlphaTest(Graphics3D::ECompareFunc inAlphaTestFunc, int inRefAlpha)
		{
			SetRenderState(SEXY3DRS_ALPHATESTENABLE, (inAlphaTestFunc != Graphics3D::COMPARE_ALWAYS));
			SetRenderState(SEXY3DRS_ALPHAFUNC, inAlphaTestFunc);
			SetRenderState(SEXY3DRS_ALPHAREF, inRefAlpha);
		}

		virtual void SetColorWriteState(bool inWriteRedEnabled,bool inWriteGreenEnabled,bool inWriteBlueEnabled,bool inWriteAlphaEnabled)
		{
			SetRenderState(SEXY3DRS_COLORWRITEENABLE,	(inWriteRedEnabled?0x08:0x0) |
														(inWriteGreenEnabled?0x04:0x0) |
														(inWriteBlueEnabled?0x02:0x0) |
														(inWriteAlphaEnabled?0x01:0x0));
		}

		virtual void SetWireframe(bool inWireframe)
		{
		}

		virtual void SetBlend(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend)
		{
			mStateMgr->SetBlendOverride(inSrcBlend, inDestBlend);
		}

		virtual void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise)
		{
			mStateMgr->SetBackfaceCulling(inCullClockwise,inCullClockwise);
		}

		virtual void SetLightingEnabled(bool inLightingEnabled)
		{
		}

		virtual void SetLightEnabled(int inLightIndex, bool inEnabled)
		{
		}

		virtual void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation)
		{
		}

		virtual void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors)
		{
		}

		virtual void SetGlobalAmbient(const Color& inColor)
		{
		}

		virtual void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1)
		{
		}

		virtual void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1)
		{
		}

		virtual void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f)
		{
		}

		virtual void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1)
		{
		}

		void SetTransform(uint32 theTransformState, const SexyMatrix4* theMatrix)
		{
			mStateMgr->SetTransform(theTransformState, theMatrix);
		}

		virtual void SetWorldTransform(const SexyMatrix4* inMatrix)
		{
			SexyMatrix4 aTempMat;
			if (!inMatrix)
			{
				aTempMat.LoadIdentity();
				inMatrix = &aTempMat;
			}
			SetTransform(OGL_TRANSFORM_WORLD, inMatrix);
		}

		virtual void SetViewTransform(const SexyMatrix4* inMatrix)
		{
			SexyMatrix4 aTempMat;
			if (!inMatrix)
			{
				aTempMat.LoadIdentity();
				inMatrix = &aTempMat;
			}
			SetTransform(OGL_TRANSFORM_VIEW, inMatrix);
		}

		virtual void SetProjectionTransform(const SexyMatrix4* inMatrix)
		{
			SexyMatrix4 aTempMat;
			if (!inMatrix)
			{
				aTempMat.LoadIdentity();
				inMatrix = &aTempMat;
			}
			SetTransform(OGL_TRANSFORM_PROJECTION, inMatrix);
		}

		virtual void SetTextureTransform(int inTextureIndex, const SexyMatrix4* inMatrix, int inNumDimensions = 2)
		{
		}

		virtual bool SetTexture(int inTextureIndex, Image* inImage)
		{
			if (inImage == NULL)
			{
				static_cast<PlatformImplT*>(this)->SetTextureSingle(inTextureIndex, 0);
				return true;
			}

			inImage = SetupAtlasState(inTextureIndex, inImage);

			MemoryImage* aMemoryImage = inImage->AsMemoryImage();
			if (aMemoryImage == NULL)
				return false;

			if (!super::CreateImageRenderData(aMemoryImage))
				return false;
			class super::TextureData* aTextureData = (class super::TextureData*)aMemoryImage->GetRenderData();

			//TODO: cubemap / volume map stuffs

			GLTexHolder aTexture = aTextureData->mTextures.begin()->mTexture;

      SexyVector2 cUVScale((float) aTextureData->mWidth / (float) aTextureData->mTexPieceWidth,
                           (float) aTextureData->mHeight / (float) aTextureData->mTexPieceHeight);

			static_cast<PlatformImplT*>(this)->SetTextureSingle(inTextureIndex, aTexture, cUVScale);
			return true;
		}

		virtual void SetTextureWrap(int inTextureIndex, bool inWrapU, bool inWrapV)
		{
			//if (mStateMgr->GetTextureUWrap(inTextureIndex) != inWrapU || mStateMgr->GetTextureVWrap(inTextureIndex) != inWrapV)
			{
			//	FlushBufferedTriangles();
				mStateMgr->SetTextureUWrap(inTextureIndex, inWrapU);
				mStateMgr->SetTextureVWrap(inTextureIndex, inWrapV);
			}
		}

		virtual void SetTextureCoordSource(int inTextureIndex, int inUVComponent, Graphics3D::ETexCoordGen inTexGen = Graphics3D::TEXCOORDGEN_NONE)
		{
		}

		virtual void SetTextureFactor(int inTextureFactor)
		{
		}

		virtual void SetViewport(int theX, int theY, int theWidth, int theHeight, float theMinZ, float theMaxZ)
		{
			mStateMgr->SetViewport((uint32)theX,(uint32)theY,(uint32)theWidth,(uint32)theHeight,theMinZ,theMaxZ);

		}


		virtual std::string GetInfoString(RenderDevice3D::EInfoString theInfoString)
		{
			//this should all be handled by the platform drivers
			switch (theInfoString) {
				case RenderDevice3D::INFOSTRING_Adapter:
				{
					std::string theRet = "";
					theRet += std::string("Vendor: ") + (char*)glGetString(GL_VENDOR) + " - ";
					theRet += std::string("Renderer: ") + (char*)glGetString(GL_RENDERER);
					return theRet;
				}
				case RenderDevice3D::INFOSTRING_DrvProductVersion:
					return (char*)glGetString(GL_VERSION);
				case RenderDevice3D::INFOSTRING_DrvProductFeatures:
				{
					const char* theExtensions = (const char*)glGetString(GL_EXTENSIONS);
					std::string theRet = "";
					//TODO: do this better, or not every frame
					if (strstr(theExtensions,"GL_EXT_framebuffer_object")!=0)
					{
						theRet += " FBO";
					}
					if (strstr(theExtensions,"GL_ARB_vertex_shader")!=0)
					{
						theRet += " VERTEXSHADER";
					}
					if (strstr(theExtensions,"GL_ARB_fragment_shader")!=0)
					{
						theRet += " PIXELSHADER";
					}
					if (super::mRenderTargetMustBePow2)
					{
						theRet += " FBO_MUST_BE_POW2";
					}
					if (super::mTextureSizeMustBePow2)
					{
						theRet += " TEX_MUST_BE_POW2";
					}

					{
						char temp[20];
						sprintf(temp, " MAX_TEX=%d",super::mMaxTextureWidth);
						theRet += temp;
					}


					return theRet;
				}

				default:
					break;
			}
			return "";
		}
        
		virtual void	CopyScreenImage(DeviceImage* ioDstImage, uint32 flags)
		{
			DBG_ASSERT(false);
		}

		virtual Image* SwapScreenImage(DeviceImage*& ioSrcImage, RenderSurface*& ioSrcSurface, uint32 flags)
		{
			if (ioSrcImage == NULL)
			{
				DBG_ASSERT(false && "SwapScreenImage requires a non-null source image to work with");
				return NULL;
			}

			// see if we have a source surface; if not, we'll have to make one here from the image
			if (ioSrcSurface == NULL)
			{
				// null out current render target image in order to skip redundancy checking
				mCurRenderTargetImage = NULL;

				// set the render target from the image
				SetRenderTarget(ioSrcImage);

				// this surface is normally only used for redundancy checks; we don't usually hold onto it.
				// however in this case, we'll be providing it back to the caller, who will end up releasing
				// it when they're done, so we need to addref it for them
				//mCurRenderTargetSurface->AddRef();
				ioSrcSurface = new RenderSurface();
				ioSrcSurface->AddRef();
				ioSrcSurface->mData = mCurRenderTargetFBO;

				// it's a new surface, probably filled with garbage, so clear it out
				ClearColorBuffer(Color::FromInt(0xff000000));
			}
			else
			{
				// we already have a surface, so go ahead and use it
				SetRenderTargetFBO(ioSrcSurface->mData);
			}

			// now that we're using this other image as our render target,
			// we'll swap out its surface with the screen image's draw surface.



			// mSurface
			/*void* aTempPtr = mGraphicsDriver->mScreenImage->mSurface;
			mGraphicsDriver->mScreenImage->mSurface = ioSrcImage->mSurface;
			ioSrcImage->mSurface = (DeviceSurface*) aTempPtr;*/

			// render data
			void* aTempPtr;
			aTempPtr = super::mGraphicsDriver->GetScreenImage()->GetRenderData();
			super::mGraphicsDriver->GetScreenImage()->SetRenderData(ioSrcImage->GetRenderData());
			ioSrcImage->SetRenderData(aTempPtr);

			// mDrawSurface
			/*aTempPtr = mGraphicsDriver->mDrawSurface;
			mGraphicsDriver->mDrawSurface = ioSrcSurface;
			ioSrcSurface = (IUnknown*)aTempPtr;*/
			aTempPtr = mSysSurface;
			mSysSurface = ioSrcSurface;
			ioSrcSurface = (RenderSurface*)aTempPtr;

			mCurRenderTargetImage = super::mGraphicsDriver->GetScreenImage();

			return ioSrcImage;
		}

		virtual int GetTexUVOffsetForFVF(uint32 inFVF, uint32 inTextureIndex)
		{
			uint32 result = 0;

			if (inFVF & SexyVF_XYZ)
				result += sizeof(float)*3;
			else if (inFVF & SexyVF_XYZRHW)
				result += sizeof(float)*4;
			if (inFVF & SexyVF_Normal)
				result += sizeof(float)*3;
			if (inFVF & SexyVF_Diffuse)
				result += sizeof(uint32);
			if (inFVF & SexyVF_Specular)
				result += sizeof(uint32);

			int aNumTexCoords = ((inFVF >> 8) & 15);
			for (int iTexCoord=0; iTexCoord<aNumTexCoords; ++iTexCoord)
			{
				if (iTexCoord == inTextureIndex)
					return result;

				int aFlagTcs1 = SexyVF_TexCoordSize1(iTexCoord);
				int aFlagTcs3 = SexyVF_TexCoordSize3(iTexCoord);
				int aFlagTcs4 = SexyVF_TexCoordSize4(iTexCoord);

				if ((inFVF & aFlagTcs1) == aFlagTcs1)
					result += sizeof(float);
				else if ((inFVF & aFlagTcs3) == aFlagTcs3)
					result += sizeof(float)*3;
				else if ((inFVF & aFlagTcs4) == aFlagTcs4)
					result += sizeof(float)*4;
				else
					result += sizeof(float)*2;
			}

			return -1;
		}

		void AdjustVertexUVsEx(uint32 theVertexFormat, SexyVertex* theVertices, int theVertexCount, int theVertexSize)
		{
			int texUVOfs = static_cast<PlatformImplT*>(this)->GetTexUVOffsetForFVF(theVertexFormat, 0);
			if (texUVOfs >= 0)
				static_cast<PlatformImplT*>(this)->AdjustVertsForAtlas(0, theVertices, theVertexCount, theVertexFormat, theVertexSize, texUVOfs);
		}

		virtual void DrawPrimitiveEx(uint32 theVertexFormat, Graphics3D::EPrimitiveType thePrimitiveType, const SexyVertex* theVertices, int thePrimitiveCount, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, uint32 theFlags = 0)
		{
			uint32 aNumVertices = 0;
			if (thePrimitiveType == Graphics3D::PT_TriangleList)
			{
				aNumVertices = thePrimitiveCount * 3;
#ifndef RELEASEFINAL
				if (super::mMetrics!=NULL)
				{
					super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListCalls)++;
					super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListPrims).Add(thePrimitiveCount);
				}
#endif
			}
			else if ((thePrimitiveType == Graphics3D::PT_TriangleStrip) || (thePrimitiveType == Graphics3D::PT_TriangleFan))
			{
				aNumVertices = thePrimitiveCount + 2;

#ifndef RELEASEFINAL				
				if (super::mMetrics!=NULL)
				{
					if (thePrimitiveType == Graphics3D::PT_TriangleStrip)
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripPrims).Add(thePrimitiveCount);
					}
					else
					{
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanCalls)++;
						super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanPrims).Add(thePrimitiveCount);
					}
				}
#endif
			}
			else if (thePrimitiveType == Graphics3D::PT_LineStrip)
			{
				aNumVertices = thePrimitiveCount + 1;

#ifndef RELEASEFINAL
				if (super::mMetrics!=NULL)
				{
					super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripCalls)++;
					super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripPrims).Add(thePrimitiveCount);
				}
#endif
			}
			else if (thePrimitiveType == Graphics3D::PT_LineList)
				aNumVertices = thePrimitiveCount * 2;
			else if (thePrimitiveType == Graphics3D::PT_PointList)
				aNumVertices = thePrimitiveCount;

			if ((aNumVertices == 0) || (thePrimitiveCount == 0))
				return;

			if (!static_cast<PlatformImplT*>(this)->PreDraw())
				return;

			FlushBufferedTriangles();

			mStateMgr->PushState();

			uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);

			SetupDrawMode(theDrawMode);
			SetTextureLinearFilter(0, blend);

			mStateMgr->SetVertexFormat(theVertexFormat,static_cast<PlatformImplT*>(this)->GetVertexSize(theVertexFormat));
			//force 3D mode if the vertex type is not RHW
			mStateMgr->Set3DMode(!(theVertexFormat & SexyVF_XYZRHW));

			//mStateMgr->SetTextureScaling(true);

			mStateMgr->CommitState();


			int aVertexSize = mStateMgr->GetVertexSize();

			uint8* aOrigVertexPtr = (uint8*)theVertices;



			//modify the verts (maybe...)
			uint8* aVertexBuf = aOrigVertexPtr;
			//glDisable(GL_BLEND);
			if (theVertexFormat & SexyVF_XYZRHW)
			{
				//jvw todo: only do nothing if the flag is set that pixel offsets are taken care of
				/*if ((aColor == 0) && (tx == 0) && (ty == 0) && (super::mTransformStack.empty()))
				{
					//do nothing
				}
				else */
				{
					//actually, in OpenGL it should be possible to just push a model transform
					//for the offset (and transformStack) and then set a color for the overall color
					// (and disable the color setting)

					//warn (performance?)
					int aNeedVertexSize = aNumVertices * aVertexSize;
					uint8* aTempVerts = msTempVertexData;
					DBG_ASSERT(aNeedVertexSize < sizeof(msTempVertexData));

					memcpy(aTempVerts,theVertices,aNeedVertexSize);

					SexyVector2 aTexScaleA = mStateMgr->GetTextureScale(0);
					SexyVector2 aTexScaleB = mStateMgr->GetTextureScale(1);


					int texScaleOffset = 0;
					int texScaleOffsetA = 0;
					int texScaleOffsetB = 0;
					if (theVertexFormat & SexyVF_XYZ)
						texScaleOffset += 12;
					if (theVertexFormat & SexyVF_XYZRHW)
						texScaleOffset += 16;
					if (theVertexFormat & SexyVF_Normal)
						texScaleOffset += 12;
					if (theVertexFormat & SexyVF_Diffuse)
						texScaleOffset += 4;
					if (theVertexFormat & SexyVF_Specular)
						texScaleOffset += 4;

					if (theVertexFormat & SexyVF_Tex2)
					{
						texScaleOffsetA = texScaleOffset;
						texScaleOffsetB = texScaleOffset + 8;
					}
					else if (theVertexFormat & SexyVF_Tex1)
					{
						texScaleOffsetA = texScaleOffset;
					}

					uint8* aCurVertexPtr = (uint8*)aTempVerts;
					for (int i=0; i<aNumVertices; i++)
					{
						SexyVertex2D* aVertexRHW = (SexyVertex2D*)aCurVertexPtr;
						aVertexRHW->x += tx + super::mPixelOffset + 0.5f;  //windows games usually pass in -0.5f adjusted verts. this compensates (until there is a flag in use)
						aVertexRHW->y += ty + super::mPixelOffset + 0.5f;

						if (aVertexRHW->color == 0)
							aVertexRHW->color = aColor;
						else
						{
							//flip the r && b channels
							//(Mac / iPhone only?? maybe these should have a BGRA flag)

							aVertexRHW->color = VertexT::PackColor((aVertexRHW->color&0x00FF0000)>>16, (aVertexRHW->color&0x0000FF00)>>8, (aVertexRHW->color&0x000000FF), (aVertexRHW->color&0xFF000000)>>24);
						}

						if (texScaleOffsetA!=0)
						{
							float* f = (float*)(aCurVertexPtr + texScaleOffsetA);
							f[0] *= aTexScaleA.x;
							f[1] *= aTexScaleA.y;
						}
						if (texScaleOffsetB!=0)
						{
							float* f = (float*)(aCurVertexPtr + texScaleOffsetB);
							f[0] *= aTexScaleB.x;
							f[1] *= aTexScaleB.y;
						}


						aCurVertexPtr += aVertexSize;
					}


					if (!super::mTransformStack.empty())
					{

						const SexyMatrix3& aMatrix = super::mTransformStack.back();
						aCurVertexPtr = (uint8*)aTempVerts;
						for (int i=0; i<aNumVertices; i++)
						{
							SexyVector2* aVector = (SexyVector2*)aCurVertexPtr;
							*aVector = aMatrix * *aVector;
							aCurVertexPtr += aVertexSize;
						}

					}

					aVertexBuf = aTempVerts;
				}

			}

			if (!(theFlags & Graphics3D::DPF_NoAdjustUVs))
			{
				//TODO: handle DISCARD flag to do this inline...
				if (aVertexBuf != msTempVertexData)
				{
					uint8* aTempVerts = msTempVertexData;
					int aNeedVertexSize = aNumVertices*aVertexSize;
					DBG_ASSERT(aNeedVertexSize < sizeof(msTempVertexData));

					memcpy(aTempVerts,theVertices,aNeedVertexSize);

					aVertexBuf = aTempVerts;
				}

				int texUVOfs = static_cast<PlatformImplT*>(this)->GetTexUVOffsetForFVF(theVertexFormat, 0);
				if (texUVOfs >= 0)
					static_cast<PlatformImplT*>(this)->AdjustVertsForAtlas(0, (void*)aVertexBuf, aNumVertices, theVertexFormat, aVertexSize, texUVOfs);
			}


			static_cast<PlatformImplT*>(this)->BindVertexStream(aVertexBuf);




			GLuint primType = GL_TRIANGLES;
			if (thePrimitiveType == Graphics3D::PT_TriangleList)
            {
				primType = GL_TRIANGLES;
#ifndef RELEASEFINAL
                if (super::mMetrics!=NULL)
                {
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListCalls)++;
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriListPrims).Add(thePrimitiveCount);
                }
#endif
            }
			else if (thePrimitiveType == Graphics3D::PT_TriangleStrip)
            {
				primType = GL_TRIANGLE_STRIP;
#ifndef RELEASEFINAL
                if (super::mMetrics!=NULL)
                {
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripCalls)++;
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriStripPrims).Add(thePrimitiveCount);
                }
#endif
            }
			else if (thePrimitiveType == Graphics3D::PT_TriangleFan)
            {
				primType = GL_TRIANGLE_FAN;
#ifndef RELEASEFINAL
                if (super::mMetrics!=NULL)
                {
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanCalls)++;
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_TriFanPrims).Add(thePrimitiveCount);
                }
#endif

            }
			else if (thePrimitiveType == Graphics3D::PT_LineStrip)
            {
				primType = GL_LINE_STRIP;
#ifndef RELEASEFINAL
                if (super::mMetrics!=NULL)
                {
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripCalls)++;
                    super::mMetrics->GetCounter(GraphicsMetrics::CT_LineStripPrims).Add(thePrimitiveCount);
                }
#endif

            }
			else if (thePrimitiveType == Graphics3D::PT_LineList)
            {
				primType = GL_LINES;
            }
			else if (thePrimitiveType == Graphics3D::PT_PointList)
				primType = GL_POINTS;

#ifndef RELEASEFINAL
			uint64 startTime =  SexyPerfTime();
#endif

			glDrawArrays(primType, 0, aNumVertices);

			static_cast<PlatformImplT*>(this)->UnbindVertexStream();

#ifndef RELEASEFINAL
			if (super::mMetrics!=NULL)
			{
				super::mMetrics->GetCounter(GraphicsMetrics::CT_TimeSpentInGraphicsAPI).Add(SexyPerfTime()-startTime);

			}
#endif

			mStateMgr->PopState();
		}


		uint32 GetVertexSize(uint32 inFVF)
		{
			uint32 result = 0;
			if (inFVF & SexyVF_XYZ)
				result += sizeof(float)*3;
			else if (inFVF & SexyVF_XYZRHW)
			{
				result += sizeof(float)*4;
			}
			if (inFVF & SexyVF_Normal)
				result += sizeof(float)*3;
			if (inFVF & SexyVF_Diffuse)
				result += sizeof(uint32);
			if (inFVF & SexyVF_Specular)
				result += sizeof(uint32);

			int aNumTexCoords = ((inFVF >> 8) & 15);

			int aTexCoordElementSize = sizeof(float);
			for (int iTexCoord=0; iTexCoord<aNumTexCoords; ++iTexCoord)
			{
				int aFlagTcs1 = SexyVF_TexCoordSize1(iTexCoord);
				int aFlagTcs3 = SexyVF_TexCoordSize3(iTexCoord);
				int aFlagTcs4 = SexyVF_TexCoordSize4(iTexCoord);

				if ((inFVF & aFlagTcs1) == aFlagTcs1)
					result += aTexCoordElementSize;
				else if ((inFVF & aFlagTcs3) == aFlagTcs3)
					result += aTexCoordElementSize*3;
				else if ((inFVF & aFlagTcs4) == aFlagTcs4)
					result += aTexCoordElementSize*4;
				else
					result += aTexCoordElementSize*2;
			}

			return result;
		}

		virtual void BindVertexStream(void* theVertexBuf)
		{
			uint8* aVertexBuf = (uint8*)theVertexBuf;

			uint32 aVertexSize = mStateMgr->GetVertexSize();
#ifndef OPENGLES2
            uint32 aVertexFormat = mStateMgr->GetVertexFormat();

			int offset = 0;
			if (aVertexFormat & SexyVF_XYZ)
			{
				glVertexPointer(3, GL_FLOAT, aVertexSize, aVertexBuf);
				glEnableClientState(GL_VERTEX_ARRAY);
				offset += 12;
			}
			else if (aVertexFormat & SexyVF_XYZRHW)
			{
				glVertexPointer(4, GL_FLOAT, aVertexSize, aVertexBuf);
				glEnableClientState(GL_VERTEX_ARRAY);
				offset += 16;
			}

			if (aVertexFormat & SexyVF_Normal)
			{
				glNormalPointer(GL_FLOAT, aVertexSize, aVertexBuf + offset);
				glEnableClientState(GL_NORMAL_ARRAY);
				offset += 12;
			}

			if (aVertexFormat & SexyVF_Diffuse)
			{
				glColorPointer(4, GL_UNSIGNED_BYTE, aVertexSize, aVertexBuf + offset);
				glEnableClientState(GL_COLOR_ARRAY);
				offset += 4;
			}

			if (aVertexFormat & SexyVF_Specular)
			{
				//doesn't support the second color channel yet
				offset += 4;
			}



			if (aVertexFormat & SexyVF_Tex2)
			{
				glClientActiveTexture(GL_TEXTURE0);
				glTexCoordPointer(2, GL_FLOAT, aVertexSize, aVertexBuf + offset);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				offset += 8;

				glClientActiveTexture(GL_TEXTURE1);
				glTexCoordPointer(2, GL_FLOAT, aVertexSize, aVertexBuf + offset);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				offset += 8;
			}
			else if (aVertexFormat & SexyVF_Tex1)
			{
				glClientActiveTexture(GL_TEXTURE0);
				glTexCoordPointer(2, GL_FLOAT, aVertexSize, aVertexBuf + offset);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				offset += 8;
			}

			glClientActiveTexture(GL_TEXTURE0);


#else
			glVertexAttribPointer(0, 2, GL_FLOAT, 0, aVertexSize, aVertexBuf);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, 1, aVertexSize, aVertexBuf + 16);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, 0, aVertexSize, aVertexBuf + 24);
			glEnableVertexAttribArray(2);
			//glDisableVertexAttribArray(2);
#endif

		}

		virtual void UnbindVertexStream()
		{
#ifndef OPENGLES2
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);

			glClientActiveTexture(GL_TEXTURE1);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glClientActiveTexture(GL_TEXTURE0);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glDisableClientState(GL_COLOR_ARRAY);
#else
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
#endif
		}

		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition)
		{
			return NULL;
		}

		virtual bool SetRenderTarget(Image* theImage)
		{
			if (theImage && (mCurRenderTargetImage == theImage))
			{
				//no change
				return true;
			}

			if (theImage == NULL)
			{
				//set the main draw surface
				if (mSysImage==NULL) return false;
				return SetRenderTarget(mSysImage);
			}

			MemoryImage* aMemoryImage = theImage->AsMemoryImage();
			if (aMemoryImage == NULL)
				return false;
			if (!super::CreateImageRenderData(aMemoryImage))
				return false;

			class super::TextureData* aTextureData = (class super::TextureData*)aMemoryImage->GetRenderData();


			//get the FBO from the obj
			bool result = SetRenderTargetFBO(aTextureData->mExtraData.mFBO);
			if (result)
			{
				//int aWidth = theImage->mWidth;
				//int aHeight = theImage->mHeight;

				//static_cast<PlatformImplT*>(this)->SetImageViewport(theImage);

				//this may not be permanent
				mCurRenderTargetImage = theImage;
			}

			return result;
		}

		virtual bool SetRenderTargetFBO(GLuint fbo) = 0;


		virtual bool LoadMesh(Mesh* theMesh)
		{
			Buffer aBuffer;
			if (!gSexyAppBase->ReadBufferFromFile(theMesh->mFileName, &aBuffer))
				return NULL;

			if (aBuffer.ReadInt() != 0x3DBEEF00)
				return false;

			auto aVersion = aBuffer.ReadInt();
			if (aVersion > 2)
				return NULL;

			theMesh->Cleanup();

			if (theMesh->mListener != NULL)
				theMesh->mListener->MeshPreLoad(theMesh);

			int anObjectCount = aBuffer.ReadShort();
			for (int anObjIdx = 0; anObjIdx < anObjectCount; anObjIdx++)
			{
				std::string anObjectName = aBuffer.ReadString();

				int aSetCount = aBuffer.ReadShort();
				int aSetIdx;
				for (aSetIdx = 0; aSetIdx < aSetCount; aSetIdx++)
				{
					if (aVersion > 1)
					{
						uchar aFlags = aBuffer.ReadByte();
						if (aFlags == 0)
							continue;
					}

					theMesh->mPieces.push_back(new GLMeshPiece());
					GLMeshPiece* aPiece = (GLMeshPiece*)theMesh->mPieces.back();

					std::string aSetName = aBuffer.ReadString();

					std::string aTexFileName;
					std::string aBumpFileName;

					aPiece->mObjectName = anObjectName;
					aPiece->mSetName = aSetName;

					int aPropCount = aBuffer.ReadShort();
					for (int i = 0; i < aPropCount; i++)
					{
						std::string aPropName = aBuffer.ReadString();
						std::string aPropValue = aBuffer.ReadString();

						if (theMesh->mListener != NULL)
							theMesh->mListener->MeshHandleProperty(theMesh, anObjectName, aSetName, aPropName, aPropValue);
						if (aPropName == "texture0.fileName")
							aTexFileName = aPropValue;
						if (aPropName == "bump.fileName")
							aBumpFileName = aPropValue;
					}

					if (aTexFileName.length() > 0)
					{
						aPiece->mTexture.SetId(RtId(), false);
						if (theMesh->mListener)
							aPiece->mTexture.SetId(theMesh->mListener->MeshLoadTex(theMesh, anObjectName, aSetName, "texture0.fileName", aTexFileName), false);
						if (aPiece->mTexture)
							gSexyAppBase->mResourceManager->GetImage(aPiece->mTexture, GetPathFrom(aTexFileName, GetFileDir(theMesh->mFileName)));

						if ((Image*) aPiece->mTexture == NULL)
							break;
						((Image*) aPiece->mTexture)->AddImageFlags(ImageFlag_MinimizeNumSubdivisions | ImageFlag_NoTriRep);
					}

					if (super::SupportsPixelShaders()) // only bother loading up the bump map if we support pixel shaders, as we don't use fixed-function bumpmapping
					{
						if (aBumpFileName.length() > 0)
						{
							aPiece->mBumpTexture.SetId(RtId(), false);
							if (theMesh->mListener)
								aPiece->mBumpTexture.SetId(theMesh->mListener->MeshLoadTex(theMesh, anObjectName, aSetName, "bump.fileName", aBumpFileName), false);
							if (aPiece->mBumpTexture)
								gSexyAppBase->mResourceManager->GetImage(aPiece->mBumpTexture, GetPathFrom(aBumpFileName, GetFileDir(theMesh->mFileName)));

							if ((Image*) aPiece->mBumpTexture == NULL)
								break;
							((Image*) aPiece->mBumpTexture)->AddImageFlags(ImageFlag_MinimizeNumSubdivisions);
						}
					}

					uint16 aType = aBuffer.ReadShort(); (void)aType;// 0 = Triangle list
					uint32 aFVF = aBuffer.ReadInt();
					int aVertexSize = sizeof(float)*(3 + 3 + 2) + sizeof(uint32);

					aPiece->mSexyVF = aFVF;
					aPiece->mVertexSize = aVertexSize;

					aPiece->mVertexBufferCount = aBuffer.ReadShort();

					aPiece->mVertexData = new uint8[aVertexSize * aPiece->mVertexBufferCount];
					aBuffer.ReadBytes((uchar*) aPiece->mVertexData, aVertexSize * aPiece->mVertexBufferCount);

					aPiece->mIndexBufferCount = aBuffer.ReadShort()*3;
					aPiece->mIndexData = new uint8[aPiece->mIndexBufferCount*2];
					aBuffer.ReadBytes((uchar*) aPiece->mIndexData, aPiece->mIndexBufferCount*2);

				}

				if (aSetIdx < aSetCount) // Failed
					return false;
			}

			return true;
		}

		virtual void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true)
		{
			FlushBufferedTriangles();

			mStateMgr->PushState();
			mStateMgr->Set3DMode(true);


			if (doSetup)
			{
				/*glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);

				// Create light components
				GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
				GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
				GLfloat specularLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

				// Assign created components to GL_LIGHT0
				glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
				glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
				glLightfv(GL_LIGHT0, GL_POSITION, position);


				// set material properties which will be assigned by glColor
				glColorMaterial(GL_FRONT, GL_DIFFUSE);
				glColorMaterial(GL_BACK, GL_DIFFUSE);
				glEnable(GL_COLOR_MATERIAL);
				glFrontFace(GL_CW);*/


				SetTextureSingle(0, 0);
				SetAlphaTest(Graphics3D::COMPARE_ALWAYS, 0);
				SetDepthState(Graphics3D::COMPARE_ALWAYS, false);
				SetBlend(Graphics3D::BLEND_DEFAULT, Graphics3D::BLEND_DEFAULT);
				SetBltDepth(0.5f);

				SetupDrawMode(Graphics::DRAWMODE_NORMAL);
				SetTextureLinearFilter(0, true);

				mStateMgr->SetRenderState(SEXY3DRS_LIGHTING, 1);
				//mStateMgr->SetSamplerState(0, SEXY3DSAMP_ADDRESSU, SEXY3DTADDRESS_WRAP);
				//mStateMgr->SetSamplerState(0, SEXY3DSAMP_ADDRESSV, SEXY3DTADDRESS_WRAP);
				mStateMgr->SetRenderState(SEXY3DRS_ZWRITEENABLE, 1);
				mStateMgr->SetRenderState(SEXY3DRS_ZENABLE, SEXY3DZB_TRUE);
				mStateMgr->SetRenderState(SEXY3DRS_ZFUNC, SEXY3DCMP_LESSEQUAL);
				mStateMgr->SetRenderState(SEXY3DRS_CULLMODE, SEXY3DCULL_CCW);

				// Fill in a light structure defining our light
				Graphics3D::LightColors colors;
				colors.mDiffuse = Color(0xffffffff);
				colors.mAmbient = Color(0);
				colors.mSpecular = Color(0);
				colors.mAutoScale = 1.f;
				//mStateMgr->SetDirectionalLight(0, SexyVector3(0.5f, 0.5f, -0.5f).Normalize(), colors);
				//mStateMgr->SetLightEnabled(0, true);

				// Finally, turn on some ambient light.
				mStateMgr->SetRenderState(SEXY3DRS_AMBIENT, 0x40404040);


				/*if (mNeedClearZBuffer)
				{
					ClearDepthBuffer();
				}*/
			}
			else
			{
				// if we're not doing setup, we still need to make sure our blend settings are correct, now that we have default values
				SetupDrawMode(Graphics::DRAWMODE_NORMAL);
			}

			mStateMgr->SetTransform(OGL_TRANSFORM_WORLD, &theMatrix);

			//Render3DObjectHelper(theMesh);
			{
				RenderStateManager::Context* aStateContext = mStateMgr->GetContext();
				mStateMgr->PushState();

				if (theMesh->mListener)
				{
					theMesh->mListener->MeshPreDraw(theMesh);
					mStateMgr->SetContext(aStateContext); // listener could have changed current context
					SetupDrawMode(Graphics::DRAWMODE_NORMAL); // listener could have changed blend override; need to update
				}

				Mesh::MeshPieceList::iterator anItr = theMesh->mPieces.begin();
				while (anItr != theMesh->mPieces.end())
				{
					GLMeshPiece* aPiece = (GLMeshPiece*)(*anItr);

					/*if (aPiece->mVertexData != NULL)
					{
						int aReadVertexSize = aPiece->mVertexSize;
						if (FAILED(InternalCreateVertexBuffer(aPiece->mVertexSize * aPiece->mVertexBufferCount, false, aPiece->mSexyVF, SEXY3DPOOL_MANAGED, &aPiece->mVertexBuffer)))
						{
							// if we failed to create the vertex buffer, do an evict then make one more attempt
							Flush(FLUSHF_ManagedResources_Immediate);

							if (CheckDXError(InternalCreateVertexBuffer(aPiece->mVertexSize * aPiece->mVertexBufferCount, false, aPiece->mSexyVF, SEXY3DPOOL_MANAGED, &aPiece->mVertexBuffer)))
								break;
						}

						void* aData = NULL;
						if (CheckDXError(InternalVertexBufferLock(aPiece->mVertexBuffer, 0, aPiece->mVertexSize * aPiece->mVertexBufferCount, &aData, SEXY3DLOCK_NOSYSLOCK)))
							break;

						uchar* aSrcData = (uchar*) aPiece->mVertexData;
						D3DModelVertex* aVertex = (D3DModelVertex*) aData;
						for (int i = 0; i < aPiece->mVertexBufferCount; i++)
						{
							memcpy(aVertex, aSrcData, aReadVertexSize);
							aSrcData += aReadVertexSize;
							aVertex = (D3DModelVertex*) (((uchar*) aVertex) + aPiece->mVertexSize);
						}
						InternalVertexBufferUnlock(aPiece->mVertexBuffer);
						delete[] aPiece->mVertexData;
						aPiece->mVertexData = NULL;
					}

					if (aPiece->mIndexData != NULL)
					{
						if (CheckDXError(InternalCreateIndexBuffer(aPiece->mIndexBufferCount*2, SEXY3DPOOL_MANAGED, &aPiece->mIndexBuffer)))
							break;

						void* aData = NULL;
						if (CheckDXError(InternalIndexBufferLock(aPiece->mIndexBuffer, 0, aPiece->mIndexBufferCount*2, &aData, SEXY3DLOCK_NOSYSLOCK)))
							break;

						ushort* anIdx = (ushort*) aData;
						memcpy(anIdx, aPiece->mIndexData, aPiece->mIndexBufferCount*2);
						InternalIndexBufferUnlock(aPiece->mIndexBuffer);
						delete[] aPiece->mIndexData;
						aPiece->mIndexData = NULL;
					}

					SetTexture(0, aPiece->mTexture);
					if ((Image*) aPiece->mBumpTexture)
						SetTexture(1, aPiece->mBumpTexture);
					mStateMgr->SetFVF(aPiece->mSexyVF);
					mStateMgr->SetStreamSource(0, aPiece->mVertexBuffer, 0, aPiece->mVertexSize);
					mStateMgr->SetIndices(aPiece->mIndexBuffer);*/

					mStateMgr->SetVertexFormat(aPiece->mSexyVF,static_cast<PlatformImplT*>(this)->GetVertexSize(aPiece->mSexyVF));

					SetTexture(0, aPiece->mTexture);
					if ((Image*) aPiece->mBumpTexture)
						SetTexture(1, aPiece->mBumpTexture);



					if (theMesh->mListener)
					{
						theMesh->mListener->MeshPreDrawSet(theMesh, aPiece->mObjectName, aPiece->mSetName, (Image*) aPiece->mBumpTexture != NULL);
						mStateMgr->SetContext(aStateContext); // listener could have changed current context
						SetupDrawMode(Graphics::DRAWMODE_NORMAL); // listener could have changed blend override; need to update
					}

					mStateMgr->CommitState();

					{
#ifndef OPENGLES2
						Graphics3D::EPrimitiveType thePrimitiveType = Graphics3D::PT_TriangleList;
						//TODO move this setup to a common function
						uint32 theVertexFormat = aPiece->mSexyVF;
						int aVertexSize = 0;
						if (theVertexFormat & SexyVF_XYZ)
							aVertexSize += 12;
						if (theVertexFormat & SexyVF_XYZRHW)
							aVertexSize += 16;
						if (theVertexFormat & SexyVF_Normal)
							aVertexSize += 12;
						if (theVertexFormat & SexyVF_Diffuse)
							aVertexSize += 4;
						if (theVertexFormat & SexyVF_Specular)
							aVertexSize += 4;
						if (theVertexFormat & SexyVF_Tex1)
							aVertexSize += 8; //always just 2 floats?
						if (theVertexFormat & SexyVF_Tex2)
							aVertexSize += 8;

						uint8* aVertexBuf = aPiece->mVertexData;


						GLuint primType = GL_TRIANGLES;
						if (thePrimitiveType == Graphics3D::PT_TriangleList)
							primType = GL_TRIANGLES;
						else if (thePrimitiveType == Graphics3D::PT_TriangleStrip)
							primType = GL_TRIANGLE_STRIP;
						else if (thePrimitiveType == Graphics3D::PT_TriangleFan)
							primType = GL_TRIANGLE_FAN;
						else if (thePrimitiveType == Graphics3D::PT_LineStrip)
							primType = GL_LINE_STRIP;

						static_cast<PlatformImplT*>(this)->BindVertexStream(aVertexBuf);

						glDrawElements(primType, aPiece->mIndexBufferCount, GL_UNSIGNED_SHORT, aPiece->mIndexData);

						static_cast<PlatformImplT*>(this)->UnbindVertexStream();
#endif
					}

					if (theMesh->mListener)
					{
						theMesh->mListener->MeshPostDrawSet(theMesh, aPiece->mObjectName, aPiece->mSetName);
						mStateMgr->SetContext(aStateContext); // listener could have changed current context
					}

					++anItr;
				}

				if (theMesh->mListener)
				{
					theMesh->mListener->MeshPostDraw(theMesh);
					mStateMgr->SetContext(aStateContext); // listener could have changed current context
				}

				mStateMgr->PopState();
			}

			mStateMgr->PopState();
		}

		void LostFocus()
		{
			OpenGLIdRegistry::StaticLostFocus();
			mStateMgr->LostFocus();
		}

		void GotFocus()
		{
			OpenGLIdRegistry::StaticGotFocus();
			mStateMgr->GotFocus();
		}
	};

}

#endif
