#ifndef RESSTREAMS_H_INCLUDED
#define RESSTREAMS_H_INCLUDED

#include "Common.h"
#include "SexyAppBase.h"
#include "CompiledMap.h"
#include "IFileDriver.h"
#include "ResStreamsFormat.h"
#include "CritSect.h"
#include "PakLib/PakInterface.h"
#include "ResourceManager.h"
#include "IResStreamsDriver.h"

#if defined HOST_ANDROID
#include <GLES2/gl2.h>
#elif defined HOST_IPHONEOS
#include <OpenGLES/ES2/gl.h>
#elif defined HOST_MACOSX
#include <OpenGL/gl.h>
#elif defined HOST_WINDOWS
//#include <OpenGL/gl.h>
#else
#error BaseGLResStreamsDriver.h not implemented for your platform
#endif

class RgRsbPatcher; // A class in resgen, forward delcare so it can be a friend of RSBPatcher.

namespace Sexy
{

	

class ResStreamsGroup;
class ResStreamsPool;

struct ResStreamsLoadDesc
{
	ResStreamsLoadDesc()
	{
		file = NULL;
		group = NULL;
		pool = NULL;
		instance = 0;
		loading = false;
		resident_loaded = false;
		gpu_data_loaded = false;
		transient_loaded = false;

#ifdef NDEBUG //PVZ2_CHINESE [WuXJ] out put the log while not release
		report_load_stats = false;
#else
        report_load_stats = true;
#endif
        
		want_gpu_data = true;
		want_resident_data = true;

		//state for loading
		started_gpu_decompress = false;
		started_resident_decompress = false;
		
		curResidentReadBytes = 0;
		curGPUReadBytes = 0;
		curTransientReadBytes = 0;
		
		curResidentDecompBytes = 0;
		curGPUDecompBytes = 0;
		curTransientDecompBytes = 0;
		
		//state for decode
		numBytesInHoldoverTile = 0;
		curTexture = 0;
		curTile = 0;
		numTilesToDecode = 0;
		numTilesToRead = 0;
		tileSize = 0;
		numOutstandingDecodes = 0;

		mHoldoverBuffer = NULL;
	}
	
	~ResStreamsLoadDesc()
	{
	}

	inline bool IsFinished()
	{
		return ( loading )
				&& ( !want_gpu_data || gpu_data_loaded ) 
				&& ( !want_resident_data || resident_loaded );
	}
	
	IFile* 				file;
	ResStreamsGroup*	group;
	ResStreamsPool*		pool;
	uint32				instance;
	bool				loading;
	bool				resident_loaded;
	bool				gpu_data_loaded;
	bool				transient_loaded;

	bool 				report_load_stats;

	
	bool				want_gpu_data;
	bool				want_resident_data;
	
	bool				started_gpu_decompress;
	bool				started_resident_decompress;
	bool				started_transient_decompress;
	
	uint32				curResidentReadBytes;
	uint32				curGPUReadBytes;
	uint32				curTransientReadBytes;
	
	uint32				curResidentDecompBytes;
	uint32				curGPUDecompBytes;
	uint32				curTransientDecompBytes;
	
	uint32				numBytesInHoldoverTile;
	uint32				curTexture;
	uint32				curTile;
	uint32				numTilesToDecode;
	uint32				numTilesToRead;
	uint32				tileSize;
	uint32				numOutstandingDecodes;

	IResStreamsDriver::TaskResource *mHoldoverBuffer;
};

typedef std::list<ResStreamsLoadDesc*> ResStreamsLoadList;
	
typedef std::vector<void*> RSTaskList;

#define UNKNOWN_GROUP (uint32)-1
	
#define IS_COMPOSITE_GROUP(x) ((x& 0x10000000)!=0)
#define GET_COMPOSITE_GROUP(x) (x& 0x0FFFFFFF)
#define MAKE_COMPOSITE_GROUP(x) (x|0x10000000)

#ifdef USE_RSB_WHOLE
	#define INIT_RSB "main.rsb"
#else
	#define INIT_RSB "dynamic.rsb"
#endif


class ResStreamsManager
{
public:
	enum GroupStatus
	{
		NOT_RESIDENT,
		DELETING,
		PREPARING,
		RESIDENT,
		
	};

