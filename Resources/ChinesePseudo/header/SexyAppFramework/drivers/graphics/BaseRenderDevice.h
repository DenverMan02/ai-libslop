#ifndef BASERENDERDEVICE_H_INCLUDED
#define BASERENDERDEVICE_H_INCLUDED

/**
 *  The BaseRenderDevice can give Prime driver implementations a boost in getting
 *  to the compliant stage of development.  
 *  
 *  the BaseRenderDevice implements all of the polygon buffering/clipping/generating
 *  operations and shuffles them into the abstract virtual DrawPrimitiveInternal 
 *  much like D3DInterface does with it's version specific implementations.
 * 
 *  The BaseRenderDevice does not implement some functions of RenderDevice that 
 *  are very platform specific. Driver implementors will still be responsible for 
 *  texture setting, context setting, predraw, etc...
 *
 *  The base render device uses the "Curiously Recurring Template Pattern" to allow
 *  for methods to be overrloaded without requiring a vtable lookup and potentially 
 *  even be inlined.
 *  http://en.wikipedia.org/wiki/Curiously_Recurring_Template_Pattern
 */
#include "RenderDevice.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"
#include "Graphics.h"
#include "DeviceImage.h"
#include "SexyMatrix.h"
#include "Debug.h"
#include "AutoCrit.h"
#include "CritSect.h"
#include "PerfTimer.h"

namespace Sexy 
{
    
template <typename VertexT, typename TextureT, typename ExtraRenderDataInfoT, class PlatformImplT> 
class BaseRenderDevice : public RenderDevice3D
{
private:
	typedef BaseRenderDevice<VertexT,TextureT,ExtraRenderDataInfoT,PlatformImplT> GenericRenderDevice;
public:
	// Needs a new name, this is related to MaxTextureSize,
	// but not really for the device, it's used for a lookup table
	static const int MAX_TEXTURE_SIZE = 4096;
	
	float	mPixelOffset;  //-0.5f for DirectX.  0.0f for OpenGL
	int		mMinTextureWidth;
	int		mMinTextureHeight;
	int		mMaxTextureWidth;
	int		mMaxTextureHeight;
	int		mMaxTextureAspectRatio;
	uint32	mRenderModeFlags;
	uint32	mSupportedTextureFormats;
	bool	mTextureSizeMustBePow2;
	bool	mRenderTargetMustBePow2;
	uint32  mDefaultVertexSize;
	uint32	mDefaultVertexFVF;

	//TODO: replace this with some of the soon to come Resolution independence
	int		mWidth;
	int		mHeight;
	
	int		mScreenWidth;
	int		mScreenHeight; //the Width and Height of the current RenderTarget... used for clipping
	
#ifndef RELEASEFINAL
	GraphicsMetrics* mMetrics;
#endif
	
	struct VertexTList
	{
		enum { MAX_STACK_VERTS = 100 };
		VertexT mStackVerts[MAX_STACK_VERTS];
		VertexT *mVerts;
		int mSize;
		int mCapacity;
		
		typedef int size_type;
		
		VertexTList() : mSize(0), mCapacity(MAX_STACK_VERTS), mVerts(mStackVerts) { }
		VertexTList(const VertexTList &theList) : mSize(theList.mSize), mCapacity(MAX_STACK_VERTS), mVerts(mStackVerts)  
		{ 
			reserve(mSize);
			memcpy(mVerts,theList.mVerts,mSize*sizeof(mVerts[0]));
		}
		
		~VertexTList() 
		{ 
			if (mVerts != mStackVerts)
				delete[] mVerts; 
		}
		
		inline void reserve(int theCapacity)
		{
			if (mCapacity < theCapacity)
			{
				mCapacity = theCapacity;
				VertexT *aNewList = new VertexT[theCapacity];
				memcpy(aNewList,mVerts,mSize*sizeof(mVerts[0]));
				if (mVerts != mStackVerts)
					delete[] mVerts;
				
				mVerts = aNewList;
			}
		}
		
		inline void push_back(const VertexT &theVert) 
		{ 
			if (mSize==mCapacity)
				reserve(mCapacity*2);
			
			mVerts[mSize++] = theVert; 
		}
		
		inline void operator=(const VertexTList &theList) 
		{ 
			reserve(theList.mSize);
			mSize = theList.mSize; 
			memcpy(mVerts,theList.mVerts,mSize*sizeof(mVerts[0]));
		}
		
		
		inline VertexT& operator[](int thePos) 
		{ 
			return mVerts[thePos]; 
		}
		
		inline int size() { return mSize; }
		inline void clear() { mSize = 0; }
	};
	

	
	
	/**
	 * GetBestTextureDimensions. 
	 * Default implementation uses the RenderDevice's min/max Texture specs
	 * to get the correct sizes. Platform implementatations should consider 
	 * overriding this to have more control over the process.
	 */
	virtual void GetBestTextureDimensions(int &theWidth, int &theHeight, bool isEdge, bool usePow2, uint32 theImageFlags)
	{
		theImageFlags |= ImageFlag_MinimizeNumSubdivisions;  //Jvw -- this should be a driver option (to insert addtl image flags)
		if (theImageFlags & ImageFlag_Use64By64Subdivisions)
		{
			theWidth = theHeight = 64;
			return;
		}
		
		static int aGoodTextureSize[MAX_TEXTURE_SIZE];
		static bool haveInited = false;
		if (!haveInited)
		{
			haveInited = true;
			int i;
			int aPow2 = 1;
			for (i=0; i<MAX_TEXTURE_SIZE; i++)
			{
				if (i > aPow2)
					aPow2 <<= 1;
				
				int aGoodValue = aPow2;
				if ((aGoodValue - i ) > 64)
				{
					aGoodValue >>= 1;
					while (true)
					{
						int aLeftOver = i % aGoodValue;
						if (aLeftOver<64 || IsPowerOf2(aLeftOver))
							break;
						
						aGoodValue >>= 1;
					}
				}
				aGoodTextureSize[i] = aGoodValue;
			}
		}
		
		int aWidth = theWidth;
		int aHeight = theHeight;
		
		if (usePow2) // && (theImageFlags & ImageFlag_RenderTarget)==0)
		{
			if (isEdge || (theImageFlags & ImageFlag_MinimizeNumSubdivisions) || (theImageFlags & ImageFlag_RenderTarget)!=0)
			{
				aWidth = aWidth >= mMaxTextureWidth ? mMaxTextureWidth : GetClosestPowerOf2Above(aWidth);
				aHeight = aHeight >= mMaxTextureHeight ? mMaxTextureHeight : GetClosestPowerOf2Above(aHeight);
			}
			else
			{
				aWidth = aWidth >= mMaxTextureWidth ? mMaxTextureWidth : aGoodTextureSize[aWidth];
				aHeight = aHeight >= mMaxTextureHeight ? mMaxTextureHeight : aGoodTextureSize[aHeight];
			}
		}
		
		if (aWidth < mMinTextureWidth)
			aWidth = mMinTextureWidth;
		else if (aWidth > mMaxTextureWidth && (theImageFlags & ImageFlag_RenderTarget)==0)
			aWidth = mMaxTextureWidth;
		
		if (aHeight < mMinTextureHeight)
			aHeight = mMinTextureHeight;
		else if (aHeight > mMaxTextureHeight && (theImageFlags & ImageFlag_RenderTarget)==0)
			aHeight = mMaxTextureHeight;
		
		if (((theImageFlags & ImageFlag_RenderTarget) == 0) && ((theImageFlags & ImageFlag_MinimizeNumSubdivisions) == 0))
		{
			// Some ATI cards pretend they can do non-square textures but they can't really, so still break up really non-square images
			//JVW - is there a flag that we can check for drivers that exhibit this behavior? it's causing chunking for lots of images
			if ((aWidth > 512) && (aHeight < aWidth/2))
				aWidth = 512;
		}
		
		if (aWidth > aHeight)
		{
			while (aWidth > mMaxTextureAspectRatio*aHeight)
				aHeight <<= 1;
		}
		else if (aHeight > aWidth)
		{
			while (aHeight > mMaxTextureAspectRatio*aWidth)
				aWidth <<= 1;
		}
		
		theWidth = aWidth;
		theHeight = aHeight;
	}
	
	template<class Pred>
	struct PointClipper
	{
		Pred mPred;
		
		void ClipPoint(int n, float clipVal, const VertexT &v1, const VertexT &v2, VertexTList &out)
		{
			if (!mPred(VertexT::GetCoord(v1,n), clipVal))
			{
				if (!mPred(VertexT::GetCoord(v2,n), clipVal)) // both inside
					out.push_back(v2);
				else // inside -> outside
				{
					float t = (clipVal - VertexT::GetCoord(v1,n))/(VertexT::GetCoord(v2,n)-VertexT::GetCoord(v1,n));
					out.push_back(VertexT::Interpolate(v1,v2,t));
				}
			}
			else
			{
				if (!mPred(VertexT::GetCoord(v2,n), clipVal)) // outside -> inside
				{
					float t = (clipVal - VertexT::GetCoord(v1, n))/(VertexT::GetCoord(v2,n)-VertexT::GetCoord(v1,n));
					out.push_back(VertexT::Interpolate(v1,v2,t));
					out.push_back(v2);
				}
				//			else // outside -> outside
			}
		}
		
		void ClipPoints(int n, float clipVal, VertexTList &in, VertexTList &out)
		{
			if(in.size()<2)
				return;
			
			ClipPoint(n,clipVal,in[in.size()-1],in[0],out);
			for(int i=0; i<in.size()-1; i++)
				ClipPoint(n,clipVal,in[i],in[i+1],out);
		}
		
	};
	

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	static void DoPolyTextureClip(VertexTList &theList)
	{
		VertexTList l2;
		
		float left = 0;
		float right = 1;
		float top = 0;
		float bottom = 1;
		
		VertexTList *in = &theList, *out = &l2;
		PointClipper<std::less<float> > aLessClipper;
		PointClipper<std::greater_equal<float> > aGreaterClipper;
		
		aLessClipper.ClipPoints(3,left,*in,*out); std::swap(in,out); out->clear();
		aLessClipper.ClipPoints(4,top,*in,*out); std::swap(in,out); out->clear();
		aGreaterClipper.ClipPoints(3,right,*in,*out); std::swap(in,out); out->clear();
		aGreaterClipper.ClipPoints(4,bottom,*in,*out); 
	}
	
	
	struct TextureDataPiece
	{
		TextureDataPiece()
		{
			mTexture = 0;
            mMultiTexture = 0;
			mCubeTexture = 0;
			mVolumeTexture = 0;
			mTexFormat = 0;
			mWidth = 0;
			mHeight = 0;
		}
		
		TextureT mTexture;          // for normal textures (null for cubemaps/volumemaps)
        TextureT mMultiTexture;     // for normal second textures (null for cubemaps/volumemaps)
		TextureT mCubeTexture;      // for cubemap textures (null for normal textures/volumemaps)
		TextureT mVolumeTexture;    // for volumemap textures (null for normal textures/cubemaps)
		int mTexFormat;
		int mWidth;
		int mHeight;
	};
	
	class TextureData
	{
	public:
		typedef std::vector<TextureDataPiece> TextureVector;
		
		GenericRenderDevice* mDevice;
		
		TextureVector mTextures;
		ExtraRenderDataInfoT mExtraData;
		int mPaletteIndex;
		
		bool mOptimizedLoad;
		int mWidth, mHeight;
		int mTexVecWidth, mTexVecHeight;
		int mTexPieceWidth, mTexPieceHeight;
		int mBitsChangedCount;
		int mTexMemSize;
		int mTexMemOriginalSize;
		uint32 mTexMemFlushRevision;
		float mMaxTotalU, mMaxTotalV;
		PixelFormat mPixelFormat;
		uint32 mImageFlags;

		TextureData(GenericRenderDevice* theDevice)
		{
			mDevice = theDevice;
			mWidth = 0;
			mHeight = 0;
			mTexVecWidth = 0;
			mTexVecHeight = 0;
			mBitsChangedCount = 0;
			mTexMemSize = 0;
			mTexMemOriginalSize = 0;
			mTexMemFlushRevision = 0;
			mTexPieceWidth = 64;
			mTexPieceHeight = 64;
			
			mPaletteIndex = -1;
			mPixelFormat = PixelFormat_Unknown;
			mImageFlags = 0;
			mOptimizedLoad = false;
		}
		
		~TextureData()
		{
			ReleaseTextures();
		}
		
		void ReleaseTextures()
		{
			for(int i=0; i<(int)mTextures.size(); i++)
			{
				if (mTextures[i].mTexture!=0)
				{
					mDevice->ReleaseTexture(this,mTextures[i].mTexture);
					mTextures[i].mTexture = 0;
				}
				
				if (mTextures[i].mCubeTexture!=0)
				{
					mDevice->ReleaseTexture(this,mTextures[i].mCubeTexture);
					mTextures[i].mCubeTexture = 0;
				}
				
				if (mTextures[i].mVolumeTexture!=0)
				{
					mDevice->ReleaseTexture(this,mTextures[i].mVolumeTexture);
					mTextures[i].mVolumeTexture = 0;
				}
			}
			
			mTextures.clear();
			
			mDevice->ReleaseExtraRenderDataInfo(this,mExtraData);
		}
		
