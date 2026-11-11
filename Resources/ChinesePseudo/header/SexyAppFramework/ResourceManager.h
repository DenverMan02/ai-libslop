#ifndef __SEXY_RESOURCEMANAGER_H__
#define __SEXY_RESOURCEMANAGER_H__

#include "Common.h"
#include "Point.h"
#include "Image.h"
#include "SexyAppBase.h"
#include "AutoCrit.h"
#include "RtObject.h"
#include "RtDb.h"
#include "RtSerial.h"
#include "ResourceTypes.h"
#include <string>
#include <map>

#ifndef HOST_WINDOWS
#include "EAStdC/EAHashString.h"
#endif

namespace ImageLib
{
class Image;
};

namespace Test {
	extern bool gTestFrameworkIsRunning;
};

#define RES_HASH_FUNC(x) EA::StdC::FNV64_String8(x)
#define RES_HASH_TYPE uint64

namespace Sexy
{

class Image;
class SoundInstance;
class SexyAppBase;
class Font;
class ImageFont;
class PrimeFont;
class PopAnim;
class PIEffect;
class RenderEffectDefinition;
class SoundResource;
class SoundBank;

typedef std::map<std::string, std::string>	StringToStringMap;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ResourceInfoTypes { class GenericResFileRes; }

class GenericResFile
: public BaseResource
{
public:
	RT_CLASS_DEFINE(GenericResFile, BaseResource, ResourceClass);
	typedef ResourceInfoTypes::GenericResFileRes InfoClass;

protected:
	std::string mFilePath;
	friend class ResourceInfoTypes::GenericResFileRes;

public:
	// simple filename indirection for now; will be expanded in the future (just trying
	// to abstract the idea of hard filenames away from the game code, which is a good
	// first step for now)
	
	inline const char* GetFilePath() const { return mFilePath.c_str(); }
};

// this structure is used directly by the Rg3 source code generator; make sure
// that any changes are propagated over to there as well
class ResGenInfo
{
public:	
	std::string				mRgExePath;
	int						mRgMajorVersion;
	int						mRgMinorVersion;
	std::string				mResPropsUsed;
	std::string				mResWatchFileUsed;
	std::string				mRgTargetName;
	std::vector<uint32>		mRgLocales;
	std::string				mRelSrcRootFromDist;

	ResGenInfo();
};

class ResourceInfoClass;
class ResourceInfo;
class ResourceGroup;
    
class ResourceInfoClass
: public RtClass
{
public:
	typedef std::map<RES_HASH_TYPE, ResourceInfo*> ResMap;
	typedef bool (*FPreCreateFilter)(ResourceManager*);

protected:
	RtClass* mInstanceClass;
	FPreCreateFilter mPreCreateFilterFunc;
	RtName mManifestTypeName;

public:
	RT_CLASS_DEFINE(ResourceInfoClass, RtClass, RtClass) {}

	ResMap mResMap;

	ResourceInfoClass()
	: mInstanceClass(NULL)
	, mPreCreateFilterFunc(NULL)
	{}

	void SetInstanceClass(RtClass* inInstanceClass) { mInstanceClass = inInstanceClass; }
	RtClass* GetInstanceClass(bool inInherited = true) const
	{
		if (mInstanceClass || !inInherited)
			return mInstanceClass;
	
		for (const ResourceInfoClass* cls = this; cls; cls = cls->GetSuper()->Cast<ResourceInfoClass>())
		{
			if (cls->mInstanceClass)
				return cls->mInstanceClass;
		}
		return NULL;
	}

	void SetPreCreateFilterFunc(FPreCreateFilter inFunc) { mPreCreateFilterFunc = inFunc; }
	FPreCreateFilter GetPreCreateFilterFunc() { return mPreCreateFilterFunc; }

	void SetManifestTypeName(const RtName& inName) { mManifestTypeName = inName; }
	RtName GetManifestTypeName() { return mManifestTypeName; }
};

class ResourceInfo
: public RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(ResourceInfo, RtObject, ResourceInfoClass) {}

	ResourceManager* mManager;
	int mReloadIdx;
	RtId mRtId;
	RtId mInstanceRtId;
	RtId mSrcRefResInfo;
	ResourceGroup* mResGroup;
	const char* mId;
	const char* mPath;
	std::string mIdStorage;
	std::string mPathStorage;
	int mArtRes;
	uint32 mLocSet;
	bool mFromProgram;