	/**
	 * For now, the initial package load will be synchronous.
	 * This operation should only be performed at the init of 
	 * a game, so hopefully no frames will have been drawn yet.
	 *
	 * The initial package load is VERY small and is primarily
	 * the group stream and pool info for the game along with 
	 * an optional every file index (used for legacy games, or games
	 * that haven't been file-access optimized)
	 *
	 * Unfortunately, it will likely also be used for content packages,
	 * so that will have to be asynchronous.
	 *
	 * Returns true if the package was succesfully loaded and is ready
	 * to stream in resources.
	 */
	bool 			NeedDecompressRsb(const std::string& theFileName, const std::string& PhonePath = "", const std::string& SDCardPath = "");
	bool			InitializeWithRSB(const std::string& theFileName, const std::string& PhonePath = "", const std::string& SDCardPath = "", bool canIgnore = false);
    
    /*
     for DLC
     add rsb file from lua
     rsb files download from network
     */
    bool    AddRSB(const std::string basePath
                   , const std::string& theFileName
                   , const std::string& PhonePath = ""
                   , const std::string& SDCardPath = ""
                   , bool canIgnore = false);
    
    bool    AddDLCRSB(const std::string basePath
                   , const std::string& theFileName
                   , const std::string& PhonePath = ""
                   , const std::string& SDCardPath = ""
                   , bool canIgnore = false);
    
    bool    DecompressRsbFile(const std::string basePath
                      , const std::string& theFileName
                      , const std::string& PhonePath
                      , const std::string& SDCardPath
                      , bool canIgnore
                      , std::string& tarRsbPath);
    
    /**
     * Resets ResStreamsManager back to a pre-initialized (with rsb) state.
     * Call this before messing with the currently being used rsb to ensure
     * There isn't an open file handle on the rsb.
     */
    void            Clear();

	/**
	 * Returns true if the manager has been initialized with an RSB file
	 * successfully.
	 */
	bool			IsInitialized(const std::string& theRsbName);

	/**
	 * Find the groupId for this group's name. Accesses are faster if using
	 * the groupId. Returns (uint32)-1 if the group could not be found.
	 */
	uint32			LookupGroup(const std::string& theGroupName);
	int             LookupGroupIndex(const std::string& theGroupName);

	/**
	 * Returns true if the group is loaded. This is the same
	 * as GetGroupStatus() == RESIDENT
	 */
	bool			IsGroupLoaded(const std::string& theGroupName);
	bool			IsGroupLoaded(uint32 theGroupId);

	/**
	 * This returns the group's current status.
	 */
	GroupStatus		GetGroupStatus(const std::string& theGroupName);
	GroupStatus		GetGroupStatus(uint32 theGroupId);

	/**
	 * This will prepare a group to be loaded. This will return
	 * false if the group could not be prepared for loading, 
	 * which is usually because there isn't a pool location 
	 * available for it.
	 */
	bool			LoadGroup(const std::string& theGroupName);
	bool			LoadGroup(uint32 theGroupId);


	/**
	 * This will synchronously load a group and return true if the
	 * load was successful, false if it was not
	 */
	bool			ForceLoadGroup(const std::string& theGroupName, const std::string& theDbgReason = "");
	bool			ForceLoadGroup(uint32 theGroupId, const std::string& theDbgReason = "");

	/**
	 * This returns true if it is currently possible to load the
	 * group stream. This will return false if there is no
	 * memory available to allocate the group OR the pool that the 
	 * group belongs to is full.
	 */
	bool			CanLoadGroup(const std::string theGroupName);
	bool			CanLoadGroup(uint32 theGroupId);