		void CreateTextureDimensions(GenericRenderDevice* theDevice, MemoryImage *theImage)
		{
			if (mImageFlags & (ImageFlag_CubeMap | ImageFlag_VolumeMap))
			{
				// cube map / volume map textures, which are a special case
				mWidth = mTexPieceWidth = theImage->GetCelWidth();
				mHeight = mTexPieceHeight = theImage->GetCelHeight();
				mTexVecWidth = mTexVecHeight = 1;
				mMaxTotalU = mMaxTotalV = 1.0f;
				
				mTextures.resize(1);
				
				TextureDataPiece &aPiece = mTextures[0];
				aPiece.mTexture = 0;
				aPiece.mCubeTexture = 0;
				aPiece.mVolumeTexture = 0;
				aPiece.mWidth = theImage->GetCelWidth();
				aPiece.mHeight = theImage->GetCelHeight();
			}
			else
			{
				// normal textures
				
				int aWidth = theImage->GetWidth();
				int aHeight = theImage->GetHeight();
				int i;
				/**/
				// Calculate inner piece sizes
				mTexPieceWidth = aWidth;
				mTexPieceHeight = aHeight;
				bool usePow2 = theDevice->mTextureSizeMustBePow2; // || mPixelFormat==PixelFormat_Palette8;
				if (mImageFlags & ImageFlag_RenderTarget)
				{
					//this appears to be the case with iPhone GL ES 2.0
					usePow2 = theDevice->mRenderTargetMustBePow2;
				}
				theDevice->GetBestTextureDimensions(mTexPieceWidth, mTexPieceHeight,false,usePow2,mImageFlags);
				
				// Calculate right boundary piece sizes
				int aRightWidth = aWidth%mTexPieceWidth;
				int aRightHeight = mTexPieceHeight;
				if (aRightWidth > 0)
					theDevice->GetBestTextureDimensions(aRightWidth, aRightHeight,true,usePow2,mImageFlags);
				else
					aRightWidth = mTexPieceWidth;
				
				// Calculate bottom boundary piece sizes
				int aBottomWidth = mTexPieceWidth;
				int aBottomHeight = aHeight%mTexPieceHeight;
				if (aBottomHeight > 0)
					theDevice->GetBestTextureDimensions(aBottomWidth, aBottomHeight,true,usePow2,mImageFlags);
				else
					aBottomHeight = mTexPieceHeight;
				
				// Calculate corner piece size
				int aCornerWidth = aRightWidth;
				int aCornerHeight = aBottomHeight;
				theDevice->GetBestTextureDimensions(aCornerWidth, aCornerHeight,true,usePow2,mImageFlags);
				/**/
				
				//	mTexPieceWidth = 64;
				//	mTexPieceHeight = 64;
				
				
				// Allocate texture array
				mTexVecWidth = (aWidth + mTexPieceWidth - 1)/mTexPieceWidth;
				mTexVecHeight = (aHeight + mTexPieceHeight - 1)/mTexPieceHeight;
				mTextures.resize(mTexVecWidth*mTexVecHeight);
				
				// Assign inner pieces
				for(i=0; i<(int)mTextures.size(); i++)
				{
					TextureDataPiece &aPiece = mTextures[i];
					aPiece.mTexture = 0;
					aPiece.mCubeTexture = 0;
					aPiece.mVolumeTexture = 0;
					aPiece.mWidth = mTexPieceWidth;
					aPiece.mHeight = mTexPieceHeight;
				}
				
				// Assign right pieces
				/**/
				for(i=mTexVecWidth-1; i<(int)mTextures.size(); i+=mTexVecWidth)
				{
					TextureDataPiece &aPiece = mTextures[i];
					aPiece.mWidth = aRightWidth;
					aPiece.mHeight = aRightHeight;
				}
				
				// Assign bottom pieces
				for(i=mTexVecWidth*(mTexVecHeight-1); i<(int)mTextures.size(); i++)
				{
					TextureDataPiece &aPiece = mTextures[i];
					aPiece.mWidth = aBottomWidth;
					aPiece.mHeight = aBottomHeight;
				}
				
				// Assign corner piece
				mTextures.back().mWidth = aCornerWidth;
				mTextures.back().mHeight = aCornerHeight;
				/**/
				
				mMaxTotalU = aWidth/(float)mTexPieceWidth;
				mMaxTotalV = aHeight/(float)mTexPieceHeight;
			}
		}
		
		
		void CreateTextures(MemoryImage *theImage, GenericRenderDevice* theDevice, bool commitBits=true)
		{
			DBG_ASSERTE(theDevice == mDevice);
			
			theImage->DeleteSWBuffers(); // don't need these buffers for 3d drawing
			
			PixelFormat aFormat = PixelFormat_A8R8G8B8;
			
			// Choose appropriate pixel format
			
			//theImage->ReplaceImageFlags(ImageFlag_UseA4R4G4B4);
			
			if (commitBits)
			{
				theImage->CommitBits();
			}
			if (!theImage->mHasAlpha && !theImage->mHasTrans)
			{
				/*if ((D3DInterface::sSupportedTextureFormats & PixelFormat_R5G6B5) &&
				 (!theImage->HasImageFlag(ImageFlag_RenderTarget) || (theInterface->mDisplayFormat == SEXY3DFMT_R5G6B5)) &&
				 (!theImage->HasImageFlag(ImageFlag_UseA8R8G8B8)))							
				 {
				 aFormat = PixelFormat_R5G6B5;
				 }
				 else if (theImage->HasImageFlag(ImageFlag_RenderTarget))*/
				
				//JVW - for now force GLDriver to use XRGB8
				{
					aFormat = PixelFormat_X8R8G8B8;
				}		
			}
			
			/*
			 //JVW for now don't support paletted images
			 if (theImage->mColorIndices != NULL && (D3DInterface::sSupportedTextureFormats & PixelFormat_Palette8) != 0 && !theInterface->mAvailPalettes.empty())
			 {
			 PALETTEENTRY aPalette[256];
			 for (int i=0; i<256; i++)
			 {
			 DWORD aPixel = theImage->mColorTable[i];
			 *(DWORD*)(aPalette+i) = (aPixel&0xFF00FF00) | ((aPixel>>16)&0xFF) | ((aPixel<<16)&0xFF0000);
			 }
			 int aPaletteIndex = theInterface->mAvailPalettes.back();
			 HRESULT aResult = theInterface->InternalSetPaletteEntries(aPaletteIndex, aPalette);
			 if (SUCCEEDED(aResult))
			 {
			 theInterface->mAvailPalettes.pop_back();
			 mPaletteIndex = aPaletteIndex;
			 aFormat = PixelFormat_Palette8;
			 }
			 else
			 {
			 std::string anError = GetDirectXErrorString(aResult);
			 D3DInterface::sSupportedTextureFormats &= ~PixelFormat_Palette8;
			 mPaletteIndex = -1;
			 }
			 }*/
			
			if (theImage->HasImageFlag(ImageFlag_UseA4R4G4B4) && aFormat==PixelFormat_A8R8G8B8 && (theDevice->mSupportedTextureFormats & PixelFormat_A4R4G4B4))
				aFormat = PixelFormat_A4R4G4B4;
			
			if (aFormat==PixelFormat_A8R8G8B8 && !(theDevice->mSupportedTextureFormats & PixelFormat_A8R8G8B8))
				aFormat = PixelFormat_A4R4G4B4;	
			
			// Release texture if image size has changed
			bool createTextures = false;
			if (mWidth!=theImage->mWidth || mHeight!=theImage->mHeight || aFormat!=mPixelFormat || theImage->GetImageFlags()!=mImageFlags)
			{
				ReleaseTextures();
				
				mPixelFormat = aFormat;
				mImageFlags = theImage->GetImageFlags();
				CreateTextureDimensions(theDevice,theImage);
				createTextures = true;
			}
			
			int i,x,y;
			
			int aHeight = theImage->GetHeight();
			int aWidth = theImage->GetWidth();
			
			if (mPaletteIndex != -1)
			{
				mTexMemSize += 256*4;
				mTexMemOriginalSize += 256*4;
			}
			
			int aFormatSize = 4;
			if (aFormat==PixelFormat_Palette8)
				aFormatSize = 1;
			else if (aFormat==PixelFormat_R5G6B5)
				aFormatSize = 2;
			else if (aFormat==PixelFormat_A4R4G4B4)
				aFormatSize = 2;
			
			if (mImageFlags & ImageFlag_CubeMap)
			{
				// special handling for cube maps
				
				TextureDataPiece &aPiece = mTextures[0];
				if (createTextures)
				{
					DBG_ASSERTE(mTexMemSize == 0);
					DBG_ASSERTE(mTexMemOriginalSize == 0);
					
					// CDH FIXME$$: render target flag not supported with cube maps; assert on this?
					//aPiece.mCubeTexture = CreateCubeTextureSurface(theInterface, aPiece.mWidth, aFormat);
					DBG_ASSERTE("NOT IMPLEMENTED"==0);
					if (aPiece.mCubeTexture==0) // create cube texture failure
					{
						mPixelFormat = PixelFormat_Unknown;
						return;
					}

					uint32 aOriginalSize = theImage->GetWidth()*theImage->GetHeight()*aFormatSize; // can't use piece width/height since that's for individual cels
					mTexMemSize += aOriginalSize;
					mTexMemOriginalSize += aOriginalSize;
					
					//theDriver->mTexMemUsageBytesAlloced += mTexMemSize;
					//theDriver->mTexMemUsageBytesOriginal += mTexMemOriginalSize;
				}
				
				DBG_ASSERTE("NOT IMPLEMENTED"==0);
				//CopyImageToCubeMap(theDriver,aPiece.mCubeTexture,theImage,aFormat);
				
				mWidth = theImage->GetWidth();
				mHeight = theImage->GetHeight();
				mBitsChangedCount = theImage->mBitsChangedCount;
				mPixelFormat = aFormat;
				
				return;
			}
			else if (mImageFlags & ImageFlag_VolumeMap)
			{
				// special handling for volume maps
				
				TextureDataPiece &aPiece = mTextures[0];
				if (createTextures)
				{
					DBG_ASSERTE(mTexMemSize == 0);
					DBG_ASSERTE(mTexMemOriginalSize == 0);
					
					// CDH FIXME$$: render target flag not supported with volume maps; assert on this?
					//aPiece.mVolumeTexture = CreateVolumeTextureSurface(theInterface, aPiece.mWidth, aFormat);
					DBG_ASSERTE("NOT IMPLEMENTED"==0);
					if (aPiece.mVolumeTexture==0) // create volume texture failure
					{
						mPixelFormat = PixelFormat_Unknown;
						return;
					}

					uint32 aOriginalSize = theImage->GetWidth()*theImage->GetHeight()*aFormatSize; // can't use piece width/height since that's for individual cels
					mTexMemSize += aOriginalSize;
					mTexMemOriginalSize += aOriginalSize;
					
					//theDriver->mTexMemUsageBytesAlloced += mTexMemSize;
					//theDriver->mTexMemUsageBytesOriginal += mTexMemOriginalSize;
				}
				
				DBG_ASSERTE("NOT IMPLEMENTED"==0);
				//CopyImageToVolumeMap(theInterface,aPiece.mVolumeTexture,theImage,aFormat);
				
				mWidth = theImage->GetWidth();
				mHeight = theImage->GetHeight();
				mBitsChangedCount = theImage->mBitsChangedCount;
				mPixelFormat = aFormat;
				
				return;
			}
			
			if (createTextures)
			{
				//DBG_ASSERTE(mTexMemSize == 0);
				//DBG_ASSERTE(mTexMemOriginalSize == 0);
			}
			
			i=0;
			for(y=0; y<aHeight; y+=mTexPieceHeight)
			{
				for(x=0; x<aWidth; x+=mTexPieceWidth, i++)
				{
					TextureDataPiece &aPiece = mTextures[i];
					if (createTextures)
					{
						aPiece.mTexture = theDevice->CreateTextureSurface(aPiece.mWidth, aPiece.mHeight, aFormat, theImage->HasImageFlag(ImageFlag_RenderTarget),this,&aPiece);
						if (aPiece.mTexture==0) // create texture failure
						{
							DBG_ASSERT("texture create failed"==0);
							mPixelFormat = PixelFormat_Unknown;
							return;
						}
						
						mTexMemSize += aPiece.mWidth*aPiece.mHeight*aFormatSize;
					}
					
					if (theImage->HasImageFlag(ImageFlag_RenderTarget))
					{
						if (theImage->mBits!=NULL)
						{
							//unlikely that this would be used
							//not supporting for simplicity for now
							DBG_ASSERTE("NOT IMPLEMENTED"==0);
						}
						/*IUnknown* aTempTex;
						 if (D3DInterface::CheckDXError(theInterface->InternalCreateTexture(aPiece.mWidth, aPiece.mHeight, 1, 0, 
						 aFormat, SEXY3DPOOL_SYSTEMMEM, &aTempTex)))
						 return;
						 
						 CopyImageToTexture(theInterface,aTempTex,theImage,x,y,aPiece.mWidth,aPiece.mHeight,aFormat);
						 theInterface->InternalTextureMakeDirty(aTempTex);
						 theInterface->InternalTextureMakeDirty(aPiece.mTexture);
						 D3DInterface::CheckDXError(theInterface->InternalUpdateTexture(aTempTex, aPiece.mTexture));
						 aTempTex->Release();*/				
					}
					else
					{
						// $ (avy) Don't call CopyImageToTexture() if mBits is NULL, otherwise when GetBits() is called massive allocations will be made.
						if (commitBits && theImage->mBits != NULL)
							mDevice->CopyImageToTexture(aPiece.mTexture,aPiece.mTexFormat,theImage,x,y,aPiece.mWidth,aPiece.mHeight,aFormat);
					}
				}
			}
			
			if (createTextures)
			{
				mTexMemOriginalSize += theImage->GetWidth()*theImage->GetHeight()*aFormatSize;
				
				//theDriver->mTexMemUsageBytesAlloced += mTexMemSize;
				//theDriver->mTexMemUsageBytesOriginal += mTexMemOriginalSize;
			}
			
			mWidth = theImage->mWidth;
			mHeight = theImage->mHeight;
			mBitsChangedCount = theImage->mBitsChangedCount;
			mPixelFormat = aFormat;
		}
		
		
		void CheckCreateTextures(MemoryImage *theImage, GenericRenderDevice* theDevice)
		{
			if(mPixelFormat==PixelFormat_Unknown || theImage->mWidth != mWidth || theImage->mHeight != mHeight || theImage->mBitsChangedCount != mBitsChangedCount || theImage->GetImageFlags() != mImageFlags)
			{
				if(mOptimizedLoad)
				{
					mImageFlags = theImage->GetImageFlags();
#ifndef PRIME_FOR_PVZ2
					OutputDebug("WARN: Image dimensions or flags changed on an optimized image.\n");
#endif
					return;
				}

				CreateTextures(theImage, theDevice);
			}
		}
		
