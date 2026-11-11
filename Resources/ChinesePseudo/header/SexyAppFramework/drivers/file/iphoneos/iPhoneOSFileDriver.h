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
	class iPhoneFile : public IFile
	{
	public:
		iPhoneFile(const std::string& theFilename, uint32 theFileSize);
		iPhoneFile(const std::string& theFilename, uint8* buffer, uint32 buffer_size, bool delete_buffer, uint32 theFileSize);
		virtual ~iPhoneFile();
		
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
		
		
		struct aiocb		mAIO;
		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;
	};
	
	class iPhoneFileSearch : public IFileSearch
	{
	public:
		DIR* mDir;
		std::string mPath;
		std::string mPattern;
		
		iPhoneFileSearch(std::string pattern, std::string path, DIR* dir) 
		{ 
			mPattern = pattern; 
			mPath = path;
			mDir = dir; 
		}
		
		virtual ~iPhoneFileSearch() {};
		
	};
	
	class iPhoneOSFileDriver : public IFileDriver
	{
	public:
		iPhoneOSFileDriver();
		
		virtual ~iPhoneOSFileDriver();
		
		virtual	std::string		FixPath(const std::string& thePath) override;
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		
		virtual void			InitSaveDataFolder() override;
		
		virtual std::string		GetSaveDataPath() override;
        
#ifdef _WIN32
        virtual std::string		GetSysFontPath() override;
#endif
        
		virtual std::string		GetLoadDataPath() override;
		
		virtual std::string		GetCacheDataPath() override;
				
		virtual std::string		GetDataPath( IFileDriver::PathType inPathType ) override;
        
		virtual std::string		GetDataPathSaveData() override;
        
		virtual std::string		GetDataPathLoadData() override;
        
		virtual std::string		GetDataPathCacheData() override;
        
        virtual std::string     GetDataPathAppSupportData();
        
		virtual std::string		GetDataPathSupportDataNoBackup() override;
        
		virtual std::string		GetDataPathSupportDataBackup() override;
        
        virtual bool            IsDataPathValid( const std::string& inPath ) override;

		virtual std::string		GetCurPath() override;
		
		virtual IFile*			CreateFile(const std::string& path) override;
		
		virtual IFile*			CreateFileDirect(const std::string& thePath) override;
		
		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																uint32 theFileSize, bool delete_buffer);
		
		virtual uint64			GetFileSize(const std::string& path) override;
#ifdef HOST_WINDOWS
		virtual FileTime		GetFileCreateTime(const std::string& path) override;
#endif
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
        
        virtual bool            GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats) override;

	private:
        virtual void            InitDataFolders();
        
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
		std::string mCacheDataFolder;
		std::string mAppSupportDataFolder;
	};
}


#endif