	/**
	 * This will delete the group and the resources associated with,
	 * returning the resources to the pool if they came from one.
	 * 
	 * This will also cancel a group load if the group is in 
	 * the process of loading.
	 *
	 * note: because some resources can be "in flight" for multiple
	 * frames (textures, primarily), the delete may not happen right 
	 * away. Call GetGroupStatus to get specifics on if it has been
	 * deleted. GetGroupStatus will return NOT_RESIDENT if it is no
	 * longer in memory
	 */
	bool			DeleteGroup(const std::string& theGroupName);
	bool			DeleteGroup(uint32 theGroupId);

	/**
	 * This returns true if there was a error loading in group data.
	 * At the moment this is pretty much a fatal error. (may change 
	 * when content package support is added)
	 * May callback into App when this happens as well, because it's
	 * usually so fatal. Typically this would be caused by a optical-disc
	 * read error or the memory unit that the game is running on being 
	 * pulled out during gameplay.
	 */
	bool			HasError();

	/**
	 * Returns true if the ResStream bundle has a global file index. 
	 * RSB Files can optionally be built without the global index to save RAM.
	 * This is for backwards compatibility if the app hasn't been optimized for 
	 * RSB usage.
	 */
	bool			HasGlobalFileIndex();

	/**
	 * This method will work regardless of the existance of a global file index.
	 * It will scan through the file indices of the currently loaded groups looking for 
	 * this file and will return the first group it finds the file in.
	 */
	uint32			GetLoadedGroupForFile(const std::string& theFileName);

	/**
	 * This method will get the groupId for the file in question, however it will
	 * only work for unloaded groups if HasGlobalFileIndex is true.  If inCheckLoadedGroupsFirst
	 * is true, GetLoadedGroupForFile will be called internally first, and return that group
	 * if successful.  Otherwise, the global file index will be checked and the returned
	 * groupId will be the first group that the file belongs to (note that files can belong
	 * to multiple groups for data-redundancy reasons).  If inEnsureGroupLoaded is true,
	 * an unloaded group will be force-loaded before before the method returns.
	 */
	uint32			GetGroupForFile(const std::string& theFileName, bool inCheckLoadedGroupsFirst = true, bool inEnsureGroupLoaded = true);

	/**
	 * GetResidentFileBuffer returns the address and size in memory of a file located
	 * in resident data inside of a group bundle.
	 *  
	 *  Specify the groupId that you want the file data from, or set theGroupId to UNKNOWN_GROUP.
	 *   Setting theGroupId to UNKNOWN_GROUP will require scanning over all loaded groups and may
	 *   return the file data from a group other than the one intended (if redundant data exists)
	 *
	 * This data is only valid as long as the group is in the RESIDENT state
	 *
	 * returns false if the file could not be found.
	 */
	bool			GetResidentFileBuffer(uint32 theGroupId, const std::string& theFileName, uint8** theBuffer, uint32* theSize);
	
	/**
	 * A utility function for getting some code working with RSB easier.
	 * Use the rest of the p_f* functions on this to work with it (including p_fclose)
	 */
	PFILE*			GetPakFileFromResidentBuffer(uint32 theGroupId, const std::string& theFileName);

	/**
	 * GetImage will return an image backed by a texture from the GPU data section.
	 *
	 * Specify the groupId that you want the file data from, or set theGroupId to UNKNOWN_GROUP.
	 *   Setting theGroupId to UNKNOWN_GROUP will require scanning over all loaded groups and may
	 *   return the file data from a group other than the one intended (if redundant data exists)
	 *
	 * This image is only valid as long as the group is in the RESIDENT state
	 *
	 * The caller is responsible for deleting the returned Image object (deleting the image object 
	 *  will not delete the texture backing, that is the responsibility of the ResStreamsManager).
	 *
	 * returns false if the file could not be found.
	 */
	bool			GetImage(uint32 theGroupId, const std::string& theFileName, Image**);
	
    /**
     * This gets the number of bytes currently loaded in for a group. It will return GetTotalBytesForGroup 
     * if the group is already resident, 0 for not_resident and a number in between that represents a currently
     * known amount of bytes processed.
     */
    uint32          GetBytesLoadedForGroup(uint32 theGroupId);
    