	// QZY added. Only get the texture is enough.
		TextureT GetTexture2(MemoryImage* theOrigImage, int& texWidth, int& texHeight)
		{
			if (mImageFlags & (ImageFlag_CubeMap | ImageFlag_VolumeMap))
				return 0;

			TextureDataPiece &aPiece = mTextures[0];

			texWidth = aPiece.mWidth;
			texHeight = aPiece.mHeight;
			return aPiece.mTexture;
		}

		void BltStrech(GenericRenderDevice* theDevice, MemoryImage* theImage, int theDrawMode, float theX, float theY, const Rect& theSrcRect, const Color& theColor)
		{
			DBG_ASSERTE(theDevice == mDevice);

			/*if (mTexMemFlushRevision < theDriver->mTexMemUsageFlushRevision)
			 {
			 theDriver->mTexMemUsageBytesCurFrame += mTexMemSize;
			 mTexMemFlushRevision = theInterface->mTexMemUsageFlushRevision;
			 }*/

			int srcLeft = theSrcRect.mX;
			int srcTop = theSrcRect.mY;
			int srcRight = srcLeft + theSrcRect.mWidth;
			int srcBottom = srcTop + theSrcRect.mHeight;
			int srcX, srcY;
			float dstX, dstY;
			int aWidth,aHeight;
			float u1,v1,u2,v2;

			srcY = srcTop;
			dstY = theY;

			uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);

			if ((srcLeft >= srcRight) || (srcTop >= srcBottom))
				return;
            
			float z = static_cast<PlatformImplT*>(theDevice)->GetBltDepth();

			srcX = srcLeft;
			dstX = theX;
			aWidth = srcRight-srcX;
			aHeight = srcBottom-srcY;

			int texWidth, texHeight;
			TextureT aTexture = GetTexture2(theImage, texWidth, texHeight);//,srcX, srcY, aWidth, aHeight, u1, v1, u2, v2);

			u1 = v1 = 0.0f;
			u2 = static_cast<PlatformImplT*>(theDevice)->mScreenWidth;
			u2 = u2/(float)texWidth;
			v2 = static_cast<PlatformImplT*>(theDevice)->mScreenHeight;
			v2 = v2/(float)texHeight;

			if (mPaletteIndex != -1)
			{
				DBG_ASSERTE("NOT IMPLEMENTED"==0);
				//theDriver->mStateMgr->SetCurrentTexturePalette(mPaletteIndex);
			}
			static_cast<PlatformImplT*>(theDevice)->SetTextureSingle(0, aTexture);

			float x = dstX + theDevice->mPixelOffset;
			float y = dstY + theDevice->mPixelOffset;

			// see about using a tri representation, if available and appropriate

			MemoryImage::TriRep::Tri* triUVs = NULL;
			int triCount = 0;
			if (PlatformImplT::SUPPORT_TRI_REP && mTextures.size() == 1)
			{
				float usageFrac = (float)(aWidth*aHeight) / (float)(theDevice->mWidth*theDevice->mHeight);
				MemoryImage::TriRep* triRep = theImage ? ((theDrawMode == Graphics::DRAWMODE_NORMAL) ? &theImage->mNormalTriRep : &theImage->mAdditiveTriRep) : NULL;
				MemoryImage::TriRep::Level* triRepLevel = triRep ? triRep->GetLevelForScreenSpaceUsage(usageFrac, false) : NULL;
				if (triRepLevel && theImage->HasImageFlag(ImageFlag_NoTriRep))
					triRepLevel = NULL;
#ifndef RELEASEFINAL
				if (theDevice->mRenderModeFlags & IGraphicsDriver::RENDERMODEF_NoTriRep)
					triRepLevel = NULL;
#endif
				if (triRepLevel)
				{
					triCount = 0;
					triUVs = triRepLevel->GetRegionTrisPtr(triCount, theImage, theSrcRect, false);
					if (triUVs==NULL) triCount = 0;
				}
			}
			if (PlatformImplT::SUPPORT_TRI_REP && triCount > 0)
			{
				// use tri representation
				VertexT* aTriVertex = (VertexT*)alloca(triCount*3*sizeof(VertexT));
				VertexT* aStartVertex = aTriVertex;
				MemoryImage::TriRep::Tri* aTriUV = triUVs;


				if ((u1==0.f) && (v1==0.f) && (u2==1.f) && (v2==1.f))
				{
					for (int q=0; q<triCount; ++q, aTriVertex += 3, ++aTriUV)
					{
						const MemoryImage::TriRep::Tri::Point* trp = aTriUV->p;

						for (int v=0; v<3; ++v)
						{
							aTriVertex[v] = VertexT(x+ aWidth*trp[v].u, y + aHeight*trp[v].v,z,
													trp[v].u,trp[v].v,aColor);
						}
					}
				}
				else
				{
					SexyVector2 uVector((float)aWidth, 0.f);
					SexyVector2 vVector(0.f, (float)aHeight);

					SexyVector2 basePos(x, y);
					if ((u1 != 0.0f) || (u2 != 1.0f))
					{
						float texDelta = u2 - u1;
						float ootexDelta = 1.f / texDelta;

						uVector *= ootexDelta;
						basePos -= uVector*u1;
					}
					if ((v1 != 0.0f) || (v2 != 1.0f))
					{
						float texDelta = v2 - v1;
						float ootexDelta = 1.f / texDelta;

						vVector *= ootexDelta;
						basePos -= vVector*v1;
					}

					for (int q=0; q<triCount; ++q, aTriVertex += 3, ++aTriUV)
					{
						const MemoryImage::TriRep::Tri::Point* trp = aTriUV->p;

						SexyVector2 pos;

						for (int v=0; v<3; ++v)
						{
							pos = basePos + uVector*trp[v].u + vVector*trp[v].v;

							aTriVertex[v] = VertexT(pos.x,pos.y,z,trp[v].u,trp[v].v,aColor);
						}
					}
				}

				static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aStartVertex,triCount*3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
				static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleList, triCount, aStartVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
			}
			else
			{
				VertexT aVertex[4] =
				{
					VertexT( x,				y,				z,	u1,v1, aColor),
					VertexT( x+aWidth,			y,				z,	u2,v1, aColor),
					VertexT( x,				y+aHeight,		z,	u1,v2, aColor),
					VertexT( x+aWidth,			y+aHeight,		z,	u2,v2, aColor)
				};

				static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aVertex,4,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
				static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
			}
		}

	// QZY end.

		TextureT GetTexture(MemoryImage* theOrigImage, int x, int y, int &width, int &height, float &u1, float &v1, float &u2, float &v2, TextureT &texMulti)
		{
			if (mImageFlags & (ImageFlag_CubeMap | ImageFlag_VolumeMap))
				return 0;
			
            int texIndex = 0;
            if ((x != 0) && (y != 0))
            {
                int tx = x/mTexPieceWidth;
                int ty = y/mTexPieceHeight;
                
                texIndex = ty*mTexVecWidth + tx;
            }
            TextureDataPiece &aPiece = mTextures[texIndex];
            
			
			int left = x%mTexPieceWidth;
			int top = y%mTexPieceHeight;
			int right = left+width;
			int bottom = top+height;
			
			if(right > aPiece.mWidth)
				right = aPiece.mWidth;
			
			if(bottom > aPiece.mHeight)
				bottom = aPiece.mHeight;
			
			width = right-left;
			height = bottom-top;
			
			if (mImageFlags & ImageFlag_Atlas)
			{
				u1 = (float)left / theOrigImage->mWidth;
				v1 = (float)top / theOrigImage->mHeight;
				u2 = (float)right / theOrigImage->mWidth;
				v2 = (float)bottom / theOrigImage->mHeight;
			}
			else
			{
				u1 = (float)left/aPiece.mWidth;
				v1 = (float)top/aPiece.mHeight;
				u2 = (float)right/aPiece.mWidth;
				v2 = (float)bottom/aPiece.mHeight;
			}
		
            texMulti = aPiece.mMultiTexture;
			return aPiece.mTexture;
		}
		
		TextureT GetTextureF(float x, float y, float &width, float &height, float &u1, float &v1, float &u2, float &v2, TextureT &texMulti)
		{
			if (mImageFlags & (ImageFlag_CubeMap | ImageFlag_VolumeMap))
				return 0;
			
			int tx = (int)(x / (float)mTexPieceWidth);
			int ty = (int)(y / (float)mTexPieceHeight);
			
			TextureDataPiece &aPiece = mTextures[ty*mTexVecWidth + tx];
			
			float left = x - tx*mTexPieceWidth;
			float top = y - ty*mTexPieceHeight;
			float right = left+width;
			float bottom = top+height;
			
			if (right > (float)aPiece.mWidth)
				right = (float)aPiece.mWidth;
			
			if (bottom > (float)aPiece.mHeight)
				bottom = (float)aPiece.mHeight;
			
			width = right-left;
			height = bottom-top;
			
			u1 = (float)left/aPiece.mWidth;
			v1 = (float)top/aPiece.mHeight;
			u2 = (float)right/aPiece.mWidth;
			v2 = (float)bottom/aPiece.mHeight;
			
            texMulti = aPiece.mMultiTexture;
			return aPiece.mTexture;
		}
		
		TextureT GetCubeTexture()
		{
			if (!(mImageFlags & ImageFlag_CubeMap))
				return NULL;
			
			return mTextures[0].mCubeTexture;
		}
		
		TextureT GetVolumeTexture()
		{
			if (!(mImageFlags & ImageFlag_VolumeMap))
				return NULL;
			
			return mTextures[0].mVolumeTexture;
		}
		
		void Blt(GenericRenderDevice* theDevice, MemoryImage* theImage, int theDrawMode, float theX, float theY, const Rect& theSrcRect, const Color& theColor)
		{
			DBG_ASSERTE(theDevice == mDevice);
			
			/*if (mTexMemFlushRevision < theDriver->mTexMemUsageFlushRevision)
			 {
			 theDriver->mTexMemUsageBytesCurFrame += mTexMemSize;
			 mTexMemFlushRevision = theInterface->mTexMemUsageFlushRevision;
			 }*/
			
			int srcLeft = theSrcRect.mX;
			int srcTop = theSrcRect.mY;
			int srcRight = srcLeft + theSrcRect.mWidth;
			int srcBottom = srcTop + theSrcRect.mHeight;
			int srcX, srcY;
			float dstX, dstY;
			int aWidth,aHeight;
			float u1,v1,u2,v2;
						
			srcY = srcTop;
			dstY = theY;
			
			uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);
			
			if ((srcLeft >= srcRight) || (srcTop >= srcBottom))
				return;
			
			//float z = (theInterface->mMaskWrite != Graphics3D::MASKWRITE_NONE) ? 0.25f : 0.5f;
			//float z = (theInterface->mMaskWrite != Graphics3D::MASKWRITE_NONE) ? theInterface->mMaskFrontDepth : theInterface->mMaskBackDepth;
			float z = static_cast<PlatformImplT*>(theDevice)->GetBltDepth();
			
			while(srcY < srcBottom)
			{
				srcX = srcLeft;
				dstX = theX;
				while(srcX < srcRight)
				{
					aWidth = srcRight-srcX;
					aHeight = srcBottom-srcY;
                    TextureT aTextureMulti;
					TextureT aTexture = GetTexture(theImage,srcX, srcY, aWidth, aHeight, u1, v1, u2, v2, aTextureMulti);
					
					if (mPaletteIndex != -1)
					{
						DBG_ASSERTE("NOT IMPLEMENTED"==0);
						//theDriver->mStateMgr->SetCurrentTexturePalette(mPaletteIndex);
					}
					static_cast<PlatformImplT*>(theDevice)->SetTextureStack(aTexture, aTextureMulti);
					
					float x = dstX + theDevice->mPixelOffset;
					float y = dstY + theDevice->mPixelOffset;
					
					// see about using a tri representation, if available and appropriate
					
					MemoryImage::TriRep::Tri* triUVs = NULL;
					int triCount = 0;
					if (PlatformImplT::SUPPORT_TRI_REP && mTextures.size() == 1)
					{
						float usageFrac = (float)(aWidth*aHeight) / (float)(theDevice->mWidth*theDevice->mHeight);
						MemoryImage::TriRep* triRep = theImage ? ((theDrawMode == Graphics::DRAWMODE_NORMAL) ? &theImage->mNormalTriRep : &theImage->mAdditiveTriRep) : NULL;
						MemoryImage::TriRep::Level* triRepLevel = triRep ? triRep->GetLevelForScreenSpaceUsage(usageFrac, false) : NULL;
						if (triRepLevel && theImage->HasImageFlag(ImageFlag_NoTriRep))
							triRepLevel = NULL;
#ifndef RELEASEFINAL
						if (theDevice->mRenderModeFlags & IGraphicsDriver::RENDERMODEF_NoTriRep)
							triRepLevel = NULL;
#endif
						if (triRepLevel)
						{
							triCount = 0;
							triUVs = triRepLevel->GetRegionTrisPtr(triCount, theImage, theSrcRect, false);
							if (triUVs==NULL) triCount = 0;
						}
					}
					if (PlatformImplT::SUPPORT_TRI_REP && triCount > 0)
					{
						// use tri representation
						VertexT* aTriVertex = (VertexT*)alloca(triCount*3*sizeof(VertexT));
						VertexT* aStartVertex = aTriVertex;
						MemoryImage::TriRep::Tri* aTriUV = triUVs;
						
						
						if ((u1==0.f) && (v1==0.f) && (u2==1.f) && (v2==1.f))
						{
							for (int q=0; q<triCount; ++q, aTriVertex += 3, ++aTriUV)
							{
								const MemoryImage::TriRep::Tri::Point* trp = aTriUV->p;
								
								for (int v=0; v<3; ++v)
								{
									aTriVertex[v] = VertexT(x+ aWidth*trp[v].u, y + aHeight*trp[v].v,z,
															trp[v].u,trp[v].v,aColor);
								}
							}
						}
						else
						{
							SexyVector2 uVector((float)aWidth, 0.f);
							SexyVector2 vVector(0.f, (float)aHeight);
							
							SexyVector2 basePos(x, y);
							if ((u1 != 0.0f) || (u2 != 1.0f))
							{
								float texDelta = u2 - u1;
								float ootexDelta = 1.f / texDelta;
								
								uVector *= ootexDelta;
								basePos -= uVector*u1;
							}
							if ((v1 != 0.0f) || (v2 != 1.0f))
							{
								float texDelta = v2 - v1;
								float ootexDelta = 1.f / texDelta;
								
								vVector *= ootexDelta;
								basePos -= vVector*v1;
							}
							
							for (int q=0; q<triCount; ++q, aTriVertex += 3, ++aTriUV)
							{
								const MemoryImage::TriRep::Tri::Point* trp = aTriUV->p;
								
								SexyVector2 pos;
								
								for (int v=0; v<3; ++v)
								{
									pos = basePos + uVector*trp[v].u + vVector*trp[v].v;
									
									aTriVertex[v] = VertexT(pos.x,pos.y,z,trp[v].u,trp[v].v,aColor);
								}					
							}
						}
						
						static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aStartVertex,triCount*3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
						static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleList, triCount, aStartVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
					}
					else
					{
						VertexT aVertex[4] = 
						{
							VertexT( x,				y,				z,	u1,v1, aColor),
							VertexT( x+aWidth,			y,				z,	u2,v1, aColor),
							VertexT( x,				y+aHeight,		z,	u1,v2, aColor),
							VertexT( x+aWidth,			y+aHeight,		z,	u2,v2, aColor)
						};
						
						static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aVertex,4,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
						static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
					}
					
					srcX += aWidth;
					dstX += aWidth;
				}
				
				srcY += aHeight;
				dstY += aHeight;
			}
		}
		