	ResourceInfo()
	: mManager(NULL)
	, mReloadIdx(0)
	, mResGroup(NULL)
	, mId(NULL)
	, mPath(NULL)
	, mArtRes(0)
	, mLocSet(0)
	, mFromProgram(false)
	{}
	virtual ~ResourceInfo()
	{}

	std::string GetCoreIdString()
	{
		std::string anId = mId;
		std::string::size_type aPipePos = anId.find('|');
		if (aPipePos != std::string::npos)
			anId = anId.substr(0, aPipePos);
		return anId;
	}

	void DeleteResource();
	virtual void ApplyConfig() { }

	virtual bool IsResourceValid() { return GetInstanceRtId(); }
	virtual bool DoLoad() = 0;
	virtual bool ParseRton() = 0;
	inline RtId GetInstanceRtId() { return mInstanceRtId; }
	inline BaseResource* GetInstancePtr()
	{
		RtWeakPtr<BaseResource> ptr(GetInstanceRtId());
		return ptr;
	}

	inline RtId GetRtId() { return mRtId; }
	inline void SetRtId(const RtId& inId) { mRtId = inId; }
};

class ResourceGroup
: public RtObject
{
public:
	RT_CLASS_DEFINE(ResourceGroup, RtObject, RtClass) {}

	typedef std::vector<ResourceInfo*> ResInfoVector;

	ResourceManager* mManager;
	bool mIsComposite;
	bool mIsLoaded;
	int mArtRes;
	uint32 mLocSet;
	RtName mGroupName;
	ResourceGroup* mParentGroup;
	std::vector<ResourceGroup*> mSubGroups;
	ResInfoVector mResInfoVector;
	float mLoadPercent;
	RtId mRtId;
	SharedImageMap mSharedImageMap;
	bool mIsFileIndexLoaded;

	ResourceGroup();
	~ResourceGroup();

	inline ResourceGroup* GetLoadableGroup() { return mParentGroup ? mParentGroup : this; }
    inline bool IsLoadableGroup() { return mParentGroup == NULL; }
	inline bool IsLoaded() { return mIsLoaded; }

	void Preload();
	bool Load();
	bool Unload();
    
    bool VerifyHasNoSoundBanks();

	/**
	 * These are used to load a file index for a group into memory, without loading the group itself.
	 * This is a synchronous load, since the file index should generally be relatively small.
	 */
	inline bool IsFileIndexLoaded() { return mIsFileIndexLoaded; }
	bool LoadFileIndex();
	bool UnloadFileIndex();

	int GetResourceCount(ResourceInfoClass* theType=NULL, bool curArtResOnly=true, bool curLocSetOnly=true);
	template <class T> int GetResourceCountT(bool curArtResOnly=true, bool curLocSetOnly=true)
	{
		return GetResourceCount(RTC(T::InfoClass), curArtResOnly, curLocSetOnly);
	}

	void GetResources(std::vector<ResourceInfo*>& outResourceInfoList, ResourceInfoClass* theType = NULL, bool curArtResOnly=true, bool curLocSetOnly=true);

	void DebugDump(std::string& theDestStr);
};

namespace ResourceInfoTypes
{
	class ImageRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::ImageRes, ResourceInfo, ResourceInfoClass);

//		std::string mVariant;
		Point mOffset;
		bool mA4R4G4B4;
		bool mA8R8G8B8;
		bool mDither16;
		bool mPurgeBits;
//		bool mCubeMap;
//		bool mVolumeMap;
		bool mNoTriRep;
		bool mIsAtlas;
		int mRows;
		int mCols;	
//		const char*	mAtlasName;
		std::string mAtlasNameStorage;
        uint16	mAtlasX;
        uint16	mAtlasY;
        uint16	mAtlasW;
        uint16	mAtlasH;

		ImageRes() { /*mType = ResType_Image; mAtlasName=NULL;*/}
		virtual void ApplyConfig() override;
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
		static bool StaticPreCreateFilter(ResourceManager* theManager);
	
		inline RtWeakPtr<Image> GetImage() { return mInstanceRtId; }
	};

	class SoundRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::SoundRes, ResourceInfo, ResourceInfoClass);

		double mVolume;
		int mPanning;

		SoundRes() { /*mType = ResType_Sound;*/ mVolume = -1.0f; mPanning = 0;}
		virtual void ApplyConfig() override;
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
		virtual bool IsResourceValid() override;
	
		inline RtWeakPtr<SoundResource> GetSound() { return mInstanceRtId; }
	};
