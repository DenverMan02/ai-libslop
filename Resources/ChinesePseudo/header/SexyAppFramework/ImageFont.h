#ifndef __IMAGEFONT_H__
#define __IMAGEFONT_H__

#include "Font.h"
#include "DescParser.h"
#include "SharedImage.h"
#include "RtDb.h"
#include "Image.h"

#ifndef REMOVE_SEXYFONT

namespace Sexy
{

class SexyAppBase;
class Image;

	//airplay and other arm gcc toolchain compilers don't support pragma pack
#ifndef __GNUC__
#pragma pack(push, 1)
#endif
struct CharDataHashEntry
{
	ushort mChar; // key
	ushort mDataIndex; // index in CharData array  (0xffff for null)
	ulong mNext; // next hash entry index, or 0xffffffff for null

	CharDataHashEntry()
	: mChar(0)
	, mDataIndex(0xffff)
	, mNext(0xffffffff)
	{}
};
#ifndef __GNUC__
#pragma pack(pop)
#endif

class CharData
{
public:
	Rect					mImageRect;
	Point					mOffset;
	ushort					mKerningFirst;
	ushort					mKerningCount;
	int						mWidth;
	int						mOrder;
	
	int						mHashEntryIndex;

public:
	CharData();
};

class CharDataHashTable
{
public:
	enum
	{
		HASH_BITS = 10,
		HASH_BUCKET_COUNT = (1 << HASH_BITS),
		HASH_BUCKET_MASK = (HASH_BUCKET_COUNT - 1)
	};
	
	bool mOrderedHash;
	std::vector<CharData> mCharData; // actual char data, just keep adding to it
	std::vector<CharDataHashEntry> mHashEntries; // hash data; initial size is HASH_BUCKET_COUNT, grows from there based on collisions

protected:
	int GetBucketIndex(SexyChar inChar);

public:
	CharDataHashTable()
	{
		mOrderedHash = false;
		mHashEntries.resize(HASH_BUCKET_COUNT);
	}

	CharData* GetCharData(SexyChar inChar, bool inAllowAdd = true);
};

class FontData;

class FontLayer
{
public:
	typedef std::vector<std::string> StringVector;
	typedef std::map<SexyString, SexyString> ExInfoMap;
#ifndef __GNUC__
#pragma pack(push, 1)
#endif
	union KerningValue
	{
		int mInt;
		struct
		{
			ushort mChar;
			short mOffset;
		};
	};
#ifndef __GNUC__
#pragma pack(pop)
#endif

public:	
	FontData*				mFontData;
	ExInfoMap				mExtendedInfo;
	std::string				mLayerName;
	StringVector			mRequiredTags;
	StringVector			mExcludedTags;	
	std::vector<int>		mKerningData;
	CharDataHashTable		mCharDataHashTable;
	Color					mColorMult;
	Color					mColorAdd;
	MixedImagePtr			mImage;
	bool					mImageIsWhite;
	std::string				mImageFileName;
	int						mDrawMode;
	Point					mOffset;
	int						mSpacing;
	int						mMinPointSize;
	int						mMaxPointSize;
	int						mPointSize;
	int						mAscent;
	int						mAscentPadding; // How much space is above the avg uppercase char
	int						mHeight;		// 	
	int						mDefaultHeight; // Max height of font character image rects	
	int						mLineSpacingOffset; // This plus height should get added between lines
	int						mBaseOrder;
	bool					mUseAlphaCorrection;

public:
	FontLayer();
	FontLayer(FontData* theFontData);
	FontLayer(const FontLayer& theFontLayer);

	CharData*				GetCharData(SexyChar theChar);
};

typedef std::list<FontLayer> FontLayerList;
typedef std::map<std::string, FontLayer*> FontLayerMap;
typedef std::list<Rect> RectList;
typedef std::vector<int> IntVector;

typedef std::map<SexyChar, SexyChar> SexyCharToSexyCharMap;

class FontData : public DescParser
{
public:
	bool					mInitialized;
	int						mRefCount;
	SexyAppBase*			mApp;		

	int						mDefaultPointSize;
	SexyCharToSexyCharMap	mCharMap;	

	FontLayerList			mFontLayerList;
	FontLayerMap			mFontLayerMap;

	std::string				mSourceFile;
	SexyString				mFontErrorHeader;	
	std::string				mImagePathPrefix;

public:
	virtual bool			Error(const SexyString& theError);

	bool					GetColorFromDataElement(DataElement *theElement, Color &theColor);
	bool					DataToLayer(DataElement* theSource, FontLayer** theFontLayer);
	virtual bool			HandleCommand(const ListDataElement& theParams);

public:
	FontData();
	virtual ~FontData();

	void					Ref();
	void					DeRef();

