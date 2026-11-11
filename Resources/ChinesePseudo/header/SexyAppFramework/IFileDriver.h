#pragma once
#ifndef IFILEDRIVER_H_INCLUDED
#define IFILEDRIVER_H_INCLUDED

namespace Sexy 
{
	class SexyAppBase;
	
	
	struct FileSearchInfo
	{
		std::string		file_name;
		bool			is_directory;
		FileTime		create_time;
		FileTime		last_write_time;
		FileTime		last_access_time;
        FileTime        birth_time;
		uint64			file_size;
	};
    
    struct VolumeStatistics
    {
        uint64          block_count;        // total blocks on device
        uint64          blocks_free;        // available blocks on device
        uint64          block_size;         // bytes in one block
    };
	
	/**
	 * IFile will load a file into a buffer. 
	 * It's meant to be a thin abstraction over low-level asnychronous file i/o.
	 * It is NOT meant to replicate the c file library. Use the p_f* calls from
	 * PakInterface to do this.
	 */
	class IFile
	{
	public:
		enum Status
		{
			READ_COMPLETE,
			READ_PENDING,
			READ_ERROR,
		};

		virtual ~IFile() {};
		
		virtual bool		IsLoaded() = 0;
		virtual bool		HasError() = 0;
		
		virtual void		AsyncLoad() = 0;
		
		/**
		 * force load will load the file immediately
		 * returns false if there was an error
		 */
		virtual bool		ForceLoad() = 0;
		
		/**
		 * GetBuffer will only have valid data
		 * when IsLoaded is true
		 */
		virtual uint8*		GetBuffer() = 0;
		
		virtual uint32		GetSize() = 0;
		
		virtual void		Close()	= 0;


		/**
		 * The following is the low-level/direct File API.
		 * You should only use these methods if you created
		 * the file with CreateFileDirect
		 * Files created with CreateFileDirect will not
		 * be loaded automatically, thus the following methods
		 * give advanced control over how the file is loaded.
		 */


		/**
		 * DirectSeek only works as an absolute position from the beginning of the 
		 * file AND theSeekPoint must be a DirectReadBlockSize() byte aligned value. 
		 * Don't seek often. Seeks on optical drives can take up to 240 milliseconds!!. 
		 * (this time cost will be absorbed into the next read operation, DirectSeek 
		 * will return immediately)
		 */
		virtual void		DirectSeek(uint64 theSeekPoint) = 0;

		/**
		 * DirectRead will read theReadSize bytes into theBuffer. theBuffer must already
		 * be allocated. theReadSize must be a multiple of DirectReadBlockSize. This will read from
		 * the current file position and update the current file position. Use DirectSeek
		 * to change the file position. Returns true if it succeeded, false if not.
		 * Monitor DirectReadStatus for completion or error information.
		 *
		 * It is not possible to issue multiple reads at the same file. Will return false
		 * if there is still a read outstanding.
		 */
		virtual bool		DirectRead(uint8* theBuffer, uint64 theReadSize) = 0;

		/**
		 * DirectReadStatus will return a Status enum indicating if the read is READ_COMPLETE,
		 * READ_PENDING, or in READ_ERROR.
		 */
		virtual Status		DirectReadStatus() = 0;

		/**
		 * DirectReadBlockSize returns the minimal block size required to read data from
		 * this device. It will always be a multiple of 32 and cross-platform code could 
		 * safely assume that 2048 is a good least-common block size
		 */
		virtual uint64		DirectReadBlockSize() = 0;
	};

	class IFileSearch
	{
	public:
		virtual ~IFileSearch() {};
	
		//The IFileSearch class represents an opaque
		//search object that various systems use.
		//I'm trying to find a way to let pak files and the 
		//file drivers play nicely together. 
		enum SearchType
		{
			UNKNOWN,
			PAK_FILE_INTERNAL,
			DRIVER_INTERNAL,
		};

		SearchType	GetSearchType() { return mSearchType; }

	protected:
		IFileSearch() { mSearchType = UNKNOWN; }

		SearchType mSearchType;
	};
	
	class IFileDriver 
	{
	public:
        // This enum is to designate differentdata path types
        // Used in conjunction with the GetDataPath function
        // The GetDataPath function can be implemented on different platforms
        //  and will return different paths under different conditions
        //  for those platforms
        // Add new path types as needed and update the platform implementations
        enum PathType
        {
            SEXY_ENUM_BEGIN(PathType_),
            PathType_SaveData,
            PathType_LoadData,
            PathType_Cache,
            PathType_NoBackup,
            PathType_Backup,
            SEXY_ENUM_END(PathType_)
        };
        
		static IFileDriver* CreateFileDriver();
		
		virtual ~IFileDriver() {};
		
		virtual bool			InitFileDriver(SexyAppBase* theApp) = 0;
		
		virtual void			InitSaveDataFolder() = 0;