    /**
     * This gets the number of bytes that makes up the group's data size as streamed in. It's not the size 
     * of the group loaded into RAM (but can be close) because that is dependent on other system issues, alignment
     * etc... This is used primarily to get an accurate loading progress for groups. 
     */
    uint32          GetTotalBytesForGroup(uint32 theGroupId);

    uint32			GetDiscSpaceForGroup(uint32 theGroupId);

	/**
	 * Check to see if a given group's resources are still intact 
	 * returns true if all is valid
	 *         false if a resource has been unloaded - perhaps on a focus-loss
	 */
	bool ValidateGroupResources( int iGroupIdx );
	void ForceLoadGPUData( int iGroupIdx );

	/**
	 * These load the file index for the group (synchronously), without loading the group itself.
	 * Used for streaming directly from the .rsb.
	 */
	bool			LoadGroupFileIndex(const std::string& theGroupName);
	bool			LoadGroupFileIndex(uint32 theGroupId);

	/**
	 * These unload the file index that was loaded by LoadGroupFileIndex().
	 */
	bool			UnloadGroupFileIndex(const std::string& theGroupName);
	bool			UnloadGroupFileIndex(uint32 theGroupId);

    /**
     * This gets a file's location in the .rsb, as well as its size.  Used for streaming directly from the .rsb. 
	 */
	bool			GetFileLocation(uint32 theGroupId, const std::string& theFileName, uint32* theIndex, uint32* theSize) const;

    /**
     * This just returns the name of the .rsb file.  Used to get a low-level file handle when streaming directly from the .rsb. 
	 */
// [PVZ CHANGE BEGIN] 
// dsiems - Fixing RSB paths (if content gets downloaded it's not in the app directory.)
	std::string		GetRSBPath() { return mRSBPath; }

	std::string		GetRSBPath(uint32 i_groupId);
// [PVZ CHANGE END]
	/**
	 * GotFocus() - called when the main application gains focus from the OS - Used to ensure that
	 * critical resources like textures weren't lost in application state transtion
	 */
	void GotFocus();

	/**
	 * LostFocus() - called when the main application loses focus to the OS - Used to ensure that
	 * we're in a good state when we regain focus as well as ensure that we're a good app citizen
	 * on resource-constrained devices
	 */
	void LostFocus();


// [PVZ2 CHINESE BEGIN]
	void CreateRSBinLocalPath(const std::string& PhonePath, const std::string& SDCardPath,
			const std::string& RSBFileName, const Buffer* pRSBBuffer,
			long i_phoneBlockFree, long i_phoneBlockSize,
			long i_sdcardBlockFree, long i_sdcardBlockSize);
// [PVZ2 CHINESE END]

	ResStreamsManager(SexyAppBase* theApp);
	virtual ~ResStreamsManager();

	void			Update();


	void			DebugDraw(Graphics* g, const Rect& aRegion);

    void PurgeResidentData(uint32 i_groupId);
    void PurgeResidentData(const std::string& i_groupName);
    
protected:
	void			FlagError();

	bool			IsCompositeChildActive(ResStreamCompositeDescriptor::Child& theChildGroup);

	/**
	 * This returns the uint8* pointer to the file index data if the filename was 
	 * found in a loaded group. This will also set theGroup to the group the file
	 * was found in.
	 */
	uint8*			GetLoadedFileData(const std::string& theFileName, uint32& theGroup);
	
	//void			StartGPUDataTransfer();
	void			KickOffDecodeTask(void* taskPtr);
	void			OnTaskFinished(void* taskPtr);
	
	void			OnResidentDataFinished(ResStreamsLoadDesc* theLoadDesc);
	void			OnGPUDataFinished(ResStreamsLoadDesc* theLoadDesc);
	
	bool			StartResidentDataLoad(ResStreamsLoadDesc* theLoadDesc);
	bool			StartGPUDataLoad(ResStreamsLoadDesc* theLoadDesc);
	
	void			StartLoadNextGroup();
	
	ResStreamsLoadDesc* FindNextGroupToLoad();
	
	void			ExecuteTasks();
	