#if SEXY_IS_WWISE_ENABLED
	class SoundBankRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::SoundBankRes, ResourceInfo, ResourceInfoClass);

		SoundBankRes() { /*mType = ResType_SoundBank;*/}
		virtual void ApplyConfig() override;
		virtual bool DoLoad() override { return DoLoadInternal(true); }
		virtual bool ParseRton() override;
		virtual bool IsResourceValid() override;
	
        inline bool DoPrepare() { return DoLoadInternal(false); }
		inline RtWeakPtr<SoundBank> GetSoundBank() { return mInstanceRtId; }
        
	protected:
		bool DoLoadInternal(bool fullLoad);
	};
#endif

#ifndef REMOVE_SEXYFONT
	class FontRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::FontRes, ResourceInfo, ResourceInfoClass);

		std::string mTags;

		// For SysFonts
		bool mSysFont;
		bool mBold;
		bool mItalic;
		bool mUnderline;
		bool mShadow;
		int mSize;

		FontRes() { /*mType = ResType_Font;*/ mSysFont = false; }
		virtual void ApplyConfig() override;
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;

		inline RtWeakPtr<Font> GetFont() { return mInstanceRtId; }
	};
#endif
    
	class PrimeFontRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::PrimeFontRes, ResourceInfo, ResourceInfoClass);
        
		PrimeFontRes() { }
    
		virtual void ApplyConfig() override;
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
        
		inline RtWeakPtr<Font> GetFont() { return mInstanceRtId; }
	};
    
	class PopAnimRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::PopAnimRes, ResourceInfo, ResourceInfoClass);

		double mScale;
        double mRasterizedScale;
        
		PopAnimRes() { /*mType = ResType_PopAnim;*/ mScale = 1.0; mRasterizedScale = 1.0; }
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;

		inline RtWeakPtr<PopAnim> GetPopAnim() { return mInstanceRtId; }
	};

	class PIEffectRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::PIEffectRes, ResourceInfo, ResourceInfoClass);

		PIEffectRes() { /*mType = ResType_PIEffect;*/ }
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
	
		inline RtWeakPtr<PIEffect> GetPIEffect() { return mInstanceRtId; }
	};

	class RenderEffectRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::RenderEffectRes, ResourceInfo, ResourceInfoClass);

		std::string mSrcFilePath;

		RenderEffectRes() { /*mType = ResType_RenderEffect;*/ }
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
	
		inline RtWeakPtr<RenderEffectDefinition> GetRenderEffectDefinition() { return mInstanceRtId; }
	};

	class GenericResFileRes
	: public ResourceInfo
	{
	public:
		RT_CLASS_DEFINE(ResourceInfoTypes::GenericResFileRes, ResourceInfo, ResourceInfoClass);

		GenericResFileRes() { /*mType = ResType_GenericResFile;*/ }
		virtual bool DoLoad() override;
		virtual bool ParseRton() override;
	
		inline RtWeakPtr<GenericResFile> GetGenericResFile() { return mInstanceRtId; }
	};
};

class ResourceManager
{
protected:
	typedef std::map<RtName, ResourceInfoClass*> ManifestTypeNameToInfoClassMap;
	std::vector<ResourceInfoClass*>	mResInfoClasses;
	ManifestTypeNameToInfoClassMap mManifestTypeNameToInfoClassMap;
	ResourceInfoClass::ResMap mResFromPathMap;
	RtDbTable* mResGroupTable;
	RtDbTable* mInfoTable;
	RtDbTable* mHiddenInfoTable;
	RtDbTable* mInstanceTable;
	RtDbTable* mHiddenInstanceTable;
	RtDbTable* mUngroupedInstanceTable;
	int mCurArtResCached;
    std::string mCurArtResKey;
	std::string	mCurLocSetKey;
	std::string	mCurArtResAndLocSetKey;
	SharedImageMap mUngroupedSharedImageMap;
	ResGenInfo mResGenInfo;
	std::string mError;
    int mContentVersion;
    bool mbResetTable;
    uint32 mDelayLoadedRSBSlotCount;