		void BltTransformed(GenericRenderDevice* theDevice, MemoryImage* theImage, int theDrawMode, const SexyMatrix3 &theTrans, const Rect& theSrcRect, const Color& theColor, const Rect *theClipRect = NULL, float theX = 0, float theY = 0, bool center = false)
		{
			DBG_ASSERTE(theDevice == mDevice);
			
			SEXY_AUTO_PERF("BltTransformed::ALL");

			/*if (mTexMemFlushRevision < theInterface->mTexMemUsageFlushRevision)
			 {
			 theInterface->mTexMemUsageBytesCurFrame += mTexMemSize;
			 mTexMemFlushRevision = theInterface->mTexMemUsageFlushRevision;
			 }*/
			
			int srcLeft = theSrcRect.mX;
			int srcTop = theSrcRect.mY;
			int srcRight = srcLeft + theSrcRect.mWidth;
			int srcBottom = srcTop + theSrcRect.mHeight;
			int srcX, srcY;
			float dstX, dstY;
			int aWidth;
			int aHeight;
			float u1,v1,u2,v2;
			float startx = 0, starty = 0;
			float pixelcorrect = -theDevice->mPixelOffset;
			
			if (center)
			{
				startx = -theSrcRect.mWidth/2.0f;
				starty = -theSrcRect.mHeight/2.0f;
				pixelcorrect = 0.0f;
			}			
			
			srcY = srcTop;
			dstY = starty;
			
			uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);			
			
			if ((srcLeft >= srcRight) || (srcTop >= srcBottom))
				return;
            
			//float z = (theInterface->mMaskWrite != Graphics3D::MASKWRITE_NONE) ? 0.25f : 0.5f;
			//float z = (theInterface->mMaskWrite != Graphics3D::MASKWRITE_NONE) ? theInterface->mMaskFrontDepth : theInterface->mMaskBackDepth;
			float z = static_cast<PlatformImplT*>(theDevice)->GetBltDepth();
			
			while(srcY < srcBottom)
			{
				srcX = srcLeft;
				dstX = startx;
				while(srcX < srcRight)
				{
					aWidth = srcRight-srcX;
					aHeight = srcBottom-srcY;
                    TextureT aTextureMulti;
					TextureT aTexture = GetTexture(theImage,srcX, srcY, aWidth, aHeight, u1, v1, u2, v2, aTextureMulti);
					
					//if (mPaletteIndex != -1)
					//	theDriver->mStateMgr->SetCurrentTexturePalette(mPaletteIndex);
					static_cast<PlatformImplT*>(theDevice)->SetTextureStack(aTexture, aTextureMulti);
					
					float x = dstX; // - 0.5f;
					float y = dstY; // - 0.5f;
					
					SexyVector2 p[4] = { SexyVector2(x, y), SexyVector2(x+aWidth, y), SexyVector2(x,y+aHeight), SexyVector2(x+aWidth, y+aHeight) };
					SexyVector2 tp[4];
					
					int i;
					for (i=0; i<4; i++)
					{
						tp[i].x = p[i].x*theTrans.m00 + p[i].y*theTrans.m01 + theTrans.m02;
						tp[i].y = p[i].x*theTrans.m10 + p[i].y*theTrans.m11 + theTrans.m12;
						tp[i].x -= pixelcorrect - theX;
						tp[i].y -= pixelcorrect - theY;
					}
					
					VertexT aVertex[4] = 
					{
						VertexT( tp[0].x,				tp[0].y,			z,	u1,v1,	aColor),
						VertexT( tp[1].x,				tp[1].y,			z,	u2,v1,	aColor),
						VertexT( tp[2].x,				tp[2].y,			z,	u1,v2,	aColor),
						VertexT( tp[3].x,				tp[3].y,			z,	u2,v2,	aColor),
					};
					
					const Rect* aClipRect = theClipRect;
					
					bool clipped = false;
					if (!PlatformImplT::SUPPORT_HW_CLIP &&
						(aClipRect != NULL) && // Don't clip if cliprect is the screen...
						((aClipRect->mX != 0) || (aClipRect->mY != 0) || (aClipRect->mWidth != theDevice->mScreenWidth) || (aClipRect->mHeight != theDevice->mScreenHeight)))
					{
						static Rect aNewClipRect;

						SexyVector2 v1a((float)aClipRect->mX, (float)aClipRect->mY);
						SexyVector2 v2a((float)(aClipRect->mX + aClipRect->mWidth), (float)(aClipRect->mY +aClipRect->mHeight));

						/*int left = aClipRect->mX;
						int right = left + aClipRect->mWidth;
						int top = aClipRect->mY;
						int bottom = top + aClipRect->mHeight;*/

						if (static_cast<PlatformImplT*>(theDevice)->mTransformStack.size() != 0)
						{
							v1a = static_cast<PlatformImplT*>(theDevice)->mTransformStack.back()*v1a;
							v2a = static_cast<PlatformImplT*>(theDevice)->mTransformStack.back()*v2a;
						}

						for (i=0; i<4; i++)
						{
							if (tp[i].x<v1a.x || tp[i].x>=v2a.x || tp[i].y<v1a.y || tp[i].y>=v2a.y)
							{
								aNewClipRect.mX = (int)v1a.x;
								aNewClipRect.mY = (int)v1a.y;
								aNewClipRect.mWidth = (int)(v2a.x-v1a.x);
								aNewClipRect.mHeight = (int)(v2a.y-v1a.y);
								aClipRect = &aNewClipRect;

								clipped = true;
								break;
							}
						}
					}

					if (PlatformImplT::SUPPORT_HW_CLIP || !clipped)
					{
						// see about using a tri representation, if available and appropriate
						
						// initial u/v vectors start in screen space
						SexyVector2 uVector = tp[1] - tp[0];
						SexyVector2 vVector = tp[2] - tp[0];
						SexyVector2 basePos = tp[0];
						MemoryImage::TriRep::Tri* triUVs = NULL;
						
						
						int triCount = 0;
						bool didTriReps = false;
						if (PlatformImplT::SUPPORT_TRI_REP)
						{
							// compute usage frac before we muck with the u/v vectors
							float usageFrac = (uVector.Magnitude() * vVector.Magnitude()) / (float)(theDevice->mWidth*theDevice->mHeight);
							
							// adjust tri base position and u/v vector length based on src u/v rect
							
							if ((u1 != 0.0f) || (u2 != 1.0f))
							{
								float texDelta = u2 - u1;
								float ootexDelta = 1.f / texDelta;
								
								uVector *= ootexDelta;
								basePos -= uVector*u1;
							}
							if ((v1 != 0.0f) || (v2 != 1.0f))
							{
								float texDelta = v2 - v1;
								float ootexDelta = 1.f / texDelta;
								
								vVector *= ootexDelta;
								basePos -= vVector*v1;
							}
							
							
							//bool checkFilter = false;
							if (mTextures.size() == 1)
							{
								bool isRotated = (SexyMath::Fabs(float(uVector.y)) > SEXYMATH_EPSILONSQ) || (SexyMath::Fabs(float(vVector.x)) > SEXYMATH_EPSILONSQ);
								MemoryImage::TriRep* triRep = theImage ? ((theDrawMode == Graphics::DRAWMODE_NORMAL) ? &theImage->mNormalTriRep : &theImage->mAdditiveTriRep) : NULL;
								MemoryImage::TriRep::Level* triRepLevel = triRep ? triRep->GetLevelForScreenSpaceUsage(usageFrac, isRotated) : NULL;
								if (triRepLevel && theImage->HasImageFlag(ImageFlag_NoTriRep))
									triRepLevel = NULL;
	#ifndef RELEASEFINAL
								if (theDevice->mRenderModeFlags & IGraphicsDriver::RENDERMODEF_NoTriRep)
									triRepLevel = NULL;
	#endif
								if (triRepLevel)
								{
									triCount = 0;
									triUVs = triRepLevel->GetRegionTrisPtr(triCount, theImage, theSrcRect, isRotated);
									if (triUVs==NULL) triCount = 0;
								}
							}
							
							if (triCount > 0)
							{
								// use tri representation
								VertexT* aTriVertex = (VertexT*)alloca(triCount*3*sizeof(VertexT));
								VertexT* aStartVertex = aTriVertex;
								MemoryImage::TriRep::Tri* aTriUV = triUVs;
								
								// enable filter checking only when the usage is great enough to justify it, or the tri count is low enough that it shouldn't cost too much
								//TODO filters
								/*if ((theDriver->mBltFilter != NULL) && ((usageFrac > 0.125f) || (triCount < 40)))
								 checkFilter = true;*/

								int finalTriCount = triCount; // final count excludes any tris that are filtered out
								for (int q=0; q<triCount; ++q, aTriVertex += 3, ++aTriUV)
								{
									const MemoryImage::TriRep::Tri::Point* trp = aTriUV->p;
									
									SexyVector2 pos;
									
									for (int v=0; v<3; ++v)
									{
										pos.x = basePos.x + uVector.x*trp[v].u + vVector.x*trp[v].v;
										pos.y = basePos.y + uVector.y*trp[v].u + vVector.y*trp[v].v;
										
										aTriVertex[v] = VertexT(pos.x,pos.y,z,trp[v].u,trp[v].v,aColor);
									}
									
									/*if (checkFilter)
									 {
									 const Rect* aUnusedRect;
									 if (!theInterface->mBltFilter(theInterface->mBltFilterContext, Graphics3D::PT_TriangleList, 1, (SexyVertex2D*)aTriVertex, D3DInterface::DEFAULT_VERTEX_SIZE, &aUnusedRect))
									 {
									 // tri was rejected, lower the final count and backtrack in the output vert array
									 aTriVertex -= 3;
									 --finalTriCount;
									 }
									 }*/
								}
								
								static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aStartVertex,finalTriCount*3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
								static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleList, finalTriCount, aStartVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
								didTriReps = true;
							}
						}
						
						if (!didTriReps)
						{
							static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aVertex,4,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
							static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
						}
					}
					else
					{
						static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aVertex,4,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
						VertexTList aList;
						aList.push_back(aVertex[0]);
						aList.push_back(aVertex[1]);
						aList.push_back(aVertex[3]);
						aList.push_back(aVertex[2]);
						
						theDevice->DrawPolyClipped(aClipRect, aList);
					}
					
					srcX += aWidth;
					dstX += aWidth;
				}
				
				srcY += aHeight;
				dstY += aHeight;
			}
		}
		
