
#ifndef __DDIMAGE_H__
#define __DDIMAGE_H__

#include "MemoryImage.h"
#include "DeviceSurface.h"

namespace Sexy
{

class SysFont;
class SexyAppBase;
class IGraphicsDriver;

class DeviceImage : public MemoryImage
{
public:
	RT_CLASS_DEFINE(DeviceImage, MemoryImage, ResourceClass) {}

protected:
	friend class			SysFont;
	void					DeleteAllNonSurfaceData();

public:
	IGraphicsDriver*		mDriver;
	bool					mSurfaceSet;
	bool					mNoLock;	
	bool					mWantDeviceSurface;	
	bool					mDrawToBits;
	
	
	int						mLockCount;
	DeviceSurfaceDesc		mLockedSurfaceDesc;
	DeviceSurface*			mSurface;

	float					mScalePercent;
#if OPTIMIZE_ANIM_DRAW
	struct CachedResult
	{
		float u1,v1,u2,v2;
		int aWidth,aHeight;
		MATH_TYPE dstX,dstY;
		int texIndex;
	};
	typedef std::vector<CachedResult> CachedResultVector;
	class CachedImageDrawInfo
	{
	public:
		CachedImageDrawInfo():mbIsDirty(false),miOldTexPieceWidth(0),miOldTexPieceHeight(0),miOldImageWidth(0),miOldImageHeight(0),mbOldImageFlagAtlas(false){}
		bool IsDirty(){return mbIsDirty;}
		void UpdateSrcRect(const Rect & rect)
		{
			if(rect != mOldRect)
			{
				mOldRect = rect;
				mbIsDirty = true;
			}
		}
		void UpdateTextureData(int iOldTexPieceWidth, int iOldTexPieceHeight, int iOldImageWidth, int iOldImageHeight, bool bOldImageFlagAtlas)
		{
			if(iOldTexPieceWidth != miOldTexPieceWidth)
			{
				miOldTexPieceWidth = iOldTexPieceWidth;
				mbIsDirty = true;
			}
			if(iOldTexPieceHeight != miOldTexPieceHeight)
			{
				miOldTexPieceHeight = iOldTexPieceHeight;
				mbIsDirty = true;
			}
			if(iOldImageWidth != miOldImageWidth)
			{
				miOldImageWidth = iOldImageWidth;
				mbIsDirty = true;
			}
			if(iOldImageHeight != miOldImageHeight)
			{
				miOldImageHeight = iOldImageHeight;
				mbIsDirty = true;
			}
			if(bOldImageFlagAtlas != mbOldImageFlagAtlas)
			{
				mbOldImageFlagAtlas = bOldImageFlagAtlas;
				mbIsDirty = true;
			}
		}
		/*
		// mTextures should never change, do not check this to reduce test cost.
		void UpdateTextureListData(std::vector<int> & vecWidth, std::vector<int> & vecHeight)
		{
			int size = vecWidth.size();
			if(size!=mvecOldWidth.size())
			{
				mvecOldWidth.clear();
				mvecOldWidth.resize(size);
				mvecOldHeight.clear();
				mvecOldHeight.resize(size);
				mbIsDirty = true;
			}
			for( int i = 0 ; i < size ; i++)
			{
				if(mvecOldWidth[i]!=vecWidth[i])
				{
					mvecOldWidth[i]=vecWidth[i];
					mbIsDirty=true;
				}
				if(mvecOldHeight[i]!=vecHeight[i])
				{
					mvecOldHeight[i]=vecHeight[i];
					mbIsDirty=true;
				}
			}
		}
		*/
		void SaveResult(const CachedResultVector & result)
		{
			mbIsDirty = false;
			auto size = static_cast<int>(result.size());
			mResultVector.clear();
			mResultVector.resize(size);
			for(int i = 0 ; i < size; i++)
			{
				mResultVector[i]= result[i];
			}
		}
		const CachedResultVector & GetResult()
		{
			assert(!mbIsDirty);
			return mResultVector;
		}
		const Rect & GetSrcRect() { return mOldRect; }
	private:
		//std::vector<int> mvecOldWidth,mvecOldHeight;
		CachedResultVector mResultVector;
		Rect mOldRect;
		int miOldTexPieceWidth, miOldTexPieceHeight;
		int miOldImageWidth,miOldImageHeight;
		bool mbOldImageFlagAtlas;
		bool mbIsDirty;
	};
	CachedImageDrawInfo*	mpCachedImageDrawInfo;
#endif //#if OPTIMIZE_ANIM_DRAW
private:
	void					Init();

public:
	DeviceImage*			AsDeviceImage() override  { return this; }

	bool					GenerateDeviceSurface();
	void					DeleteDeviceSurface();	
	
	//these can't be supported in prime...
	//HDC					GetSurfaceDC();
	//void					ReleaseSurfaceDC(HDC theDC);
	
	virtual void			ReInit() override;

	virtual void			BitsChanged() override;
	virtual void			CommitBits() override;

	virtual void			NormalFillRect(const Rect& theRect, const Color& theColor);
	virtual void			AdditiveFillRect(const Rect& theRect, const Color& theColor);
	virtual void			NormalBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
	virtual void			AdditiveBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
	virtual void			NormalDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
	virtual void			AdditiveDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
	virtual void			NormalDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
	virtual void			AdditiveDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);


	virtual void			NormalBltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
	virtual void			AdditiveBltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);

	virtual void			FillScanLinesWithCoverage( RenderDevice::Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const uint8* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight) override;

public:
	DeviceImage();
	DeviceImage(SexyAppBase*);
	DeviceImage(IGraphicsDriver*);
	virtual ~DeviceImage();		

	virtual bool			LockSurface();
	virtual bool			UnlockSurface();

	virtual void			SetSurface(void* theSurface);

	virtual void			Create(int theWidth, int theHeight) override;
	virtual uint32*			GetBits(int i_x = 0, int i_y = 0, int i_width = 0, int i_height = 0) override;
	
	virtual void			FillRect(const Rect& theRect, const Color& theColor, int theDrawMode) override;
	virtual void			DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode, bool antiAlias = false) override;
	virtual void			Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override;
	virtual void			BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode) override;
	virtual void			BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY) override;
	virtual void			BltStretched(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror = false) override;
    virtual void BltMatrix2(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend,bool center) override;
	virtual void			BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend) override;
	virtual void			BltTriangles(Image* theImage, const TriVertex theVertices[][3], int theNumTriangles, const Color &theColor, int theDrawMode, float tx = 0, float ty = 0, bool blend = true, const Rect* theClipRect = NULL) override;

	virtual void			BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode) override;

	virtual bool			Palletize() override;
	virtual void			PurgeBits() override;
	virtual void			DeleteNativeData() override;
	virtual void			DeleteExtraBuffers() override;	

	static bool				CheckCache(const std::string& theSrcFile, const std::string& theAltData);
	static bool				SetCacheUpToDate(const std::string& theSrcFile, const std::string& theAltData);
	static DeviceImage*		ReadFromCache(const std::string& theSrcFile, const std::string& theAltData);
	virtual void			WriteToCache(const std::string& theSrcFile, const std::string& theAltData);	
#if OPTIMIZE_ANIM_DRAW
	CachedImageDrawInfo & GetCachedInfo()
	{
		if(!mpCachedImageDrawInfo)
		{
			mpCachedImageDrawInfo = new CachedImageDrawInfo();
		}
		return *mpCachedImageDrawInfo;
	}
#endif
};

}

#endif //__DDIMAGE_H__