	void			OnAdvanceTiles(ResStreamsLoadDesc* theLoadDesc);
	
	ResStreamCompositeDescriptor* GetComposite(uint32 theIndex);
	
	struct ManifestLoadContext
	{
		ResourceManager*				mManager;
		const char*						mCompositeName;
		const char*						mGroupName;
		int								mArtResolution;
		ResourceGroup::ResInfoVector*	mResList;
	};
    
    void DebugDrawText(Graphics* g, SexyString text, int x, int y, int width, int justify);
	
private:
    struct RelativeGroupInfo
    {
    	uint32 	mRsbIndex;
    	uint32  mGroupId;

    	RelativeGroupInfo()
    	{
    		mRsbIndex = (uint32)-1;
    		mGroupId = (uint32)-1;
    	}
    };

    struct RSBDesc
    {
    	IFile* mFile;
    	uint32 mBaseIndex;
    	std::string mRsbName;
    	std::string mRsbPath;
    	uint8* mCommonBuffer;
    	uint32 mCommonSize;

    	CompiledMap mFileToGroupIndex;
    	CompiledMap mGroupNameToIdIndex;
    	CompiledMap mCompositeNameToIdIndex;

    	uint32				mNumGroups;
		ResStreamsGroup*	mGroups;

		uint32				mNumPools;
		ResStreamsPool*		mPools;

		RelativeGroupInfo*	mRelativeGroups;

		RSBDesc();

		~RSBDesc();
    };

    void ClearRSB(const std::string& theRSBName);
    bool LoadGroup(RSBDesc* pRsbDesc, uint32 theGroupId);
    bool DeleteGroup(RSBDesc* pRsbDesc, uint32 theGroupId);
    uint32 GetBytesLoadedForGroup(RSBDesc* pRsbDesc, uint32 theGroupId);
    uint32 GetTotalBytesForGroup(RSBDesc* pRsbDesc, uint32 theGroupId);

    uint32 GetDiscSpaceForGroup(RSBDesc* pRsbDesc, uint32 theGroupId);

private:
	SexyAppBase*		mApp;
	bool				mHasError;
	bool				mIsIdle;

	ResStreamsLoadList	mLoadingQueue;

	RSTaskList			mPendingTasks;
	RSTaskList			mExecutedTasks;
	
	CritSect			mLoadingQueueCritSect;

	bool				mbShouldForceReloadOnFocus;

	std::list<RSBDesc*> mRsbList;

	uint32				 mBaseIndex;

// [PVZ CHANGE BEGIN] 
// dsiems - Fixing RSB paths (if content gets downloaded it's not in the app directory.)
	std::string			mRSBPath;
// [PVZ CHANGE END]
};







class ResStreamsGroup
{
public:
	ResStreamsGroup();
	~ResStreamsGroup();
    
    void                            Reset();

	//this gets called at system startup
	void							InitDescriptor(ResStreamGroupDescriptor* theDesc, uint8* theTexDescsPtr, uint32 theTexDescSize);


	//this gets called when the group loads
	void							InitGroupStream(ResStreamGroupHeader* theHeader, uint32 theInstanceId);

	//this gets called when the group loads only its file index.  The load is done synchronously, since only the
	// file index is being loaded.
	bool							LoadGroupFileIndex(IFile* aFile);

	ResStreamsManager::GroupStatus	GetStatus() { return mStatus; }

	uint8*							GetFileIndexData(const std::string& theFileName);	

	//this just inits the group data pre-load. the actual loading code
	// is managed by the streams manager
	void							StartLoad();

	bool							CanLoad();

	uint8*							GetResidentDataBaseAddress();

	uint8*							GetGPUDataBaseAddress();

#ifdef HOST_WINDOWS
	void*							GetTextureReference(uint32 theTextureId);
	void*                           GetTextureMultiReference(uint32 theTextureId);
#else
	GLuint							GetTextureReference(GLuint theTextureId);
	GLuint                          GetTextureMultiReference(GLuint theTextureId);
#endif

#ifdef HOST_ANDROID
	void*							GetRenderData( uint32 theTextureId );
#endif // HOST_ANDROID