#if OPTIMIZE_ANIM_DRAW
		void BltTransformedOptimized(GenericRenderDevice* theDevice, MemoryImage* theImage, int theDrawMode, const SexyMatrix3 &theTrans, const Color& theColor, const Rect *theClipRect, MATH_TYPE theX, MATH_TYPE theY, bool bNeedUpdateImage)
		{
			DBG_ASSERTE(theDevice == mDevice);

			DeviceImage::CachedImageDrawInfo & cachedInfo = static_cast<DeviceImage*>(theImage)->GetCachedInfo();
			const Rect& theSrcRect = cachedInfo.GetSrcRect();
			if ((theSrcRect.mWidth<=0) || (theSrcRect.mHeight<=0))
				return;

			//SEXY_AUTO_PERF("BltTransformedOptimized::ALL");

			float z = static_cast<PlatformImplT*>(theDevice)->GetBltDepth();
			uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);
			{
				//Update data to check if cache dirty.
				/*
				// mTextures should never change, do not check this to reduce test cost.
				int size = mTextures.size();
				std::vector<int> vecWidth;
				std::vector<int> vecHeight;
				vecWidth.resize(size);
				vecHeight.resize(size);
				for( int i = 0 ; i < size ; i++)
				{
					TextureDataPiece &aPiece = mTextures[i];
					vecWidth[i] = aPiece.mWidth;
					vecHeight[i] = aPiece.mHeight;
				}
				cachedInfo.UpdateTextureListData(vecWidth,vecHeight);
				*/
				cachedInfo.UpdateTextureData(mTexPieceWidth,mTexPieceHeight,theImage->mWidth,theImage->mHeight, mImageFlags&ImageFlag_Atlas);
			}
			static Rect aNewClipRect;
			MATH_TYPE translatedTheX = MATH_TYPE(theX);
			MATH_TYPE translatedTheY = MATH_TYPE(theY);
			if(cachedInfo.IsDirty())
			{
				int srcLeft;
				int srcTop;
				int srcRight;
				int srcBottom;

				int srcX, srcY;
				MATH_TYPE dstX, dstY;
				int aWidth;
				int aHeight;
				MATH_TYPE startx;
				MATH_TYPE starty;
				srcLeft = theSrcRect.mX;
				srcTop = theSrcRect.mY;
				srcRight = srcLeft + theSrcRect.mWidth;
				srcBottom = srcTop + theSrcRect.mHeight;
				startx = -theSrcRect.mWidth/2.0f;
				starty = -theSrcRect.mHeight/2.0f;
				srcY = srcTop;
				dstY = starty;
				//SEXY_AUTO_PERF("BltTransformedOptimized::Dirty");
				DeviceImage::CachedResultVector resultVector;
				
				theDevice->SetupAtlasState(0, theImage);
				while(srcY < srcBottom)
				{
					srcX = srcLeft;
					dstX = startx;
					while(srcX < srcRight)
					{
						float u1,v1,u2,v2;
						aWidth = srcRight-srcX;
						aHeight = srcBottom-srcY;
						TextureT aTextureMulti;
						TextureT aTexture = GetTexture(theImage,srcX, srcY, aWidth, aHeight, u1, v1, u2, v2, aTextureMulti);

						//if (mPaletteIndex != -1)
						//	theDriver->mStateMgr->SetCurrentTexturePalette(mPaletteIndex);
						static_cast<PlatformImplT*>(theDevice)->SetTextureStack(aTexture, aTextureMulti);

						MATH_TYPE x = dstX; // - 0.5f;
						MATH_TYPE y = dstY; // - 0.5f;

						SexyVector2 p[4] = { SexyVector2(x, y), SexyVector2(x+aWidth, y), SexyVector2(x,y+aHeight), SexyVector2(x+aWidth, y+aHeight) };
						SexyVector2 tp[4];

						for (int i=0; i<4; i++)
						{
							tp[i].x = p[i].x*theTrans.m00 + p[i].y*theTrans.m01 + theTrans.m02 + translatedTheX;
							tp[i].y = p[i].x*theTrans.m10 + p[i].y*theTrans.m11 + theTrans.m12 + translatedTheY;
						}

						VertexT aVertex[4] =
						{
							VertexT( tp[0].x,				tp[0].y,			z,	u1,v1,	aColor),
							VertexT( tp[1].x,				tp[1].y,			z,	u2,v1,	aColor),
							VertexT( tp[2].x,				tp[2].y,			z,	u1,v2,	aColor),
							VertexT( tp[3].x,				tp[3].y,			z,	u2,v2,	aColor),
						};
						static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,aVertex,4,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());

						const Rect* aClipRect = theClipRect;

						// PlatformImplT::SUPPORT_HW_CLIP is always false right now.

						//mTransformStack support is removed. This was not used for PopAnim. So there is no need to update clipRect.

						// PlatformImplT::SUPPORT_TRI_REP is false, remove code for this.

						bool clipped = false;
						if ((aClipRect != NULL) && // Don't clip if cliprect is the screen...
							((aClipRect->mX != 0) || (aClipRect->mY != 0) || (aClipRect->mWidth != theDevice->mScreenWidth) || (aClipRect->mHeight != theDevice->mScreenHeight)))
						{
							SexyVector2 v1a(aClipRect->mX, aClipRect->mY);
							SexyVector2 v2a((aClipRect->mX + aClipRect->mWidth), (aClipRect->mY +aClipRect->mHeight));
							for (int i=0; i<4; i++)
							{
								if (tp[i].x<v1a.x || tp[i].x>=v2a.x || tp[i].y<v1a.y || tp[i].y>=v2a.y)
								{
									aNewClipRect.mX = (int)v1a.x;
									aNewClipRect.mY = (int)v1a.y;
									aNewClipRect.mWidth = (int)(v2a.x-v1a.x);
									aNewClipRect.mHeight = (int)(v2a.y-v1a.y);
									aClipRect = &aNewClipRect;

									clipped = true;
									break;
								}
							}
						}

						if (!clipped)
						{
							static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
						}
						else
						{
							VertexTList aList;
							aList.push_back(aVertex[0]);
							aList.push_back(aVertex[1]);
							aList.push_back(aVertex[3]);
							aList.push_back(aVertex[2]);

							theDevice->DrawPolyClipped(aClipRect, aList);
						}

						DeviceImage::CachedResult result;
						result.u1 = aVertex[0].u; result.v1 = aVertex[0].v; result.u2 = aVertex[3].u; result.v2 = aVertex[3].v;
						result.dstX = dstX; result.dstY = dstY;
						result.aWidth = aWidth; result.aHeight = aHeight;
						{
							result.texIndex = 0;
							if ((srcX != 0) && (srcY != 0))
							{
								int tx = srcX/mTexPieceWidth;
								int ty = srcY/mTexPieceHeight;

								result.texIndex = ty*mTexVecWidth + tx;
							}
						}
						resultVector.push_back(result);


						srcX += aWidth;
						dstX += aWidth;
					}

					srcY += aHeight;
					dstY += aHeight;
				}
				cachedInfo.SaveResult(resultVector);
			}
			else
			{
				//SEXY_AUTO_PERF("BltTransformedOptimized::Cached");
				const DeviceImage::CachedResultVector & result = cachedInfo.GetResult();
				auto size = result.size();
				MATH_TYPE deltaX = theTrans.m02 + translatedTheX;
				MATH_TYPE deltaY = theTrans.m12 + translatedTheY;
				for(int i = 0 ; i < size; i++)
				{
					const DeviceImage::CachedResult& rResult = result[i];

					if(bNeedUpdateImage)
					{
						TextureDataPiece &aPiece = mTextures[rResult.texIndex];
						static_cast<PlatformImplT*>(theDevice)->SetTextureStack(aPiece.mTexture, aPiece.mMultiTexture);
					}
					SexyVector2 p[4] = { SexyVector2(rResult.dstX, rResult.dstY), SexyVector2(rResult.dstX+rResult.aWidth, rResult.dstY), SexyVector2(rResult.dstX,rResult.dstY+rResult.aHeight), SexyVector2(rResult.dstX+rResult.aWidth, rResult.dstY+rResult.aHeight) };
					SexyVector2 tp[4];


					for (int j = 0; j < 4; j++)
					{
						tp[j].x = p[j].x*theTrans.m00 + p[j].y*theTrans.m01 + deltaX;
						tp[j].y = p[j].x*theTrans.m10 + p[j].y*theTrans.m11 + deltaY;
					}

					VertexT aVertex[4] =
					{
						VertexT( tp[0].x,				tp[0].y,			z,	rResult.u1,rResult.v1,	aColor),
						VertexT( tp[1].x,				tp[1].y,			z,	rResult.u2,rResult.v1,	aColor),
						VertexT( tp[2].x,				tp[2].y,			z,	rResult.u1,rResult.v2,	aColor),
						VertexT( tp[3].x,				tp[3].y,			z,	rResult.u2,rResult.v2,	aColor),
					};
					{
						const Rect* aClipRect = theClipRect;
						bool clipped = false;
						{
							//SEXY_AUTO_PERF("BltTransformedOptimized::Clip");
							if ((aClipRect != NULL) && // Don't clip if cliprect is the screen...
								((aClipRect->mX != 0) || (aClipRect->mY != 0) || (aClipRect->mWidth != theDevice->mScreenWidth) || (aClipRect->mHeight != theDevice->mScreenHeight)))
							{
		
								SexyVector2 v1a(aClipRect->mX, aClipRect->mY);
								SexyVector2 v2a((aClipRect->mX + aClipRect->mWidth), (aClipRect->mY +aClipRect->mHeight));
								for (int ii=0; ii<4; ii++)
								{
									if (tp[ii].x<v1a.x || tp[ii].x>=v2a.x || tp[ii].y<v1a.y || tp[ii].y>=v2a.y)
									{
										aNewClipRect.mX = (int)v1a.x;
										aNewClipRect.mY = (int)v1a.y;
										aNewClipRect.mWidth = (int)(v2a.x-v1a.x);
										aNewClipRect.mHeight = (int)(v2a.y-v1a.y);
										aClipRect = &aNewClipRect;
		
										clipped = true;
										break;
									}
								}
							}
						}

						{
							//SEXY_AUTO_PERF("BltTransformedOptimized::Draw");
							if (!clipped)
							{
								static_cast<PlatformImplT*>(theDevice)->BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, theDevice->mDefaultVertexSize, theDevice->mDefaultVertexFVF);
							}
							else
							{
								VertexTList aList;
								aList.push_back(aVertex[0]);
								aList.push_back(aVertex[1]);
								aList.push_back(aVertex[3]);
								aList.push_back(aVertex[2]);
                                
								theDevice->DrawPolyClipped(aClipRect, aList);
							}
						}
					}
				}
			}
		}