		/**
		 * this patches up directory slashes in theFilename to 
		 * operating system conventions
		 */
		virtual std::string		FixPath(const std::string& theFileName) = 0;
		
		virtual std::wstring	FixPath(const std::wstring& theFileName)
		{
			return StringToWString(FixPath(WStringToString(theFileName)));
		}
		
		/**
		 * This returns the directory that the game should save 
		 * data to. Ie the "AppData" folder on windows
		 * These really should return wstring versions (or only wstring)
		 * currently GetAppDataFolder is string only
		 */
        // SOON TO BE DEPRECATED
		virtual std::string		GetSaveDataPath() = 0;
		
		//PVZ2_CHINESE_BEGIN
		/**
		* This returns the directory that the game should get sys ttf font from
		 */
#ifdef _WIN32
		virtual std::string		GetSysFontPath() = 0;   //NANLANG
#endif

		
		//PVZ2_CHINESE_END
		
		/**
		 * This is the directory that the game will load resource
		 * data from. Usually the dir it's installed to on windows
		 * or the package resources folder on mac. or d:\ on xbox
		 */
        // SOON TO BE DEPRECATED
		virtual std::string		GetLoadDataPath() = 0;
        
		/**
		
		 * This returns the directory that the game should save caches to.
		 * In this context, cache data is data that can be re-created or
		 * re-acquired from external sources and does not need to be
		 * backed up or otherwise guaranteed to be preserved in the long-term.
		 */
        // SOON TO BE DEPRECATED
		virtual std::string		GetCacheDataPath() = 0;
        
		/**
		 * This returns a directory based on the PathType enum passed in (see above)
		 */
		virtual std::string		GetDataPath( PathType inPathType ) = 0;
        
		/**
		 * This returns the directory that the game should save
		 * data to. Ie the "AppData" folder on windows
		 * These really should return wstring versions (or only wstring)
		 * currently GetAppDataFolder is string only
		 */
		virtual std::string		GetDataPathSaveData() = 0;

		/**
		 * This is the directory that the game will load resource
		 * data from. Usually the dir it's installed to on windows
		 * or the package resources folder on mac. or d:\ on xbox
		 */
		virtual std::string		GetDataPathLoadData() = 0;
		
		/**
		 * This returns the directory that the game should save caches to.
		 * In this context, cache data is data that can be re-created or
		 * re-acquired from external sources and does not need to be
		 * backed up or otherwise guaranteed to be preserved in the long-term.
		 */
        virtual std::string		GetDataPathCacheData() = 0;
		
		/**
		 * This returns a directory that won't get automatically backed up to a
         * server through automatic services like iCloud (for iOS) or any future
         * equivalents for other platforms. This folder is meant to store support
         * files, meaning files that can be redownloaded or regenerated by the
         * program.
		 */
        virtual std::string		GetDataPathSupportDataNoBackup() = 0;
        
		/**
		 * This returns a directory that will get automatically backed up to a
         * server through automatic services like iCloud (for iOS) or any future
         * equivalents for other platforms. This folder is meant to store support
         * files, meaning files that can be redownloaded or regenerated by the
         * program.
		 */
        virtual std::string		GetDataPathSupportDataBackup() = 0;

		/**
		 * This is used to verify that a path you want to write out to is a valid
         * directory for the platform you are on
		 */
        virtual bool            IsDataPathValid( const std::string& inPath ) = 0;
		
		virtual std::string		GetCurPath() = 0;

		virtual IFile*			CreateFile(const std::string& thePath) = 0;
		
		virtual IFile*			CreateFile(const std::wstring& thePath)
		{
			return CreateFile(WStringToString(thePath));
		}
		
		/**
		 * This will load the file into a buffer that already exists
		 * closing the file will not delete the buffer.
		 * Note that many platforms have strict alignment rules for 
		 * async loading, this buffer will need to be aligned.
		 */
		virtual IFile*			CreateFileWithBuffer(const std::string& thePath, uint8* theBuffer, uint32 theBufferSize) = 0;
		
		virtual IFile*			CreateFileWithBuffer(const std::wstring& thePath, uint8* theBuffer, uint32 theBufferSize)
		{
			return CreateFileWithBuffer(WStringToString(thePath), theBuffer, theBufferSize);
		}

		/**
		 * This will open the file and return an IFile object but will not 
		 * START loading the file asynchronously. Instead, the IFile can be used
		 * more directly to seek and load smaller parts of the file at a time.
		 */
		virtual IFile*			CreateFileDirect(const std::string& thePath) = 0;
		
		virtual IFile*			CreateFileDirect(const std::wstring& thePath)
		{
			return CreateFileDirect(WStringToString(thePath));
		}

		/**
		 * Some platforms can support memory mapping large files.
		 * If the file driver returns true for SupportsMemoryMappedFiles() then
		 * it is possible to CreateFileMemoryMapped()
		 */
		virtual bool			SupportsMemoryMappedFiles() { return false; }