	ResStreamTextureDescriptor*		GetTextureDescriptor(uint32 theTextureId);

	inline uint32							GetNumTextures() { return mNumTexDescs; }

	void operator=(ResStreamsGroup& right);

	std::string							mName;
	ResStreamsManager::GroupStatus		mStatus;

	CompiledMap							mFileIndex;

	uint32								mPoolIndex;
	ResStreamsPool*						mPool;

	uint32								mFileLocation;
	uint32								mFileSize;

	ResStreamGroupDescriptor*			mDesc;

	
	//stats kept for tuning. 
	//Because the ResStreamsManager only gets updated once per frame
	// (except in special circumstances). These stats will only be granular
	// to the update framerate of the device. All stats are in milliseconds
	
	//This is how long it takes to load the package from 
	// the moment the load call is processed (from the loading queue)
	// to the time it finished.
	uint64								mTotalLoadTime;

	//This is the total time spent decoding/copying the data 
	// when loading in. For in-between level loads this is ideally
	// the same as but not over the time spent on disk IO.
	uint64								mDecodeTime;

	//This is the total time spent on disk IO for this group. This should
	// be relatively constant in terms of bytes loaded/time. Location on 
	// optical media could change this, as could disk fragmentation.
	// To reduce this time, compression should be added to the group.
	// For optimal performance, the decompression/decode time should not 
	// exceed the the disk IO time.
	uint64								mDiskIOTime;


	//variables used for stat tracking
	uint64								mLoadStartTime;
	uint64								mDecodeStartTime;
	uint64								mDiskIOStartTime;

	uint32								mLoadedAtInstance;
	
	//only valid while loaded
	ResStreamGroupHeader*				mLoadedHeader;

	uint32						mNumTexDescs;
	uint8*						mTexDescsPtr;
	uint32						mTexDescSize;

#ifdef HOST_WINDOWS
	void**						mTextures_Main;
	void**						mTextures_Multi;
#else
	GLuint*						mTextures_Main;
	GLuint*						mTextures_Multi;
#endif

#ifdef HOST_ANDROID
	void**						mTextureDatas;
#endif

	uint8*						mFileIndexPtr;
	uint32						mFileIndexSize;
};





class ResStreamsPool
{
public:
	ResStreamsPool();
	~ResStreamsPool();

	//this gets called at system startup
	void				InitDescriptor(ResStreamPoolDescriptor* theDesc);


	//This will actually allocate the resources for the pool
	void				Allocate();

	//this will destroy the resources for the pool.
	// Ideally this won't be called (esp on console platforms where
	// fragmentation could kill the app)
	void				Destroy();

	bool				IsInstanceAvailable();

	//Returns the instance id for this group or (uint32)-1
	// if unsuccessful (instances are full)
	// calls for mem write info and texture info use this instance id
	uint32				LockInstanceForGroup(ResStreamsGroup* theGroup, int theGroupIndex);

	//This returns the resident data memory pointer for the given instanceId
	void*				GetResidentDataMemory(uint32 theInstanceId);

	//This returns the GPU data memory pointer for the given instanceId.
	// This will return NULL for platforms that don't support direct GPU data
	// access.
	void*				GetGPUDataMemory(uint32 theInstanceId);

	//TODO this may need to check if the unlock operation is possible...
	//IE checking texture->IsBusy etc...
	void				UnlockInstanceForGroup(ResStreamsGroup* theGroup);
	
	int					GetOccupantCount();
	
	const std::string&	GetName();

	void operator=(ResStreamsPool& right);

public: //these are public for now so that the driver can access them...
	//Some of this data is duplicated from the common header, which will
	// still be in RAM, so it could be re-sourced from that... but I imagine
	// that textures will be a much bigger RAM concern
	std::string					mName;
	
	bool						mAllocated;
	uint32						mNumInstances;


	uint32						mResidentDataSize;
	uint32						mGPUDataSize;
	uint32						mFlags;

