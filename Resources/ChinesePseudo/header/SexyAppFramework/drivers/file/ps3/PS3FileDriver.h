#pragma once
#ifndef PS3FILEDRIVER_H_INCLUDED
#define PS3FILEDRIVER_H_INCLUDED


#include "IFileDriver.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cell/cell_fs.h>
#include <sysutil/sysutil_gamecontent.h>

namespace Sexy 
{
	class PS3File : public IFile
	{
	public:
		PS3File(const std::string& theFilename, struct stat* theFileStat);
		PS3File(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer, struct stat* fileStat);
		virtual ~PS3File();
		
		virtual bool IsLoaded() override;
		virtual bool HasError() override;
		virtual void AsyncLoad() override;
		virtual bool ForceLoad() override;
		virtual uint8* GetBuffer() override;
		virtual uint32 GetSize() override;
		virtual void Close() override;
		virtual void DirectSeek(uint64 theSeekPoint) override;
		virtual bool DirectRead(uint8* theBuffer, uint64 theReadSize) override;
		virtual Status DirectReadStatus() override;

		virtual uint64 DirectReadBlockSize() override;

	protected:
		bool InitRead(const std::string& filename, struct stat* fileStat);

	private:
		friend class PS3FileDriver;

		bool mDeleteBuffer;
		uint8* mBuffer;
		uint32 mBufferSize;
		uint32 mSize;
		bool mIsLoaded;
		bool mHasError;

		CellFsAio mAIO;
		int mId;
		
		bool mIsDirect;
		uint32 mReadPos;
		uint32 mReadSize;

		//debug info
		uint32 mDirectReadCount;
		uint32 mLastReadPos;
	};
	
	
	class PS3FileSearch : public IFileSearch
	{
	public:
		DIR* mDir;
		std::string mPath;
		std::string mPattern;
		
		PS3FileSearch(std::string pattern, std::string path, DIR* dir) 
		{ 
			mPattern = pattern; 
			mPath = path;
			mDir = dir; 
		}
		
		virtual ~PS3FileSearch() {};
		
	};
	
	class PS3FileDriver : public IFileDriver
	{
	public:
		PS3FileDriver();
		
		virtual ~PS3FileDriver();
		
		virtual std::string FixPath(const std::string& inFileName);
		virtual bool InitFileDriver(SexyAppBase* theApp) override;
		virtual void InitSaveDataFolder() override;
		virtual std::string GetSaveDataPath() override;
		virtual std::string GetCurPath() override;
		virtual std::string GetLoadDataPath() override;
		virtual IFile* CreateFile(const std::string& path) override;
		virtual IFile* CreateFileDirect(const std::string& path) override;
		virtual IFile* CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		virtual IFile* CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size,
		struct stat* attrData, bool delete_buffer);
		virtual bool SupportsMemoryMappedFiles() { return false; }
//		virtual IFile* CreateFileMemoryMapped(const std::string& thePath);
		virtual uint64 GetFileSize(const std::string& path) override;
		virtual FileTime GetFileTime(const std::string& path) override;
		virtual bool FileExists(const std::string& path, bool* isFolder=NULL) override;
		virtual bool MakeFolders(const std::string& folder) override;
		virtual bool DeleteTree(const std::string& path) override;
		virtual bool DeleteFile(const std::string& path) override;

		virtual IFileSearch* FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool FileSearchEnd(IFileSearch*) override;

		//cellFS callbacks
		static void CellFSAIOComplete(CellFsAio *xaio, CellFsErrno error, int xid, uint64_t size);

		static std::string FixPathStatic( const std::string& inFileName );

		int GetFreeHDDSpace();
	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
		bool		mInitSaveData;

		unsigned int mBootType, mBootAttrs;
		CellGameContentSize mSize;
		char mDirName[CELL_GAME_DIRNAME_SIZE];
	};
}


#endif