    struct PreLoadTask
    {
    	std::string RSBFileName;
    	Buffer* RSBBuffer;

    	PreLoadTask()
    	{
    		RSBBuffer = NULL;
    	}

    	~PreLoadTask()
    	{
    		delete RSBBuffer;
    	}
    };
    std::list<PreLoadTask*> mPreLoadList;

    std::string mPhonePath;
    std::string mSDCardPath;
    long i_phoneBlockFree;
    long i_phoneBlockSize;
    long i_sdcardBlockFree;
    long i_sdcardBlockSize;

public:
	SexyAppBase* mApp;
	CritSect mLoadCrit;
	CritSect mInitCrit;
	RtSerialRtonReader*	mRtonReader;
	int	mReloadIdx;
#ifdef _DEBUG
	bool mEnableUngroupedResourceRefTracking;
#endif
	
	int	mBaseArtRes;
	int	mCurArtRes;
	uint32 mCurLocSet;

public:
	ResourceManager(SexyAppBase *theApp);
	virtual ~ResourceManager();

	/*
		Initialize the resource manager with the given art res information, RSB file name (optional; may be empty), and manifest file name.
		
		If you use Rg3, its generated "InitResourceManager" function in your Resources.h/.cpp will automatically call this method, so just
		go ahead and use that function instead of calling this directly.
	*/
	bool Init(int inBaseArtRes,
			  int inCurArtRes,
			  const std::string& inRSBFileName = "",
			  const std::string& inManifestFileName = "properties\\resources.rton",
			  bool canIgnore = false);
    
    bool InitForDecompressRsbFile(int inBaseArtRes,
                                  int inCurArtRes,
                                  const std::string& inRSBFileName = "",
                                  const std::string& inManifestFileName = "properties\\resources.rton",
                                  bool canIgnore = false);
    
    /*
     add rsb file in lua
     rsb file downloaded from network
     */
    bool AddRsb(const std::string& basePath,const std::string& inRSBFileName,const std::string& inManifestFileName);
    bool AddDLCRsb(const std::string& basePath,const std::string& inRSBFileName,const std::string& inManifestFileName);
    
	void PreLoadRsb(const std::string& inRSBFileName);
	bool LoadAllRsb();

    void Clear();
    
    bool IsDelayLoadRSB(const std::string& inRSBFileName);
    const std::string& GetLastNonDelayLoadRSBManifestName();
    void InitDelayLoadedRSBSlotCount();
    uint32 GetDelayLoadedRSBSlotCount();
	/*
		Get the number of ResourceInfoClass classes, or a given ResourceInfoClass* by index
	*/
	inline uint32 GetInfoClassCount() { return (uint32)mResInfoClasses.size(); }
	inline ResourceInfoClass* GetInfoClassIndexed(uint32 inIndex) { return mResInfoClasses[inIndex]; }

	/*
		Get the resource group for a given name
	*/
	ResourceGroup* GetResourceGroupNamed(const RtName& inName);
	inline ResourceGroup* GetResourceGroupNamed(const std::string& inName) { return GetResourceGroupNamed(StringToWString(inName)); }

	/*
		Get the ResGen information supplied at initialization
	*/
	inline const ResGenInfo* GetResGenInfo() { return &mResGenInfo; }

	/*
		Get the number of resources of a given type (or all types, if theType is null), across all groups.
		If you want information for a specific group, use the corresponding method of the ResourceGroup itself.
	*/
	int GetResourceCount(ResourceInfoClass* theType=NULL, bool curArtResOnly=true, bool curLocSetOnly=true);
	template <class T> int GetResourceCountT(bool curArtResOnly=true, bool curLocSetOnly=true)
	{
		return GetResourceCount(RTC(T::InfoClass), curArtResOnly, curLocSetOnly);
	}

	/*
		Get the ResourceInfo for a resource of a given type (or any type, if theType is null),
		based on a given string id or file path.
	*/
	ResourceInfo* GetResInfoForStringId(ResourceInfoClass* theType, const std::string& theId);
	template <class T> typename T::InfoClass* GetResInfoForStringIdT(const std::string& theId)
	{
		return (typename T::InfoClass*)GetResInfoForStringId(RTC(T::InfoClass), theId);
	}
	ResourceInfo* GetResInfoForPath(ResourceInfoClass* theType, const std::string& thePath);
	template <class T> typename T::InfoClass* GetResInfoForPathT(const std::string& thePath)
	{
		return (typename T::InfoClass*)GetResInfoForPath(RTC(T::InfoClass), thePath);
	}