	//this is a mapping of instance to group occupant
	ResStreamsGroup**			mOccupant;
	ResStreamsGroup**			mPrevOccupant;

	int*						mOccupantIndex;
	int*						mPrevOccupantIndex;

	struct PoolInstance
	{
		uint8*		mResidentData;
		uint8*		mGPUData;
	};

	PoolInstance*				mInstances;

	uint8*						mResidentBuffer;
	uint8*						mGPUBuffer;
};
    
    class RSBPatchGenerator
    {
    public:
        RSBPatchGenerator(SexyAppBase* inApp);
        
        bool MakePatch(const std::string& inBaseRsbFilePath, const std::string& inTargetRsbFilePath, const std::string& inRsbPatchFilePath);
        
    private:
        // Caller will own the returned buffer and must delete it when it is no longer needed.
        uint8* CreateBinaryDiffData(uint8* inBaseData, uint32 inBaseDataByteCount, uint8* inTargetData, uint32 inTargetDataByteCount, uint32& outBinaryDiffDataByteCount );
        SexyAppBase* mApp;
    };
    
    
    //
    // Provides access to the raw bytes of various parts of an RSB:
    //  - The raw header bytes
    //  - The raw bytes for each group
    //
    // Also provided methods for determining the order of groups
    // as they are found in the RSB.
    //
    // This class is used to break an RSB down into separate resource
    // group (*.rsg) files and for generating an updated rsb from
    // an rsb patch file.
    //
    class ResStreamsUnpacker
    {
    public:
        ResStreamsUnpacker(SexyAppBase* inApp);
        ~ResStreamsUnpacker();
        
        bool Init(const std::string& inRsbFilePath);
        void Close();
        
        // The caller does not own the returned buffer and must not delete it.
        // The caller should also not reference the buffer once this ResStreamsUnpacker object
        // has been deleted or has gone out of scope.
        uint8* GetCommonData(uint32& outCommonDataByteCount);
        
        std::vector<std::string> GetResourceGroupNameOrder();
        
        // Caller will own the returned buffer and must delete it when it is no longer needed.
        uint8* AllocResGroupData(const std::string& inGroupName, uint32& outResGroupDataByteCount);

        bool RsbHasSwappedBytes();
        
    private:
        struct GroupInfo
        {
            GroupInfo(const std::string& inName, uint32 inFileLoc, uint32 inDataSize)
            {
                name = inName;
                file_location = inFileLoc;
                data_size = inDataSize;
            }
            
            std::string name;
            uint32 file_location;
            uint32 data_size;
        };

        SexyAppBase* mApp;
        IFile* mFile;
        ResStreamHeader* mHeader;
        uint8* mCommonBuffer;
        uint32 mCommonBufferSize;
        bool mRsbRequiresByteSwapping;
        
        std::vector<GroupInfo> mGroupInfos;
    };
    
    
    
    class FileWriter;
    class RSBPatcher;
    
    class IRSBPatcherListener
    {
    public:
        // Called when the patching process has begun.
        // Note: I is possible for PatchStarted() to never be called if the patching process fails or
        // is canceled very early in the process.
        virtual void PatchStarted(const RSBPatcher* inPatcher, void* inListenerContext) = 0;
        
        // Called when the patching operation has completed successfully.
        // PatchStarted() will always be called prior to this method being called.
        virtual void PatchComplete(const RSBPatcher* inPatcher, void* inListenerContext) = 0;
        
        // Called if the patching process failed. PatchStarted() may or may not be called prior
        // to this method.
        virtual void PatchError(const RSBPatcher* inPatcher, void* inListenerContext) = 0;
        
        // Called if the patching process was canceled. PatchStarted() may or may not be called prior
        // to this method.
        virtual void PatchCanceled(const RSBPatcher* inPatcher, void* inListenerContext) = 0;
    };
    
    class RSBPatcher
    {
        friend class RgRsbPatcher;
    public:
        enum Status
        {
            Status_Invalid,
            Status_Patching,
            Status_Complete,
            Status_Error,
            Status_Canceling, // Can be in this state after Cancel() has been called, while we're waiting for the Patching thread to exit.
            Status_Canceled
        };

