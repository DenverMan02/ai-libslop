#pragma once
#ifndef ANDROIDFILEDRIVER_H_INCLUDED
#define ANDROIDFILEDRIVER_H_INCLUDED


#include "IFileDriver.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <aio.h>

namespace Sexy 
{
	class AndroidFile : public IFile
	{
	public:
		AndroidFile(const std::string& theFilename, uint32 theFileSize);
		AndroidFile(const std::string& theFilename, uint8* buffer, uint32 buffer_size, bool delete_buffer, uint32 theFileSize);
		virtual ~AndroidFile();
		
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
		
		// OS-level async IO isn't supported on Android. Is there a more-native abstraction though?
		int 				mFileDesc;
//		struct aiocb		mAIO;
		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;

		bool 				mbIsAndroidArchive;
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
	
	class AndroidFileDriver : public IFileDriver
	{
	public:
		AndroidFileDriver();
		
		virtual ~AndroidFileDriver();
		
		virtual	std::string		FixPath(const std::string& thePath);
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		
		virtual void			InitSaveDataFolder() override;
		
		virtual std::string		GetSaveDataPath() override;
		
		virtual std::string		GetSysFontPath() override;						//PVZ2_CHINESE

		virtual std::string		GetCurPath() override;
		
		virtual std::string		GetLoadDataPath() override;
		
		virtual IFile*			CreateFile(const std::string& path) override;
		
		virtual IFile*			CreateFileDirect(const std::string& thePath) override;
		
		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																uint32 theFileSize, bool delete_buffer);
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual FileTime		GetFileTime(const std::string& path) override;
		
		virtual bool			FileExists(const std::string& path, bool* isFolder=NULL) override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
		
		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;


		static bool			IsAssetFilename( std::string const & path );

// TODO: This sucks!!

	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;


		static char const * sAssetPrefix;

	};
}


#endif