#endif //OPTIMIZE_ANIM_DRAW
#define GetColorFromSexyVertex(theVertex, theColor) (theVertex.color?theVertex.color:theColor)
		void BltTriangles(GenericRenderDevice* theDevice, MemoryImage* theImage, const TriVertex theVertices[][3], int theNumTriangles, uint32 theColor, float tx = 0, float ty = 0, const Rect* theClipRect = NULL)
		{	
			DBG_ASSERT(theDevice == mDevice);
            
			
            
            //prefetch (add macros for other platforms)
#ifdef HOST_IPHONEOS
            __builtin_prefetch(theVertices,0); //readonly
            __builtin_prefetch(theDevice->mBatchedTriangleBuffer + theDevice->mBatchedTriangleIndex,1); //readwrite
#endif
			
			
			if ((mMaxTotalU <= 1.0) && (mMaxTotalV <= 1.0))
			{
                static_cast<PlatformImplT*>(theDevice)->SetTextureStack(mTextures[0].mTexture, mTextures[0].mTexture);
				
				float z = static_cast<PlatformImplT*>(theDevice)->GetBltDepth();
				
				bool doxform = !theDevice->mTransformStack.empty();
				
				bool doClipping = theClipRect!=NULL && ((theClipRect->mX != 0) || (theClipRect->mY != 0) || (theClipRect->mWidth != theDevice->mScreenWidth) || (theClipRect->mHeight != theDevice->mScreenHeight));
				
				theDevice->CheckBatchAndCommit();
				
				if (doxform)
				{
					SexyMatrix3& theTrans = theDevice->mTransformStack.back();
					for (int aTriangleNum = 0; aTriangleNum < theNumTriangles; aTriangleNum++)
					{
						if (theDevice->mBatchedTriangleIndex > theDevice->mBatchedTriangleSize-3)
						{
							theDevice->FlushBufferedTriangles();
						}
						
						TriVertex* aTriVerts = (TriVertex*) theVertices[aTriangleNum];
						
						//todo... batch vector process this 
						SexyVector2 p[3];
						p[0].x = aTriVerts[0].x + tx;
						p[0].y = aTriVerts[0].y + ty;
						p[1].x = aTriVerts[1].x + tx;
						p[1].y = aTriVerts[1].y + ty;
						p[2].x = aTriVerts[2].x + tx;
						p[2].y = aTriVerts[2].y + ty;
						
						
						p[0].x = p[0].x*theTrans.m00 + p[0].y*theTrans.m01 + theTrans.m02;
						p[0].y = p[0].x*theTrans.m10 + p[0].y*theTrans.m11 + theTrans.m12;
						
						p[1].x = p[1].x*theTrans.m00 + p[1].y*theTrans.m01 + theTrans.m02;
						p[1].y = p[1].x*theTrans.m10 + p[1].y*theTrans.m11 + theTrans.m12;
						
						p[2].x = p[2].x*theTrans.m00 + p[2].y*theTrans.m01 + theTrans.m02;
						p[2].y = p[2].x*theTrans.m10 + p[2].y*theTrans.m11 + theTrans.m12;
						
						theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(p[0].x,
																										p[0].y,
																										z,
																										aTriVerts[0].u * mMaxTotalU,
																										aTriVerts[0].v * mMaxTotalV,
																										aTriVerts[0].color?VertexT::PackColor((aTriVerts[0].color>>16)&0xFF,
																																			  (aTriVerts[0].color>> 8)&0xFF,
																																			  (aTriVerts[0].color    )&0xFF,
																																			  (aTriVerts[0].color>>24)&0xFF):theColor);
						
						theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(p[1].x,
																										p[1].y,
																										z,
																										aTriVerts[1].u * mMaxTotalU,
																										aTriVerts[1].v * mMaxTotalV,
																										aTriVerts[1].color?VertexT::PackColor((aTriVerts[1].color>>16)&0xFF,
																																			  (aTriVerts[1].color>> 8)&0xFF,
																																			  (aTriVerts[1].color    )&0xFF,
																																			  (aTriVerts[1].color>>24)&0xFF):theColor);
						
						
						theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(p[2].x,
																										p[2].y,
																										z,
																										aTriVerts[2].u * mMaxTotalU,
																										aTriVerts[2].v * mMaxTotalV,
																										aTriVerts[2].color?VertexT::PackColor((aTriVerts[2].color>>16)&0xFF,
																																			  (aTriVerts[2].color>> 8)&0xFF,
																																			  (aTriVerts[2].color    )&0xFF,
																																			  (aTriVerts[2].color>>24)&0xFF):theColor);

						
						//TODO: attempt to inline the atlas math so that this can be done faster
						// as an alt... this could bookend the loop so that more processing could be done at once
						static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,theDevice->mBatchedTriangleBuffer + (theDevice->mBatchedTriangleIndex-3),3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
													   
						if (!PlatformImplT::SUPPORT_HW_CLIP && doClipping)
						{	
							
							VertexTList aList;
							aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-3]);
							aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-2]);
							aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-1]);	
							//back out the list 3 verts
							theDevice->mBatchedTriangleIndex-=3;
							theDevice->DrawPolyClipped(theClipRect, aList);						
						}
					}
				}
				else
				{
                    if (!PlatformImplT::SUPPORT_HW_CLIP && doClipping)
                    {
                        for (int aTriangleNum = 0; aTriangleNum < theNumTriangles; aTriangleNum++)
                        {
                            if (theDevice->mBatchedTriangleIndex > theDevice->mBatchedTriangleSize-3)
                                static_cast<PlatformImplT*>(theDevice)->FlushBufferedTriangles();
                            
                            
                            TriVertex* aTriVerts = (TriVertex*) theVertices[aTriangleNum];
                            
                            theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[0].x + tx,
                                                                                                            aTriVerts[0].y + ty,
                                                                                                            z,
                                                                                                            aTriVerts[0].u * mMaxTotalU,
                                                                                                            aTriVerts[0].v * mMaxTotalV,
                                                                                                            aTriVerts[0].color?VertexT::PackColor((aTriVerts[0].color>>16)&0xFF,
                                                                                                                                                  (aTriVerts[0].color>> 8)&0xFF,
                                                                                                                                                  (aTriVerts[0].color    )&0xFF,
                                                                                                                                                  (aTriVerts[0].color>>24)&0xFF):theColor);
                            
                            theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[1].x + tx,
                                                                                                            aTriVerts[1].y + ty,
                                                                                                            z,
                                                                                                            aTriVerts[1].u * mMaxTotalU,
                                                                                                            aTriVerts[1].v * mMaxTotalV,
                                                                                                            aTriVerts[1].color?VertexT::PackColor((aTriVerts[1].color>>16)&0xFF,
                                                                                                                                                  (aTriVerts[1].color>> 8)&0xFF,
                                                                                                                                                  (aTriVerts[1].color    )&0xFF,
                                                                                                                                                  (aTriVerts[1].color>>24)&0xFF):theColor);
                            
                            
                            theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[2].x + tx,
                                                                                                            aTriVerts[2].y + ty,
                                                                                                            z,
                                                                                                            aTriVerts[2].u * mMaxTotalU,
                                                                                                            aTriVerts[2].v * mMaxTotalV,
                                                                                                            aTriVerts[2].color?VertexT::PackColor((aTriVerts[2].color>>16)&0xFF,
                                                                                                                                                  (aTriVerts[2].color>> 8)&0xFF,
                                                                                                                                                  (aTriVerts[2].color    )&0xFF,
                                                                                                                                                  (aTriVerts[2].color>>24)&0xFF):theColor);
                            
                            
                            static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,theDevice->mBatchedTriangleBuffer + (theDevice->mBatchedTriangleIndex-3),3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
                            
                            if (!PlatformImplT::SUPPORT_HW_CLIP && doClipping)
                            {	
                                
                                VertexTList aList;
                                aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-3]);
                                aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-2]);
                                aList.push_back(theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex-1]);	
                                //back out the list 3 verts
                                theDevice->mBatchedTriangleIndex-=3;
                                theDevice->DrawPolyClipped(theClipRect, aList);						
                            }
                        }
                    }
                    else
                    {
                        int aTriangleNum = 0;
                        while (aTriangleNum < theNumTriangles)
                        {
                            
                            
                             if ((theDevice->mBatchedTriangleIndex + 3) >= theDevice->mBatchedTriangleSize)
                            {
                                 //theDevice->AdjustVertsForAtlas(0,theDevice->mBatchedTriangleBuffer + (batchStart),numSubmittedTris*3,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
                                 theDevice->FlushBufferedTriangles();
                            }

                            uint32 batchStart = theDevice->mBatchedTriangleIndex;
                            uint32 numSubmittedVerts = 0;
							int vertSpace = (int)(theDevice->mBatchedTriangleSize-theDevice->mBatchedTriangleIndex);

                            uint32 vertCount = min(vertSpace, (theNumTriangles-aTriangleNum)*3);

                            while ((numSubmittedVerts+3) <= vertCount)
                            {
                                //prefetch (add macros for other platforms)
#ifdef HOST_IPHONEOS
//num triangles to prefetch (should be tuned per platform)
#define LOOKAHEAD 8
                                __builtin_prefetch(theVertices + aTriangleNum + LOOKAHEAD,0); //readonly
                                __builtin_prefetch(theDevice->mBatchedTriangleBuffer + theDevice->mBatchedTriangleIndex + (LOOKAHEAD*3),1); //readwrite
#endif

                                TriVertex* aTriVerts = (TriVertex*) theVertices[aTriangleNum];
                                
                                PRIME_ASSERT(theDevice->mBatchedTriangleSize-theDevice->mBatchedTriangleIndex >= 3);
                                
                                theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[0].x + tx,
                                                                                                                aTriVerts[0].y + ty,
                                                                                                                z,
                                                                                                                aTriVerts[0].u * mMaxTotalU,
                                                                                                                aTriVerts[0].v * mMaxTotalV,
                                                                                                                aTriVerts[0].color?VertexT::PackColor((aTriVerts[0].color>>16)&0xFF,
                                                                                                                                                      (aTriVerts[0].color>> 8)&0xFF,
                                                                                                                                                      (aTriVerts[0].color    )&0xFF,
                                                                                                                                                      (aTriVerts[0].color>>24)&0xFF):theColor);
                                
                                theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[1].x + tx,
                                                                                                                aTriVerts[1].y + ty,
                                                                                                                z,
                                                                                                                aTriVerts[1].u * mMaxTotalU,
                                                                                                                aTriVerts[1].v * mMaxTotalV,
                                                                                                                aTriVerts[1].color?VertexT::PackColor((aTriVerts[1].color>>16)&0xFF,
                                                                                                                                                      (aTriVerts[1].color>> 8)&0xFF,
                                                                                                                                                      (aTriVerts[1].color    )&0xFF,
                                                                                                                                                      (aTriVerts[1].color>>24)&0xFF):theColor);
                                
                                
                                theDevice->mBatchedTriangleBuffer[theDevice->mBatchedTriangleIndex++] = VertexT(aTriVerts[2].x + tx,
                                                                                                                aTriVerts[2].y + ty,
                                                                                                                z,
                                                                                                                aTriVerts[2].u * mMaxTotalU,
                                                                                                                aTriVerts[2].v * mMaxTotalV,
                                                                                                                aTriVerts[2].color?VertexT::PackColor((aTriVerts[2].color>>16)&0xFF,
                                                                                                                                                      (aTriVerts[2].color>> 8)&0xFF,
                                                                                                                                                      (aTriVerts[2].color    )&0xFF,
                                                                                                                                                      (aTriVerts[2].color>>24)&0xFF):theColor);
                                numSubmittedVerts+=3;
                                aTriangleNum++;
                            }
                            static_cast<PlatformImplT*>(theDevice)->AdjustVertsForAtlas(0,theDevice->mBatchedTriangleBuffer + (batchStart),numSubmittedVerts,VertexT::FVF,theDevice->mDefaultVertexSize,VertexT::TexCoordOffset());
                        }
                    }

#ifndef RELEASEFINAL
					if (theDevice->mBatchedTriangleIndex > 0 && theDevice->mRenderModeFlags & IGraphicsDriver::RENDERMODEF_NoBatching)
					{
						theDevice->DrawPrimitiveInternal(Graphics3D::PT_TriangleList, theDevice->mBatchedTriangleIndex/3, theDevice->mBatchedTriangleBuffer, sizeof(VertexT), VertexT::FVF);
						theDevice->mBatchedTriangleIndex=0;
					}
#endif
				}
				
				
				
			}
		}
		
	};
	
	
	
	
	
	typedef std::vector<SexyMatrix3> TransformStack;
	typedef std::set<MemoryImage*> ImageSet;
	typedef std::vector<int> IntVector;
	
public:
	bool				mSceneBegun;
	
	TransformStack		mTransformStack;
	VertexT*			mBatchedTriangleBuffer;
	uint32_t			mBatchedTriangleIndex;
	uint32_t			mBatchedTriangleSize;
	IGraphicsDriver*	mGraphicsDriver;
	ImageSet			mImageSet;
	
	BaseRenderDevice(IGraphicsDriver* theDriver)
	{
		mGraphicsDriver = theDriver;
		mBatchedTriangleIndex = 0;
		mBatchedTriangleSize = 0;
		mBatchedTriangleBuffer = NULL;
		mSceneBegun = false;
		mRenderTargetMustBePow2 = false;
		
#ifndef RELEASEFINAL
		mMetrics = NULL;
#endif
	}
	
	RenderDevice3D* Get3D() 
	{
		return this;
	}
	
	bool CanFillPoly()
	{
		return true;
	}

	
	//HRenderContext CreateContext(Image* theDestImage, const HRenderContext& theSourceContext = HRenderContext((void*)0));
	//void DeleteContext(const HRenderContext& theContext);
	//void SetCurrentContext(const HRenderContext& theContext);
	//HRenderContext GetCurrentContext() const;
	//void PushState();
	//void PopState();
	
	/**
	 * JVW - looks like this is only implemented for Software on Windows...
	 * I might move the MemoryImage or not decision into Graphics
	 */
	void ClearRect(const Rect& theRect)
	{
	}
	
	void FillRect(const Rect& theRect, const Color& theColor, int theDrawMode)
	{
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		
		uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);			
		float x = (float)theRect.mX + mPixelOffset ; //extra half pixel offset? would this be better if TransformStack is empty 
		float y = (float)theRect.mY + mPixelOffset ;
		float aWidth = (float)theRect.mWidth;
		float aHeight = (float)theRect.mHeight;
		
		float z = static_cast<PlatformImplT*>(this)->GetBltDepth();
		
		VertexT aVertex[4] = 
		{
			VertexT( x,				y,				z,	0,0,	aColor),
			VertexT( x+aWidth,		y,				z,	0,0,	aColor),
			VertexT( x,				y+aHeight,		z,	0,0,	aColor),
			VertexT( x+aWidth,		y+aHeight,		z,	0,0,	aColor)
		};
		
		
		if (!mTransformStack.empty())
		{
			SexyVector2 p[4] = { SexyVector2(x, y), SexyVector2(x,y+aHeight), SexyVector2(x+aWidth, y) , SexyVector2(x+aWidth, y+aHeight) };
			
			int i;
			for (i=0; i<4; i++)
			{
				p[i] = mTransformStack.back()*p[i];
				
				//JVW -I assume this is the half-pixel offset for DirectX, which isn't neccessary for GL
				p[i].x += mPixelOffset;   
				p[i].y += mPixelOffset;
				aVertex[i].SetPosition(p[i].x,p[i].y,z);
			}
		}
		
		
		static_cast<PlatformImplT*>(this)->SetTextureSingle(0, 0);
		BufferedDrawPrimitive(Graphics3D::PT_TriangleStrip, 2, aVertex, mDefaultVertexSize, mDefaultVertexFVF);		
	}
	
	void FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const uint8* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight)
	{
	}
	
	void FillPoly(const Point theVertices[], int theNumVertices, const Rect *theClipRect, const Color &theColor, int theDrawMode, int tx, int ty)
	{
		if (theNumVertices<3)
			return;
		
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);			
		
		float z = static_cast<PlatformImplT*>(this)->GetBltDepth();
		
		VertexTList aList;
		for (int i=0; i<theNumVertices; i++)
		{
			VertexT vert = 	VertexT( theVertices[i].mX + (float)tx, theVertices[i].mY + (float)ty,	z,	0,0,	aColor);
			if (!mTransformStack.empty())
			{
				SexyVector2 v(vert.x,vert.y);
				v = mTransformStack.back()*v;
				vert.SetPosition(v.x,v.y,z);
			}
			
			aList.push_back(vert);
		}
		
		if (theClipRect != NULL)
			DrawPolyClipped(theClipRect, aList);
		else
		{
			BufferedDrawPrimitive(Graphics3D::PT_TriangleFan, aList.size()-2, &aList[0], mDefaultVertexSize, mDefaultVertexFVF);
		}
	}
	
	void DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode, bool antiAlias = false)
	{
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		
		float x1, y1, x2, y2;
		uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);			
		
		if (!mTransformStack.empty())
		{
			SexyVector2 p1((float)theStartX, (float)theStartY);
			SexyVector2 p2((float)theEndX, (float)theEndY);
			p1 = mTransformStack.back()*p1;
			p2 = mTransformStack.back()*p2;
			
			x1 = p1.x;
			y1 = p1.y;
			x2 = p2.x;
			y2 = p2.y;
		}
		else
		{
			x1 = (float)theStartX;
			y1 = (float)theStartY;
			x2 = (float)theEndX;
			y2 = (float)theEndY;
		}
		
		float z = static_cast<PlatformImplT*>(this)->GetBltDepth();
		
		VertexT aVertex[3] = 
		{
			VertexT( x1,				y1,				z,	0,0, aColor),
			VertexT( x2,				y2,				z,	0,0, aColor)
		};
		static_cast<PlatformImplT*>(this)->SetTextureSingle(0, 0);
		BufferedDrawPrimitive(Graphics3D::PT_LineStrip, 1, aVertex, mDefaultVertexSize, mDefaultVertexFVF);
	}
	
	void Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode)
	{
		BltNoClipF(theImage, (float)theX, (float)theY, theSrcRect, theColor, theDrawMode);
	}
	
// QZY added. provide a method to stretch the front buffer to fit in device's resolution.
#if 1
	void BltStretch(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode)
	{
		if (!mTransformStack.empty())
		{
			BltClipF(theImage,theX,theY,theSrcRect,NULL,theColor,theDrawMode);
			return;
		}

		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;


		Image* theOrigImage = theImage;
		theImage = SetupAtlasState(0, theImage);

		MemoryImage* aSrcMemoryImage = (MemoryImage*) theImage;

		if (!CreateImageRenderData(aSrcMemoryImage))
			return;

		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);

		TextureData *aData = (TextureData*)aSrcMemoryImage->GetRenderData();

		//SetTextureLinearFilter(0, linearFilter); // CDH hardware now ignores filter argument (caused excessive batching problems; it now stays on by default); callers can use SetTextureLinearFilter directly if necessary
		aData->BltStrech(this,(MemoryImage*)theOrigImage,theDrawMode,theX,theY,theSrcRect,theColor);
	}
