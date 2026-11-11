#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Common.h"
#include "Color.h"
#include "Rect.h"
#include "Point.h"
#include "ResourceTypes.h"

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
enum ImageFlags 
{
	ImageFlag_MinimizeNumSubdivisions	=			0x0001,		// subdivide image into fewest possible textures (may use more memory)
	ImageFlag_Use64By64Subdivisions		=			0x0002,		// good to use with image strips so the entire texture isn't pulled in when drawing just a piece
	ImageFlag_UseA4R4G4B4				=			0x0004,		// images with not too many color gradients work well in this format
	ImageFlag_UseA8R8G8B8				=			0x0008,		// non-alpha images will be stored as R5G6B5 by default so use this option if you want a 32-bit non-alpha image
	ImageFlag_RenderTarget				=			0x0010,		// requests that the image can be rendered to
	ImageFlag_CubeMap					=			0x0020,		// image represents a cubemap, with its six cells being the faces in the order FT,LF,BK,RT,DN,UP
	ImageFlag_VolumeMap					=			0x0040,		// image represents a volumemap, with its cells being in depth order
	ImageFlag_NoTriRep					=			0x0080,		// don't use trirep data for this image (for rare cases where the added geometry could bottleneck)
	ImageFlag_NoQuadRep					=			ImageFlag_NoTriRep, // backward compatibility; trireps supercede old quadreps which served same purpose
	ImageFlag_RTUseDefaultRenderMode	=			0x0100,		// if we're the current render target, ignore the render mode and use the default instead (used only by render targets)
	ImageFlag_Atlas						=			0x0200,		// image is an atlas of other images
	ImageFlag_UngroupedSharedImage		=			0x0400,		// image is not in a group but is shared in the "ungrouped" image map in the resource manager; needs to remove self upon deletion

	REFLECT_ATTR_ENUM_FLAGS
};

class SysFont;
class MemoryImage;
class DeviceImage;
namespace ResourceInfoTypes { class ImageRes; }

class Image
: public BaseResource
{
public:
	RT_CLASS_DEFINE_ABSTRACT(Image, BaseResource, ResourceClass);
	typedef ResourceInfoTypes::ImageRes InfoClass;

protected:
	ImageFlags				mImageFlags;
	void*					mRenderData;

public:
	bool					mDrawn;
	std::string				mFilePath;
	int						mWidth;
	int						mHeight;

	// for image strips
	int						mNumRows; 
	int						mNumCols;

	// for atlased images
	RtWeakPtr<Image>		mAtlasImage;
	int						mAtlasStartX;
	int						mAtlasStartY;
	int						mAtlasEndX;
	int						mAtlasEndY;

#if OPTIMIZE_ANIM_DRAW
	struct CachedAtlasUVResult
	{
		Image * pAtlasImage;
		SexyVector2 aBase,aU,aV;
	};
	struct TestValue
	{
		int w,h,asx,asy,aex,aey;
	};
	class CachedImageAtlasUVInfo
	{
	public:
		CachedImageAtlasUVInfo():mbIsDirty(true)
		{
			mOldValue.w = mOldValue.h = mOldValue.asx = mOldValue.asy = mOldValue.aex = mOldValue.aey = 0;
		}
		bool IsDirty(){return mbIsDirty;}
		void UpdateData(const TestValue & value)
		{
			if(value.w != mOldValue.w
					|| value.h != mOldValue.h
					|| value.asx != mOldValue.asx
					|| value.asy != mOldValue.asy
					|| value.aex != mOldValue.aex
					|| value.aey != mOldValue.aey)
			{
				mOldValue = value;
				mbIsDirty = true;
			}
		}

		void SaveResult(const CachedAtlasUVResult & result)
		{
			mbIsDirty = false;
			mResult = result;
		}

		const CachedAtlasUVResult & GetResult()
		{
			assert(!mbIsDirty);
			return mResult;
		}
	private:
		TestValue mOldValue;
		CachedAtlasUVResult mResult;
		bool mbIsDirty;
	};
	CachedImageAtlasUVInfo*	mpCachedImageAtlasUVInfo;

	CachedImageAtlasUVInfo & GetCachedAtlasUVInfo()
	{
		if(!mpCachedImageAtlasUVInfo)
		{
			mpCachedImageAtlasUVInfo = new CachedImageAtlasUVInfo();
		}
		return *mpCachedImageAtlasUVInfo;
	}
#endif //#if OPTIMIZE_ANIM_DRAW

public:
	Image();
protected:
	Image(const Image& theImage);
public:
	virtual ~Image();

	virtual MemoryImage*	AsMemoryImage() { return NULL; }
	virtual DeviceImage*	AsDeviceImage() { return NULL; }

	int						GetWidth();
	int						GetHeight();
	int						GetCelWidth();		// returns the width of just 1 cel in a strip of images
	int						GetCelHeight();	// like above but for vertical strips
	int						GetCelCount();
	Rect					GetCelRect(int theCel);				// Gets the rectangle for the given cel at the specified row/col 
	Rect					GetCelRect(int theCol, int theRow);	// Same as above, but for an image with both multiple rows and cols
	void					CopyAttributes(Image *from);
	//Graphics*				GetGraphics();

	inline uint32			GetImageFlags() { return mImageFlags; }
	inline void				ReplaceImageFlags(uint32 inFlags) { mImageFlags = (ImageFlags)inFlags; }
	inline void				AddImageFlags(uint32 inFlags) { mImageFlags = (ImageFlags)(mImageFlags | inFlags); }
	inline void				RemoveImageFlags(uint32 inFlags) { mImageFlags = (ImageFlags)(mImageFlags & ~inFlags); }
	inline bool				HasImageFlag(uint32 inFlag) { return (mImageFlags & inFlag) != 0; }

	inline void*			GetRenderData() { return mRenderData; }
	inline void				SetRenderData(void* inRenderData) { mRenderData = inRenderData; }
	
	void					CreateRenderData(); // convenience method for precaching; just calls CreateImageRenderData on render device, if available

public:
	RA_METAMETHOD_TOSTRING(ToString)
	{
		return StrFormat("\"%s\"", mFilePath.c_str());
	}
};

typedef RtWeakPtr<Image> ImagePtr;
typedef RtMixedPtr<Image> MixedImagePtr;

}

#endif //__IMAGE_H__