	/*
		Get a resource of a given type (or any type, if theType is null), based on a given
		string id or file path.  If the "optional" bool is false, failure to retrieve the
		resource will put the resource manager in an error state as well as throw an exception
		on platforms that support it (hence this should be considered fatal, so you should leave
		the optional flag on unless you really mean it).
	*/


#define IS_OPTIONAL_RESOURCE_BIAS false


	virtual RtWeakPtr<BaseResource> GetResourceForStringId(ResourceInfoClass* theType, const std::string& theId, bool optional = IS_OPTIONAL_RESOURCE_BIAS);
	template <class T> RtWeakPtr<T> GetResourceForStringIdT(const std::string& theId, bool optional = IS_OPTIONAL_RESOURCE_BIAS)
	{
		return GetResourceForStringId(RTC(T::InfoClass), theId, optional);
	}
	RtWeakPtr<BaseResource> GetResourceForPath(ResourceInfoClass* theType, const std::string& thePath, bool optional = IS_OPTIONAL_RESOURCE_BIAS);
	template <class T> RtWeakPtr<T> GetResourceForPathT(const std::string& thePath, bool optional = IS_OPTIONAL_RESOURCE_BIAS)
	{
		return GetResourceForPath(RTC(T::InfoClass), thePath, optional);
	}

#undef IS_OPTIONAL_RESOURCE_BIAS

	/*
		Register a resource into the resource tables, used mostly if you make new
		resources on-the-fly (like MemoryImages etc) which are not part of a group in the
		manifest but need to interact with other APIs that use resource RtIds.  The outId argument
		will have the RtId of the added resource, and will be set in Strong mode if the resource
		isn't backed by a group in the resource manager (meaning that it won't be deleted unless
		somebody takes ownership of it, hence the Strong reference).

		The internal form of this method should only be used by resource type loaders or other
		similar situations where custom control of the registration type is required.
	*/
	void RegisterResource(RtMixedPtrBase& outId, BaseResource* inRes);
	RtId RegisterResourceInternal(RtMixedPtrBase* outId, BaseResource* inRes, const RtId& inInfoId, BaseResource::EResourceRegistrationType inType);

	/*
		Locale support (mostly used by SexyAppBase and drivers for locale setup)
	*/
	std::string GetLocaleFolder(bool addTrailingSlash);
	uint32 GetLocSetForLocaleName(const std::string& theLocaleName); // take in an RFC1766 / RFC4646 locale code (xx-XX), returns a game-supported loc set
    
    //[PvZ2 CHANGE]
    //GetLocSetForLocaleName isn't working, so creating a new one
    uint32 GetLocaleSetForLocaleName(const std::string& theLocaleName);
    //[PvZ2 CHANGE END]
    
	/*
		GetImageOptions - These options are optionally passed into GetImage to adjust behavior.
		They are often unnecessary in applications (most of the settings are only used internally
		by the resource manager) but a couple flags such as mAllowTriReps and mNoShare may have
		some application value in rare circumstances.  If the default behavior is acceptable,
		you can pass in null to GetImage for simplicity.
	*/
	struct GetImageOptions
	{
		bool mTestOnly; // if this is true, only checks for existence of current image; does not attempt to create a new one
		bool mAllowTriReps; // allow tri reps to be built for newly-created images
		bool mIsInAtlas; // internal use: indicates that a newly-generated image is part of an atlas
		bool mNoShare; // if true, no image map is checked for sharing; always generates a new image
		RtId mInfoId; // internal use: RtId of the associated ResourceInfo for the image, if available
		ResourceGroup* mResGroup; // group whos shared image map should be used; if null, the general "ungrouped image" map is used instead
		int mUseWidth, mUseHeight; // internal use: force width and height on a newly-created image within an atlas; only used if mIsInAtlas is true
		std::string mVariant; // internal use: engine variant used as part of the shared image lookup

		GetImageOptions()
		: mTestOnly(false)
		, mAllowTriReps(true)
		, mIsInAtlas(false)
		, mNoShare(false)
		, mResGroup(NULL)
		, mUseWidth(0), mUseHeight(0)
		{}
	};