        enum ErrorReason
        {
            ErrorReason_NoError,
            ErrorReason_PatchReadFailure,           // Rsb patch file did not exist or did not have read permission
            ErrorReason_BadPatchRsbHeader,          // Patch rsb header was garbage or of incorrect endianess
            ErrorReason_PatchRsbVersionMismatch,    // Patch rsb version was not the version required by Prime
            ErrorReason_FailedSignatureCheck,       // The base rsb is not the correct rsb to use with this patch file
            ErrorReason_BaseRsbReadFailure,         // Base rsb file did not exist or did not have read permission
            ErrorReason_TargetRsbWriteFailure,      // Could not write target rsb file, either there was not enough free disk space or directory permissions did not allow the target rsb file to be created
            ErrorReason_DiffDecodeError             // Patch rsb file is corrupt
        };
        
        RSBPatcher(SexyAppBase* inApp, IRSBPatcherListener* inListener, void* inListenerContext = NULL);
		RSBPatcher(SexyAppBase* inApp);
        
        void    Start(const std::string& inBaseRsbFilePath, const std::string& inRsbPatchFilePath, const std::string& inPatchedRsbFilePath);
        void    Update();
        float   GetProgress() const;
        
        // Use this to access mStatus (even internal to the class), it
        // ensures that mStatus is accessed safely from multiple threads.
        Status  GetStatus() const;

        // Use this to access mErrorReason (even internal to the class), it
        // ensures that mErrorReason is accessed safely from multiple threads.
        ErrorReason GetErrorReason() const;
        
        // Call to abort the patch generation task. The listener's PatchCanceled() method will eventually be called
        // and the final status will be Status_Canceled.
        void    Cancel();
        
        // Call to find out when the Patching task is finished.
        // $ Note: Update() must be called or IsFinished() will not report correctly.
        bool    IsFinished() const;
        
        // Runs on patching thread
        bool ApplyPatch(const std::string& inBaseRsbFilePath, const std::string& inRsbPatchFilePath, const std::string& inPatchedRsbFilePath);

    private:
        void Init(SexyAppBase* inApp, IRSBPatcherListener* inListener, void* inListenerContext);
        
        // Called only by ApplyPatch(). ApplyPatch() will call this and then clean up the partially generated
        // inPatchedRsbFilePath file if ApplyPatchHelper() returns false (didn't succeed in producing a target rsb).
        bool ApplyPatchHelper(const std::string& inBaseRsbFilePath, const std::string& inRsbPatchFilePath, const std::string& inPatchedRsbFilePath);
        
        static void SynchroniousRSBPatchThreadProc(void* inContext);
        
        // Runs on patching thread
        void SynchroniousRSBPatch();
        
        void SetStatus(Status inStatus);
        void SetErrorReason(ErrorReason inReason);
        bool IsCancelRequested();
        void IncrementTargetRsbBytesProcessed(uint64 inDeltaByteCount);
        
        // Runs on patching thread
        bool ApplyDiff(uint8* inBaseData, uint64 inBaseDataByteCount, uint8* inPatchData, uint64 inPatchDataByteCount, std::string& outTargetData);

        
        SexyAppBase* mApp;
        
        IRSBPatcherListener* mListener;
        void* mListenerContext;
        
        std::string mBaseRsbFilePath;
        std::string mRsbPatchFilePath;
        std::string mPatchedRsbFilePath;
        
        bool mHaveProcessedFirstUpdateSinceStart;
        bool mIsPatchRunning; // True if the patching thread has been started and has not yet finished.
        
        mutable CritSect mCritSect;
        Status mStatus; // access to this field must always be protected by mCritSect
        ErrorReason mErrorReason; // access to this field must always be protected by mCritSect
        
        // These two fields are used to determine patching progress.
        // Access to them must be protected by mCritSect, they are updated by the patching
        // thread and read from by the main thread.
        uint64 mTotalTargetRsbByteCount;
        uint64 mTargetRsbBytesProcessed;    
    };

}

#endif
