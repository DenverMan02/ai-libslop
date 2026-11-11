#pragma once
#ifndef _ANDROIDFILEDRIVER_H_INCLUDED_
#define _ANDROIDFILEDRIVER_H_INCLUDED_


#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <list>

#include "CritSect.h"
#include "Android_aio.h"
#include "IFileDriver.h"


namespace Sexy 
{
	class AndroidAsyncIOFile : public IFile
	{
	public:
		AndroidAsyncIOFile(const std::string& theFilename, uint32 theFileSize, class AndroidAsyncIOFileDriver * pDriver);
		AndroidAsyncIOFile(const std::string& theFilename, uint8* buffer, uint32 buffer_size, bool delete_buffer, uint32 theFileSize, class AndroidAsyncIOFileDriver * pDriver);
		virtual ~AndroidAsyncIOFile();
		
		virtual bool		IsLoaded() override;
		virtual bool		HasError() override;
		
		virtual void		AsyncLoad() override;
		
		virtual bool		ForceLoad() override;
		
		virtual uint8*		GetBuffer() override;
		
		virtual uint32		GetSize() override;
		
		virtual void		Close()	override;
		
		virtual void		DirectSeek(uint64 theSeekPoint) override;
		
		virtual bool		DirectRead(uint8* theBuffer, uint64 theReadSize) override;
		
		virtual Status		DirectReadStatus() override;
		
		virtual uint64		DirectReadBlockSize() override;
	protected:
		bool				InitRead(const std::string& filename, uint32 theFileSize);
	private:
		bool				mDeleteBuffer;
		uint8*				mBuffer;
		uint32				mBufferSize;
		uint32				mSize;
		bool				mIsLoaded;
		bool				mHasError;
		
		struct AndroidAIO::aiocb		mAIO;
		class AndroidAsyncIOFileDriver * mAsyncDriver;
		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;

		bool				mbIsAndroidArchive;
		uint32				mArchiveOffset;
	};
	
	class AndroidFileSearch : public IFileSearch
	{
	public:
		DIR * mDir;
		std::string mPath;
		std::string mPattern;
		
		AndroidFileSearch(std::string const & pattern, std::string const & path, DIR * dir) 
		{ 
			mPattern = pattern; 
			mPath = path;
			mDir = dir; 
		}
		
		virtual ~AndroidFileSearch() {};
		
	};
	
	class AndroidAsyncIOFileDriver : public IFileDriver
	{
	public:
		AndroidAsyncIOFileDriver();
		
		virtual ~AndroidAsyncIOFileDriver();
		
		virtual	std::string		FixPath(const std::string& thePath);
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		
		virtual void			InitSaveDataFolder() override;
		
        virtual std::string		GetCacheDataPath() override;
        
		virtual std::string		GetSaveDataPath() override;
#ifdef _WIN32
		virtual std::string		GetSysFontPath() override;						//PVZ2_CHINESE
#endif
		virtual std::string		GetCurPath() override;
		
		virtual std::string		GetLoadDataPath() override;
		
		virtual std::string		GetDataPath( IFileDriver::PathType inPathType ) override;
        
		virtual std::string		GetDataPathSaveData() override;
        
		virtual std::string		GetDataPathLoadData() override;
        
		virtual std::string		GetDataPathCacheData() override;
        
		virtual std::string		GetDataPathSupportDataNoBackup() override;
        
		virtual std::string		GetDataPathSupportDataBackup() override;
        
        virtual bool            IsDataPathValid( const std::string& inPath ) override;
		
		virtual IFile*			CreateFile(const std::string& path) override;
		
		virtual IFile*			CreateFileDirect(const std::string& thePath) override;
		
		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, size_t buffer_size,
                                                                  size_t theFileSize, bool delete_buffer);
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual FileTime		GetFileLastAccessTime(const std::string& path) override;
		virtual FileTime		GetFileTime(const std::string& path) override;
		virtual FileTime		GetFileBirthTime(const std::string& path) override;
		
		virtual bool			FileExists(const std::string& path, bool* isFolder=NULL) override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
		
		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;
	
        virtual bool            GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats);
	
	
		static bool 		IsAssetFilename( std::string const & path );

	
	// TODO: This sucks!!
	
	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
		std::string mCacheDataFolder;
		std::string mAppSupportDataFolder;

		static char const * sAssetPrefix;

		static void * AsyncIOThreadMain( void * pParam );

		CritSect mAsyncWorkCS;
		Condition mAsyncWorkAvailable;
		Condition mMainWorkAvailable;
		int32 mbAsyncThreadTimeToDie;
		int32 mbAsyncThreadRunning;
		std::list<AndroidAIO::aiocb*> mAsyncIOJobs;
		
	public:
		void CreateIOThread();
		void DestroyIOThread();

		static void StaticAsyncIOThreadMain( void * pParam );
		void AsyncIOThreadMain();
		int SubmitAsyncRead( struct AndroidAIO::aiocb * pContext );
		struct AndroidAIO::aiocb * GetAsyncReadJob();
		void WaitIOThread();
	};
}


#endif // _ANDROIDFILEDRIVER_H_INCLUDED_