	bool					Load(SexyAppBase* theSexyApp, const std::string& theFontDescFileName);
	//bool					LoadLegacy(Image* theFontImage, const std::string& theFontDescFileName);
};

typedef std::map<SexyChar, Rect> SexyCharToRectMap;

class ActiveFontLayer
{
public:
	FontLayer*				mBaseFontLayer;
	
	MixedImagePtr			mScaledImages[8]; // 7 is normal white, others are filled in as needed for alpha correction	
	bool					mUseAlphaCorrection;	
	bool					mOwnsImage;
	SexyCharToRectMap		mScaledCharImageRects;
	std::vector<Color>		mColorStack;
public:
	ActiveFontLayer();
	ActiveFontLayer(const ActiveFontLayer& theActiveFontLayer);
	virtual ~ActiveFontLayer();
	ImagePtr				GenerateAlphaCorrectedImage(int thePalette);
	
	void					PushColor(const Color& theColor);
	void					PopColor();
};

typedef std::list<ActiveFontLayer> ActiveFontLayerList;

class RenderCommand
{
public:
	ActiveFontLayer*		mFontLayer;	
	int						mDest[2];
	int						mSrc[4];
	int						mMode;
	Color					mColor;
	RenderCommand*			mNext;
};

typedef std::multimap<int, RenderCommand> RenderCommandMap;

class ImageFont : public Font
{
public:
	RT_CLASS_DEFINE(ImageFont, Font, ResourceClass) {}

public:
	typedef std::vector<std::string> StringVector;	

public:	
	static bool				mAlphaCorrectionEnabled;
	static bool				mOrderedHash;
	FontData*				mFontData;
	int						mPointSize;
	StringVector			mTagVector;
	bool					mActivateAllLayers;

	bool					mActiveListValid;
	ActiveFontLayerList		mActiveLayerList;
	double					mScale;
	bool					mForceScaledImagesWhite;
	bool					mWantAlphaCorrection;
	MixedImagePtr			mFontImage;

public:
	virtual void			GenerateActiveFontLayers();
	virtual void			DrawStringEx(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect* theClipRect, RectList* theDrawnAreas, int* theWidth);
	static void				EnableAlphaCorrection(bool alphaCorrect = true)
	{
		mAlphaCorrectionEnabled = alphaCorrect;
	}
	static void				SetOrderedHashing(bool orderedHash = true)
	{
		mOrderedHash = orderedHash;
	}
	SexyChar				GetMappedChar(SexyChar theChar);

private:
	ImageFont();

public:
	ImageFont(SexyAppBase* theSexyApp, const std::string& theFontDescFileName, const std::string& theImagePathPrefix = "");
	ImageFont(Image *theFontImage); // for constructing your own image font without a file descriptor
	ImageFont(const ImageFont& theImageFont);
	virtual ~ImageFont();

	// Deprecated
	//ImageFont(Image* theFontImage, const std::string& theFontDescFileName);
	//ImageFont(const ImageFont& theImageFont, Image* theImage);
	
	virtual ImageFont*		AsImageFont() override {	return this; }

	virtual int				CharWidth(SexyChar theChar) override;
	virtual int				CharWidthKern(SexyChar theChar, SexyChar thePrevChar) override;
	virtual int				StringWidth(const SexyString& theString) override;
	virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect) override;

	virtual Font*			Duplicate() override;

	virtual void			SetPointSize(int thePointSize);
	virtual int				GetPointSize();
	virtual void			SetScale(double theScale);
	virtual int				GetDefaultPointSize();
	virtual bool			AddTag(const std::string& theTagName);	
	virtual bool			RemoveTag(const std::string& theTagName);
	virtual bool			HasTag(const std::string& theTagName);
	virtual SexyString		GetDefine(const SexyString& theName);

	virtual void			Prepare();

	static bool				CheckCache(const std::string& theSrcFile, const std::string& theAltData);
	static bool				SetCacheUpToDate(const std::string& theSrcFile, const std::string& theAltData);
	static ImageFont*		ReadFromCache(const std::string& theSrcFile, const std::string& theAltData);
	virtual void			WriteToCache(const std::string& theSrcFile, const std::string& theAltData);

	bool					SerializeRead(void* thePtr, int theSize);

	//this is a temporary solution (soon ResGen3 will endian convert ahead of time)
	bool					SerializeReadEndian(void* thePtr, int theSize);
	int						SerializeWrite(void* thePtr, int theSizeIfKnown = 0);
	
	
	int						GetLayerCount();
	
	void					PushLayerColor(const std::string& theLayerName, const Color& theColor);
	void					PushLayerColor(int theLayer, const Color& theColor);
	void					PopLayerColor(const std::string& theLayerName);
	void					PopLayerColor(int theLayer);
};

}

#endif // REMOVE_SEXYFONT

#endif //__IMAGEFONT_H__