#endif
// QZY end.

	void BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode)
	{
		FRect aClipRect((MATH_TYPE)theClipRect.mX,(MATH_TYPE)theClipRect.mY,(MATH_TYPE)theClipRect.mWidth,(MATH_TYPE)theClipRect.mHeight);
		FRect aDestRect(theX,theY,(MATH_TYPE)theSrcRect.mWidth,(MATH_TYPE)theSrcRect.mHeight);
		
		FRect anIntersect = aDestRect.Intersection(aClipRect);
		if (anIntersect.mWidth!=aDestRect.mWidth || anIntersect.mHeight!=aDestRect.mHeight)
		{
			if (anIntersect.mWidth!=0 && anIntersect.mHeight!=0)
				BltClipF(theImage,theX,theY,theSrcRect,&theClipRect,theColor,theDrawMode);
		}
		else
			BltNoClipF(theImage,theX,theY,theSrcRect,theColor,theDrawMode,true);
	}
	
	void BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY)
	{
		SexyTransform2D aTransform;
		
		aTransform.Translate(-theRotCenterX, -theRotCenterY);
		aTransform.RotateRad((float)theRot);
		aTransform.Translate(theX+theRotCenterX,theY+theRotCenterY);
		
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,true);
	}
	
    void BltMatrix2(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend,bool center)
    {
        BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,theMatrix,blend,x,y,center);
    }
    
	// Word of warning, this function will CENTER the image at the specified location
	void BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend)
	{
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,theMatrix,blend,x,y,true);
	}
#if OPTIMIZE_ANIM_DRAW
	void BltMatrixOptimized(Image* theImage, MATH_TYPE x, MATH_TYPE y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool blend, bool bNeedUpdateImage)
	{
		BltTransformedOptimized(theImage,&theClipRect,theColor,theDrawMode,theMatrix,blend,x,y,bNeedUpdateImage);
	}
	void BltTransformedOptimized(Image* theImage, const Rect* theClipRect, const Color& theColor, int theDrawMode, const SexyMatrix3 &theTransform, bool linearFilter, MATH_TYPE theX, MATH_TYPE theY, bool bNeedUpdateImage)
	{
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;

		Image* theOrigImage = theImage;
		MemoryImage* aSrcMemoryImage;
		Image::CachedImageAtlasUVInfo & info = theImage->GetCachedAtlasUVInfo();
		Image* atlasImage;
		if(info.IsDirty())
		{
			atlasImage = theImage->mAtlasImage;
		}
		else
		{
			atlasImage = info.GetResult().pAtlasImage;
		}
		if(atlasImage)
		{
			theImage = atlasImage;
		}

		aSrcMemoryImage = (MemoryImage*) theImage;		
		if(bNeedUpdateImage)
		{
			if (!CreateImageRenderData(aSrcMemoryImage))
				return;

			static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		}

		TextureData *aData = (TextureData*)aSrcMemoryImage->GetRenderData();

		assert(mTransformStack.empty()); //The original branch to handle this is removed. We don't need this for PopAnim.
		aData->BltTransformedOptimized(this, (MemoryImage*)theOrigImage, theDrawMode, theTransform, theColor, theClipRect, theX, theY, bNeedUpdateImage);

	}
#endif //OPTIMIZE_ANIM_DRAW
	void BltTriangles(Image* theImage, const SexyVertex2D theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx, float ty, bool blend = true, const Rect* theClipRect = NULL)
	{
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		Image* theOrigImage = theImage;
		theImage = SetupAtlasState(0, theImage);
		MemoryImage* aSrcMemoryImage = (MemoryImage*)theImage;
		
		if (!CreateImageRenderData(aSrcMemoryImage))
			return;
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		uint32 aColor = VertexT::PackColor(theColor.mRed, theColor.mGreen, theColor.mBlue, theColor.mAlpha);			
		
		TextureData *aData = (TextureData*)aSrcMemoryImage->GetRenderData();
		
		//SetTextureLinearFilter(0, blend); // CDH hardware now ignores filter argument (caused excessive batching problems; it now stays on by default); callers can use SetTextureLinearFilter directly if necessary
				
		aData->BltTriangles(this, (MemoryImage*)theOrigImage, theVertices, theNumTriangles, aColor, tx, ty, theClipRect);
		
	}
	
	void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode)
	{
		SexyTransform2D aTransform;		
		
		aTransform.Translate(-(float)theSrcRect.mWidth,0);
		aTransform.Scale(-1, 1);
		aTransform.Translate((float)theX, (float)theY);
		
		BltTransformed(theImage,NULL,theColor,theDrawMode,theSrcRect,aTransform,false);
	}
	
	void BltStretched(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror = false)
	{
		float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
		float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;
		
		SexyTransform2D aTransform;
		if (mirror)
		{
			aTransform.Translate(-(float)theSrcRect.mWidth,0);
			aTransform.Scale(-xScale, yScale);
		}
		else
			aTransform.Scale(xScale, yScale);
		
		aTransform.Translate((float)theDestRect.mX, (float)theDestRect.mY);
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,!fastStretch);
	}
	
	virtual void BltStretchedAndRotated(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, bool fastStretch, bool mirror = false)
	{
		SexyTransform2D aTransform;

		// Apply scale
		float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
		float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;

		if (mirror)
		{
			aTransform.Translate(-(float)theSrcRect.mWidth,0);
			aTransform.Scale(-xScale, yScale);
		}
		else
			aTransform.Scale(xScale, yScale);

		// Apply rotation (order probably matters)
		aTransform.Translate(-theRotCenterX, -theRotCenterY);
		aTransform.RotateRad((float)theRot);
		aTransform.Translate(theRotCenterX, theRotCenterY);

		aTransform.Translate((float)theDestRect.mX, (float)theDestRect.mY);

		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,!fastStretch);
	}

#ifdef PRIME_FOR_BEJBLITZ
	// @BLITZ(MEB) : this is a terrible name but we needed to be able to flip on x and y.
	void BltStretchedSpecial(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirrorX, bool mirrorY)
	{
		float xScale = (float)theDestRect.mWidth / theSrcRect.mWidth;
		float yScale = (float)theDestRect.mHeight / theSrcRect.mHeight;
		
		SexyTransform2D aTransform;
		if (mirrorX)
		{
			aTransform.Translate(-(float)theSrcRect.mWidth,0);
			aTransform.Scale(-xScale, yScale);
		}
		if (mirrorY)
		{
			aTransform.Translate(0,-(float)theSrcRect.mHeight);
			aTransform.Scale(xScale, -yScale);
		}
		
		if (!mirrorX && !mirrorY)
			aTransform.Scale(xScale, yScale);
		
		aTransform.Translate((float)theDestRect.mX, (float)theDestRect.mY);
		BltTransformed(theImage,&theClipRect,theColor,theDrawMode,theSrcRect,aTransform,!fastStretch);
	}
