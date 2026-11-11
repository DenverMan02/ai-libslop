#pragma once
#ifndef MACOSXFILEDRIVER_H_INCLUDED
#define MACOSXFILEDRIVER_H_INCLUDED


#include "IFileDriver.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <aio.h>

namespace Sexy 
{
	class MacosxFile : public IFile
	{
	public:
		MacosxFile(const std::string& theFilename, struct stat* theFileStat);
		MacosxFile(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer, struct stat* fileStat);
		virtual ~MacosxFile();
		
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
		bool				InitRead(const std::string& filename, struct stat* fileStat);
	private:
		bool				mDeleteBuffer;
		uint8*				mBuffer;
		uint32				mBufferSize;
		uint32				mSize;
		bool				mIsLoaded;
		bool				mHasError;
		
		
		struct aiocb		mAIO;
		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;
		
		//debug info
		uint32				mDirectReadCount;
		uint32				mLastReadPos;
	};
	
	
	class MacosxMMapFile : public IFile
	{
	public:
		MacosxMMapFile(const std::string& theFilename, bool isDirect);
		virtual ~MacosxMMapFile();
		
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
		bool				InitRead(const std::string& filename);
	private:
		uint8*				mBuffer;
		uint32				mBufferSize;
		uint32				mSize;
		bool				mIsLoaded;
		bool				mHasError;
		
		
		int					mFileDes;		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;
		
	};
	
	class MacosxFileSearch : public IFileSearch
	{
	public:
		DIR* mDir;
		std::string mPath;
		std::string mPattern;
		
		MacosxFileSearch(std::string pattern, std::string path, DIR* dir) 
		{ 
			mPattern = pattern; 
			mPath = path;
			mDir = dir; 
		}
		
		virtual ~MacosxFileSearch() {};
		
	};
	
	class MacosxFileDriver : public IFileDriver
	{
	public:
		MacosxFileDriver();
		
		virtual ~MacosxFileDriver();
		
		virtual std::string		FixPath(const std::string& inFileName);
		
		virtual bool			InitFileDriver(SexyAppBase* theApp) override;
		
		virtual void			InitSaveDataFolder() override;
		
		virtual std::string		GetSaveDataPath() override;
		
		virtual std::string		GetCacheDataPath() override;
		
		virtual std::string		GetDataPath(PathType inPathType) override;

		virtual std::string		GetDataPathSaveData() override;

		virtual std::string		GetDataPathLoadData() override;
		
        virtual std::string		GetDataPathCacheData() override;
		
        virtual std::string		GetDataPathSupportDataNoBackup() override;
        
        virtual std::string		GetDataPathSupportDataBackup() override;

		virtual bool            IsDataPathValid(const std::string& inPath) override;

		virtual std::string		GetCurPath() override;
		
		virtual std::string		GetLoadDataPath() override;
		
		virtual IFile*			CreateFile(const std::string& path) override;
		
		virtual IFile*			CreateFileDirect(const std::string& path) override;
		
		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																struct stat* attrData, bool delete_buffer);
		
		virtual bool			SupportsMemoryMappedFiles() { return true; }
		
		virtual IFile*			CreateFileMemoryMapped(const std::string& thePath);
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
		virtual bool			MoveFile(const std::string& thePathSrc, const std::string& thePathDest);
		
        
        //virtual FileTime        GetFileCreateTime(const std::string& thePath) override;
        //virtual std::string		GetFileCreateTimeReadable(const std::string& thePath) override;
        virtual FileTime		GetFileLastAccessTime(const std::string& thePath) override;
        //virtual std::string		GetFileLastAccessTimeReadable(const std::string& thePath) override;
        virtual FileTime		GetFileTime(const std::string& thePath) override;
        //virtual std::string		GetFileTimeReadable(const std::string& thePath) override;
		virtual FileTime		GetFileBirthTime(const std::string& thePath) override;
		//virtual std::string		GetFileBirthTimeReadable(const std::string& thePath) override;
        
		virtual bool			FileExists(const std::string& thePath, bool* isFolder=NULL) override;
		
		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;
        
        virtual bool            GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats) override;
	private:
		SexyAppBase* mApp;
		std::string mCacheDataFolder;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
		bool		mInitCacheData;
		bool		mInitSaveData;
	};
}


#endif