		virtual IFile*			CreateFileMemoryMapped(const std::string& thePath) { return NULL; }

		virtual IFile*			CreateFileMemoryMapped(const std::wstring& thePath) 
		{
			return CreateFileMemoryMapped(WStringToString(thePath));
		}
		
		virtual uint64			GetFileSize(const std::string& thePath) = 0;
		
		virtual uint64			GetFileSize(const std::wstring& thePath)
		{
			return GetFileSize(WStringToString(thePath));
			
		}

        virtual FileTime		GetFileLastAccessTime(const std::string& thePath) = 0;
		
		virtual FileTime		GetFileLastAccessTime(const std::wstring& thePath)
		{
			return GetFileLastAccessTime(WStringToString(thePath));
		}

        virtual FileTime		GetFileTime(const std::string& thePath) = 0;
		
		virtual FileTime		GetFileTime(const std::wstring& thePath)
		{
			return GetFileTime(WStringToString(thePath));
		}

		virtual FileTime		GetFileBirthTime(const std::string& thePath) = 0;
		
		virtual FileTime		GetFileBirthTime(const std::wstring& thePath)
		{
			return GetFileBirthTime(WStringToString(thePath));
		}

		virtual bool			FileExists(const std::string& thePath, bool* isFolder=NULL) = 0;
		
		virtual bool			FileExists(const std::wstring& thePath, bool* isFolder=NULL)
		{
			return FileExists(WStringToString(thePath), isFolder);
		}
		
		/**
		 * Only expect MakeFolders and DeleteTree/DeleteFile to work on Windows and Macosx
		 * These should only be used for debug or specific system integration, save games will
		 * be handled through a different abstraction
		 */
		virtual bool			MakeFolders(const std::string& theFolder) = 0;
		
		virtual bool			MakeFolders(const std::wstring& theFolder)
		{
			return MakeFolders(WStringToString(theFolder));
		}
		
		virtual bool			DeleteTree(const std::string& thePath) = 0;
		
		virtual bool			DeleteTree(const std::wstring& thePath)
		{
			return DeleteTree(WStringToString(thePath));
		}
		
		virtual bool			DeleteFile(const std::string& thePath) = 0;
		
		virtual bool			DeleteFile(const std::wstring& thePath)
		{
			return DeleteFile(WStringToString(thePath));
		}
		
		virtual bool			MoveFile(const std::string& thePathSrc, const std::string& thePathDest)
		{
			return false;
		}
		
		virtual bool			MoveFile(const std::wstring& thePathSrc, const std::wstring& thePathDest)
		{
			return MoveFile(WStringToString(thePathSrc),WStringToString(thePathDest));
		}
		
	
		virtual IFileSearch*	FileSearchStart(const std::string& theCriteria, FileSearchInfo* outInfo) = 0;
		
		virtual IFileSearch*	FileSearchStart(const std::wstring& theCriteria, FileSearchInfo* outInfo)
		{
			return FileSearchStart(WStringToString(theCriteria), outInfo);
		}
		
		
		virtual bool			FileSearchNext(IFileSearch* theSearch, FileSearchInfo* theInfo) = 0;
		virtual bool			FileSearchEnd(IFileSearch* theInfo) = 0;
        
        virtual bool            GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats) = 0;


		//PVZ2_CHINESE_START CJD_RSG3
#ifdef HOST_WINDOWS
		/**
		* This returns the directory that the game should get sys ttf font from
		 */

		virtual FileTime		GetFileCreateTime(const std::string& thePath) = 0;
		
		virtual FileTime		GetFileCreateTime(const std::wstring& thePath)
		{
			return GetFileCreateTime(WStringToString(thePath));
		}

        virtual std::string		GetFileCreateTimeReadable(const std::string& thePath) = 0;
		
		virtual std::string		GetFileCreateTimeReadable(const std::wstring& thePath)
		{
			return GetFileCreateTimeReadable(WStringToString(thePath));
		}

		virtual std::string		GetFileLastAccessTimeReadable(const std::string& thePath) = 0;
		
		virtual std::string		GetFileLastAccessTimeReadable(const std::wstring& thePath)
		{
			return GetFileLastAccessTimeReadable(WStringToString(thePath));
		}

		virtual std::string		GetFileTimeReadable(const std::string& thePath) = 0;
		
		virtual std::string		GetFileTimeReadable(const std::wstring& thePath)
		{
			return GetFileTimeReadable(WStringToString(thePath));
		}

		virtual std::string		GetFileBirthTimeReadable(const std::string& thePath) = 0;
		
		virtual std::string		GetFileBirthTimeReadable(const std::wstring& thePath)
		{
			return GetFileBirthTimeReadable(WStringToString(thePath));
		}
#endif
		//PVZ2_CHINESE_END

	};
}


#endif