#endif

	
	/**
	 * The following methods must be implemented by the concrete driver
	 * documentation forthcoming..
	 */
	//virtual float	GetBltDepth() = 0;
	//virtual void	SetupDrawMode(int theDrawMode) = 0;
	//virtual bool	PreDraw() = 0;
	//virtual void	SetTextureDirect(int stage, TextureT tex) = 0;
	virtual void	SetTextureLinearFilter(int theStage, bool hasLinearFilter) = 0;
	virtual void	DrawPrimitiveInternal(uint32 inPrimType, uint32 inPrimCount, const void* inVertData, uint32 inVertStride, uint32 inVertFormat, bool inDoCommit=true) = 0;
	virtual void	CheckBatchAndCommit() = 0;
	virtual TextureT CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, TextureData* theTexData, TextureDataPiece* theTexPiece) = 0;
	virtual void	CopyImageToTexture(TextureT theTexture, int theTextureFormat, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat) = 0;
	virtual void	ReleaseTexture(TextureData*, TextureT& theTexture) = 0;
	virtual void	ReleaseExtraRenderDataInfo(TextureData*, ExtraRenderDataInfoT& theInfo) = 0;

	virtual Image*	SetupAtlasState(int inTextureIndex, Image* inImage) = 0;
	//virtual void	AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, uint32 inVertFormat, int inStride, int inTexUVOfs) = 0;

	virtual bool CreateImageRenderData(MemoryImage* inImage)
	{
		bool wantPurge = false;
		
		if(inImage->GetRenderData()==NULL)
		{
			inImage->SetRenderData(new TextureData(this));
			
			// The actual purging was deferred
			wantPurge = inImage->mPurgeBits;
			
			AutoCrit aCrit(mGraphicsDriver->GetCritSect()); // Make images thread safe
			mImageSet.insert(inImage);
		}
		
		TextureData *aData = (TextureData*)inImage->GetRenderData();
		aData->CheckCreateTextures(inImage, this);
		
		if ((wantPurge) || inImage->HasImageFlag(ImageFlag_RenderTarget))
			inImage->PurgeBits();
		
		return aData->mPixelFormat != PixelFormat_Unknown;
	}
	
	void RemoveImageRenderData(MemoryImage* inImage)
	{
		if (inImage->GetRenderData() != NULL)
		{
			FlushBufferedTriangles(); // incase we're currently using this texture
			
			delete (TextureData*)inImage->GetRenderData();
			inImage->SetRenderData(NULL);
			
			AutoCrit aCrit(mGraphicsDriver->GetCritSect()); // Make images thread safe
			mImageSet.erase(inImage);
		}
	}
	
	void BltClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect *theClipRect, const Color& theColor, int theDrawMode)
	{
		SexyTransform2D aTransform;
		aTransform.Translate(theX, theY);
		
		BltTransformed(theImage,theClipRect,theColor,theDrawMode,theSrcRect,aTransform,true);
	}
	
	void BltNoClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter = false)
	{
		if (!mTransformStack.empty())
		{
			BltClipF(theImage,theX,theY,theSrcRect,NULL,theColor,theDrawMode);
			return;
		}
		
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		
		Image* theOrigImage = theImage;
		theImage = SetupAtlasState(0, theImage);
		
		MemoryImage* aSrcMemoryImage = (MemoryImage*) theImage;
		
		if (!CreateImageRenderData(aSrcMemoryImage))
			return;
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		
		TextureData *aData = (TextureData*)aSrcMemoryImage->GetRenderData();
		
		//SetTextureLinearFilter(0, linearFilter); // CDH hardware now ignores filter argument (caused excessive batching problems; it now stays on by default); callers can use SetTextureLinearFilter directly if necessary
		aData->Blt(this,(MemoryImage*)theOrigImage,theDrawMode,theX,theY,theSrcRect,theColor);
	}
	
	void BltTransformed(Image* theImage, const Rect* theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, const SexyMatrix3 &theTransform, bool linearFilter, float theX = 0, float theY = 0, bool center = false)
	{
		if (!static_cast<PlatformImplT*>(this)->PreDraw())
			return;
		
		Image* theOrigImage = theImage;
		theImage = SetupAtlasState(0, theImage);
		
		MemoryImage* aSrcMemoryImage = (MemoryImage*) theImage;
		
		if (!CreateImageRenderData(aSrcMemoryImage))
			return;
		
		
		//jvw - experimental opt for iphones/low fill rate machines.
		// would be nice to split this out for large images only
		// note: that statemanager must turn off blending for this to
		// actually help
		bool drawingWithoutAlpha=false; 
		if (theDrawMode==Graphics::DRAWMODE_NORMAL 
			&& !aSrcMemoryImage->mHasAlpha 
			&& theColor.mAlpha>=255 
			&& (theOrigImage->mWidth*theOrigImage->mHeight > 40000))
		{
			SetBlend(Graphics3D::BLEND_ONE, Graphics3D::BLEND_ZERO);
			drawingWithoutAlpha = true;
		}
		
		static_cast<PlatformImplT*>(this)->SetupDrawMode(theDrawMode);
		
		TextureData *aData = (TextureData*)aSrcMemoryImage->GetRenderData();
		
		if (!mTransformStack.empty())
		{
            // CDH hardware now ignores filter argument (caused excessive batching problems; it now stays on by default); callers can use SetTextureLinearFilter directly if necessary
			//SetTextureLinearFilter(0, true); // force linear filtering in the case of a global transform
            
			if (theX!=0 || theY!=0)
			{
				SexyTransform2D aTransform;
				if (center)
					aTransform.Translate(-theSrcRect.mWidth/2.0f,-theSrcRect.mHeight/2.0f);
				
				aTransform = theTransform * aTransform;
				aTransform.Translate(theX,theY);
				aTransform = mTransformStack.back() * aTransform;
				
				aData->BltTransformed(this, (MemoryImage*)theOrigImage, theDrawMode, aTransform, theSrcRect, theColor, theClipRect);
			}
			else
			{
				SexyTransform2D aTransform = mTransformStack.back()*theTransform;
				aData->BltTransformed(this, (MemoryImage*)theOrigImage, theDrawMode, aTransform, theSrcRect, theColor, theClipRect, theX, theY, center);
			}
		}
		else
		{
			//SetTextureLinearFilter(0, linearFilter); // CDH hardware now ignores filter argument (caused excessive batching problems; it now stays on by default); callers can use SetTextureLinearFilter directly if necessary
			aData->BltTransformed(this, (MemoryImage*)theOrigImage, theDrawMode, theTransform, theSrcRect, theColor, theClipRect, theX, theY, center);
		}
		
		if (drawingWithoutAlpha)
		{
			SetBlend(Graphics3D::BLEND_DEFAULT, Graphics3D::BLEND_DEFAULT);
		}
	}
	
	void BufferedDrawPrimitive(int thePrimType, uint32 thePrimCount, const VertexT* theVertices, int theVertexSize, uint32 theVertexFormat)
	{		
		/*
		 JVW - TODO,  what are drawprim filters used for?
		 if (mDrawPrimFilter != NULL)
		 {
		 if (!mDrawPrimFilter(mDrawPrimFilterContext, thePrimType, thePrimCount, (SexyVertex2D*) theVertices, theVertexSize))
		 return;
		 }*/
		
#ifndef RELEASEFINAL
		if (mRenderModeFlags & IGraphicsDriver::RENDERMODEF_NoBatching)
		{
			//IFNOTRELEASEFINAL(AdjustPrimCount(&thePrimCount));
			//IFNOTRELEASEFINAL(MetricsAddPrimitive(thePrimType, thePrimCount));

			DrawPrimitiveInternal(thePrimType, thePrimCount, theVertices, (uint32)theVertexSize, theVertexFormat);

			return;
		}
#endif
		
		if ((uint32)theVertexSize != mDefaultVertexSize || theVertexFormat != mDefaultVertexFVF || 
			(thePrimType != Graphics3D::PT_TriangleStrip && thePrimType != Graphics3D::PT_TriangleList && thePrimType != Graphics3D::PT_TriangleFan) ||
			(thePrimType != Graphics3D::PT_TriangleList && thePrimCount*3 > mBatchedTriangleSize))
		{
			FlushBufferedTriangles();
			
			//IFNOTRELEASEFINAL(AdjustPrimCount(&thePrimCount));
			//IFNOTRELEASEFINAL(MetricsAddPrimitive(thePrimType, thePrimCount));

			DrawPrimitiveInternal(thePrimType, thePrimCount, theVertices, (uint32)theVertexSize, theVertexFormat);

			//mDrawPrimMtx.mPrims += thePrimCount;
			//mDrawPrimMtx.mCalls++;
		}
		else
		{
			DBG_ASSERTE(mBatchedTriangleSize >= 3);

			CheckBatchAndCommit();
			
			switch (thePrimType)
			{
				case Graphics3D::PT_TriangleList:
					while (thePrimCount)
					{
						if (mBatchedTriangleIndex > mBatchedTriangleSize-3)
							FlushBufferedTriangles();
                        
                        PRIME_ASSERT(mBatchedTriangleSize-mBatchedTriangleIndex >= 3);
						mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
						mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
						mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
						thePrimCount--;
					}
					break;
					
				case Graphics3D::PT_TriangleStrip:
					if (thePrimCount*3 > mBatchedTriangleSize - mBatchedTriangleIndex)
						FlushBufferedTriangles();
					
                    DBG_ASSERT(thePrimCount*3 <= mBatchedTriangleSize);
                    
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					thePrimCount--;
					while (thePrimCount)
					{
                        PRIME_ASSERT(mBatchedTriangleSize-mBatchedTriangleIndex >= 3);
						mBatchedTriangleBuffer[mBatchedTriangleIndex  ] = mBatchedTriangleBuffer[mBatchedTriangleIndex-2];
						mBatchedTriangleBuffer[mBatchedTriangleIndex+1] = mBatchedTriangleBuffer[mBatchedTriangleIndex-1];
						mBatchedTriangleBuffer[mBatchedTriangleIndex+2] = *theVertices++;
						mBatchedTriangleIndex += 3;
						thePrimCount--;
					}
					break;
					
				case Graphics3D::PT_TriangleFan:
				{
                    //This converts a triangle fan into a triangle list so it can be used by the batched triangle buffer
					if (thePrimCount*3 > mBatchedTriangleSize - mBatchedTriangleIndex)
						FlushBufferedTriangles();
					
					PRIME_ASSERT(mBatchedTriangleSize-mBatchedTriangleIndex >= 3);
					
					VertexT initialVertex = *theVertices;
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					VertexT previousVertex = *theVertices;
					mBatchedTriangleBuffer[mBatchedTriangleIndex++] = *theVertices++;
					thePrimCount--;
					while (thePrimCount)
					{
						if (3 > (mBatchedTriangleSize - mBatchedTriangleIndex))
						{
							FlushBufferedTriangles();
						}
						
						PRIME_ASSERT(mBatchedTriangleSize-mBatchedTriangleIndex >= 3);
						
						mBatchedTriangleBuffer[mBatchedTriangleIndex  ] = initialVertex;
						mBatchedTriangleBuffer[mBatchedTriangleIndex+1] = previousVertex;
						previousVertex = *theVertices;
						mBatchedTriangleBuffer[mBatchedTriangleIndex+2] = *theVertices++;
						mBatchedTriangleIndex += 3;
						thePrimCount--;
					}
					break;
				}
					
				default:
					DBG_ASSERTE(!"Invalid logic encountered in Triangle Buffering code BufferedDrawPrimitive");
					break;
			}
			
			// Flush now if we're full
			if (mBatchedTriangleIndex+3 > mBatchedTriangleSize)
				FlushBufferedTriangles();
		}
	}
	
	virtual void FlushBufferedTriangles()
	{
		if (mSceneBegun && mBatchedTriangleIndex > 0)
		{
			auto primCount = mBatchedTriangleIndex/3;
			
			//IFNOTRELEASEFINAL(AdjustPrimCount((ulong*)&primCount));
			//ADDMETRIC(CT_TriListCalls, 1);
			//ADDMETRIC(CT_TriListPrims, primCount);
			
			DrawPrimitiveInternal(Graphics3D::PT_TriangleList, primCount, mBatchedTriangleBuffer, mDefaultVertexSize, mDefaultVertexFVF, false);
			
			//mDrawPrimMtx.mPrims += primCount;
			//mDrawPrimMtx.mCalls++;
			mBatchedTriangleIndex = 0;
		}
	}
	
	
	void DrawPolyClipped(const Rect *theClipRect, const VertexTList &theList)
	{
		VertexTList l1, l2;
		l1 = theList;
		
		int left = theClipRect->mX;
		int right = left + theClipRect->mWidth;
		int top = theClipRect->mY;
		int bottom = top + theClipRect->mHeight;
		
		VertexTList *in = &l1, *out = &l2;
		PointClipper<std::less<float> > aLessClipper;
		PointClipper<std::greater_equal<float> > aGreaterClipper;
		
		aLessClipper.ClipPoints(0,(float)left,*in,*out); std::swap(in,out); out->clear();
		aLessClipper.ClipPoints(1,(float)top,*in,*out); std::swap(in,out); out->clear();
		aGreaterClipper.ClipPoints(0,(float)right,*in,*out); std::swap(in,out); out->clear();
		aGreaterClipper.ClipPoints(1,(float)bottom,*in,*out); 
		
		VertexTList &aList = *out;
		
		if (aList.size() >= 3)
		{
			BufferedDrawPrimitive(Graphics3D::PT_TriangleFan, aList.size()-2, &aList[0], mDefaultVertexSize, mDefaultVertexFVF);
		}
	}
	
	void CopyImageToTexture8888(void *theDest, uint32 theDestPitch, MemoryImage *theImage, int offx, int offy, int theWidth, int theHeight, bool rightPad)
	{
		if (theImage->mColorTable == NULL)
		{
			uint32 *srcRow = theImage->GetBits() + offy * theImage->GetWidth() + offx;
			char *dstRow = (char*)theDest;
			
			int thePadAmt = theDestPitch/4 - theWidth;
			
			for(int y=0; y<theHeight; y++)
			{
				uint32 *src = srcRow;
				uint32 *dst = (uint32*)dstRow;
				for(int x=0; x<theWidth; x++)
				{
					*dst++ = *src++;
				}
				
				if (rightPad) 
				{
					for (int x=0; x<thePadAmt; x++)
					{
						*dst = *(dst-1);
						dst++;
					}
				}
				
				srcRow += theImage->GetWidth();
				dstRow += theDestPitch;
			}
		}
		else // palette
		{
			uchar *srcRow = (uchar*)theImage->mColorIndices + offy * theImage->GetWidth() + offx;
			uchar *dstRow = (uchar*)theDest;
			uint32 *palette = theImage->mColorTable;
			
			for(int y=0; y<theHeight; y++)
			{
				uchar *src = srcRow;
				uint32 *dst = (uint32*)dstRow;
				for(int x=0; x<theWidth; x++)
					*dst++ = palette[*src++];
				
				if (rightPad) 
					*dst = *(dst-1);
				
				srcRow += theImage->GetWidth();
				dstRow += theDestPitch;
			}
		}
		
		
		//support dithering and 16bit out?
		/*if ((theImage->mDither16) && (theDriver->mDisplayFormat == SEXY3DFMT_R5G6B5))
		 {		
		 if (!gQuantMaxTableInitialized)
		 {
		 for (int i = 0; i < 256+8; i++)
		 gQuantMaxTable[i] = min(255, i);
		 gQuantMaxTableInitialized = true;
		 }
		 
		 int aTableSize = theImage->mWidth+1;
		 ulong aStaticTable[8192];
		 
		 ulong* anErrorTable;
		 if (aTableSize > 8192)
		 anErrorTable = new ulong[aTableSize];
		 else
		 anErrorTable = aStaticTable;
		 memset(anErrorTable, 0, aTableSize*4);
		 
		 int aTablePos = 0;
		 int anOffsets[4] = {1, theImage->mWidth-1, theImage->mWidth, theImage->mWidth+1};
		 int aFactors[4] = {7, 3, 5, 1};
		 
		 uchar *ptrRow = (uchar*)theDest;
		 for(int y=0; y<theHeight; y++)
		 {
		 ulong *ptr = (ulong*) ptrRow;	
		 for(int x=0; x<theWidth; x++)
		 {
		 ulong aColor = *ptr;
		 
		 uchar* aColorComp = (uchar*) &aColor;
		 uchar* anErrorComp = (uchar*) &anErrorTable[aTablePos];
		 
		 for (int i = 0; i < 3; i++)
		 aColorComp[i] = gQuantMaxTable[aColorComp[i] + anErrorComp[i]/16];				
		 
		 ulong aNewColor = aColor & 0xFFF8FCF8;
		 ulong anError = aColor - aNewColor;
		 
		 for (int i = 0; i < 4; i++)			
		 anErrorTable[(aTablePos + anOffsets[i]) % aTableSize] += anError * aFactors[i];			
		 
		 anErrorTable[aTablePos] = 0;
		 aTablePos = (aTablePos+1) % aTableSize;
		 
		 *ptr++ = aNewColor;
		 }
		 
		 if (rightPad) 
		 *ptr = *(ptr-1);
		 
		 ptrRow += theDestPitch;
		 }
		 
		 if (anErrorTable != aStaticTable)
		 delete [] anErrorTable;
		 }*/
		
	}
	
	void CopyImageToLockedRect(void* theLockedBits, int theLockedPitch, MemoryImage *theImage, int offx, int offy, int texWidth, int texHeight, PixelFormat theFormat)
	{
		int aWidth = min(texWidth,(theImage->GetWidth()-offx));
		int aHeight = min(texHeight,(theImage->GetHeight()-offy));
		
		bool rightPad = aWidth<texWidth;
		bool bottomPad = aHeight<texHeight;
		//	if(aWidth < texWidth || aHeight < texHeight)
		//		memset(aDesc.lpSurface, 0, aDesc.lPitch*aDesc.dwHeight);
		
		if(aWidth>0 && aHeight>0)
		{
			switch (theFormat)
			{
				default:
					DBG_ASSERT("FORMAT NOT SUPPORTED"==0);
					assert(false);
					return;
				case PixelFormat_X8R8G8B8:
				case PixelFormat_A8R8G8B8:	CopyImageToTexture8888(theLockedBits, theLockedPitch, theImage, offx, offy, aWidth, aHeight, rightPad); break;
					//case PixelFormat_A4R4G4B4:	CopyImageToTexture4444(theLockedBits, theLockedPitch, theImage, offx, offy, aWidth, aHeight, rightPad); break;
					//case PixelFormat_R5G6B5:	CopyImageToTexture565(theLockedBits, theLockedPitch, theImage, offx, offy, aWidth, aHeight, rightPad); break;
					//case PixelFormat_Palette8:	CopyImageToTexturePalette8(theLockedBits, theLockedPitch, theImage, offx, offy, aWidth, aHeight, rightPad); break;
			}
			
			if (bottomPad)
			{
				uint8 *dstrow = ((uint8*)theLockedBits) + theLockedPitch*aHeight;
				uint8 *finalrow = dstrow - theLockedPitch;
				int thePadAmt = texHeight - aHeight;
				for (int i=0; i<thePadAmt; i++)
				{
					memcpy(dstrow, finalrow, theLockedPitch);
					dstrow += theLockedPitch;
				}
			}
		}
	}
	
	
	///////////////////////////////////////////////
	//RENDERDEVICE3D IMPLEMENTATION
	//Most of this has to be overridden. It's implemented for convenience when 
	// writing new drivers
	///////////////////////////////////////////////
	
	
	
	// Present the back buffer to the window
	virtual bool Present(const Rect* theSrcRect, const Rect* theDestRect)
	{
		DBG_ASSERT("NOT IMPLEMENTED"==0);
		return false;
	}
	
	virtual uint32 GetCapsFlags()
	{
		return 0;
	}

	virtual int GetMaxTextureStages()
	{
		return 1;
	}

	virtual void GetBackBufferDimensions(uint32& outWidth, uint32& outHeight)
	{
		outWidth = mWidth;
		outHeight = mHeight;
	}

	virtual bool SceneBegun()
	{
		return mSceneBegun;
	}
	

	
	//These have to be impl'd by a more concrete RenderDevice
	//check RenderDevice3D for more docs
	/*virtual bool RecoverImageBitsFromRenderData(MemoryImage* inImage) = 0;
	virtual int	GetTextureMemorySize(MemoryImage* theImage) = 0;
	virtual PixelFormat GetTextureFormat(MemoryImage* theImage) = 0;
	virtual void ClearColorBuffer(const Color& inColor = Color::Black) = 0;
	virtual void ClearDepthBuffer() = 0;
	virtual void SetBltDepth(float inDepth) = 0;
	virtual void ClearColorBuffer(const Color& inColor = Color::Black) = 0;
	virtual void ClearDepthBuffer() = 0;
	*/
	
	
	// Push/pop a transform to use with 2D Blt-related functions
	virtual void PushTransform(const SexyMatrix3 &theTransform, bool concatenate = true)
	{
		if (mTransformStack.empty() || !concatenate)
			mTransformStack.push_back(theTransform);
		else 
		{
			SexyMatrix3 &aTrans = mTransformStack.back();
			mTransformStack.push_back(aTrans*theTransform);
		}

	}
	
	virtual void PopTransform()
	{
		if (!mTransformStack.empty())
			mTransformStack.pop_back();
	}
	
	virtual void PopTransform(SexyMatrix3 &theTransform)
	{
		if (!mTransformStack.empty())
			theTransform = mTransformStack.back();
		else 
		{
			SexyMatrix3 aMatrix = SexyMatrix3();
			aMatrix.LoadIdentity();
			theTransform = aMatrix;
			
		}

		PopTransform();
	}
	
	
	virtual bool LoadMesh(Mesh* theMesh)
	{
		return false;
	}
	
	virtual void RenderMesh(Mesh* theMesh, const SexyMatrix4& theMatrix, const Color& theColor = Color::White, bool doSetup = true)
	{
		
	}
	
};
}

#endif