	/*
		GetImage - Primary image retrieval method.  The result is placed into outImage, which will be set in Weak mode if the
		image is present in a group (so group load/unload will control the image lifetime), or Strong mode if the image is
		newly created and is ungrouped, meaning its lifetime must be managed explicitly by the strong reference (the image RtId
		will be in the general ungrouped resources table, all of which should be cleaned up prior to app shutdown in order to
		avoid warnings).
	*/
	void GetImage(RtMixedPtr<Image>& outImage, const std::string& theFileName, const GetImageOptions* theOpts = NULL, bool* isNew = NULL);

	/*
		Called by Image dtor to remove images from the ungrouped shared image map; not normally called from game code directly
	*/
	void RemoveUngroupedSharedImage(Image* inImage);

	/*
		RSB-specific bulk-load support methods (CDH FIXME$$$ need to integrate into ResourceGroup API)
	*/


    //returns an amount from 0.0f to 1.0f of the loading progress of all the given groups
    float                   GetLoadResourcesListProgress(const std::vector<std::string>& theGroups);

    void                    PrepareLoadResourcesList(const char** theGroups);

	/*
		Error handling methods, mostly used internally and by resource type loaders
	*/
	bool Fail(const std::string& theErrorText);
	inline bool HadError() { return !mError.empty(); }
	inline std::string GetErrorText() { return mError; }
	inline void	ClearError() { mError.clear(); }
	void ShowResourceError(bool doExit = false);

    /*
        Methods for checking resource version/compatiblity with the current app
     */
    int GetContentVersion() { return mContentVersion; }
    
#if SEXY_IS_WWISE_ENABLED
    void SetSoundBankInvaild();
#endif
    
private:

	void InitResourceGen(const ResGenInfo& theInfo);

	ResourceGroup* CreateResourceGroup(const RtName& inName, bool inIsComposite, bool& bExisted);

	bool RemoveAllDelayLoadedRSBConfigFiles();
	uint32 GetAllDelayLoadedRSBSlotCount();
	uint32 ReadResourceFileSlotCount(const std::string& theFilename);
	bool ParseResourcesFile(const std::string& theFilename);
	bool ParseCommonResource(ResourceInfo*& ioRes, ResourceInfoClass* inResType, ResourceGroup* inGroup);
	bool ParseGroupResources(ResourceGroup* theGroup, uint32 uBaseIndex);

	DeviceImage* BuildImage(const std::string& theFileName, bool commitBits = true, bool allowTriReps = true);

	void ResetTables(uint32 inSlotCount);
	bool ResizeTables(uint32 iAdvancedSlotCount, const std::string& theFilename);
	void OnInstanceTableObjectFault(const RtId& inId);	

	bool ReplaceResource(ResourceInfoClass* theType, const std::string& theId, BaseResource* theRes);
	template <class T> bool ReplaceResourceT(const std::string& theId, T* theRes)
	{
		return ReplaceResource(RTC(T::InfoClass), theId, theRes);
	}

	inline void DeleteResource(ResourceInfoClass* theType, const std::string& theId)
	{
		ReplaceResource(theType, theId, NULL);
	}
	template <class T> void DeleteResourceT(const std::string& theId)
	{
		DeleteResource(RTC(T::InfoClass), theId);
	}

	RtWeakPtr<BaseResource> LoadResourceForStringId(ResourceInfoClass* theType, const std::string& theName);
	template <class T> RtWeakPtr<T> LoadResourceForStringIdT(const std::string& theName)
	{
		return LoadResourceForStringId(RTC(T::InfoClass), theName);
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifdef SUPPORT_EXCEPTIONS
	struct ResourceManagerException : public std::exception
	{
		std::string what;
		ResourceManagerException(const std::string &theWhat) : what(theWhat) { }
		~ResourceManagerException() throw() {}
	};
#endif

typedef std::map<std::string, ResGenInfo> ResGenInfoMap;

class ResourceManagerInfo
{
public:
	static ResourceManagerInfo* sInstance;
	ResGenInfoMap mResGenInfoMap;
};

class AutoInitResourceGen3
{
public:
	AutoInitResourceGen3(const std::string& theResourceManifestFileName, const ResGenInfo& theInfo);
};

}

#endif //__SEXY_RESOURCEMANAGER_H__


