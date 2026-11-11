#pragma once
#ifndef VITAFILEDRIVER_H_INCLUDED
#define VITAFILEDRIVER_H_INCLUDED


#include "IFileDriver.h"
#include <fios2.h>

namespace Sexy 
{
	class VitaFile : public IFile
	{
	public:
		VitaFile(const std::string& theFilename, int64 theFileSize);
		VitaFile(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer, int64 theFileSize);
		virtual ~VitaFile();
		
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
		bool InitRead(const std::string& filename, int64 theFileSize);

	private:
		friend class PS3FileDriver;

		bool mDeleteBuffer;
		uint8* mBuffer;
		uint32 mBufferSize;
		uint32 mSize;
		bool mIsLoaded;
		bool mHasError;

		//CellFsAio mAIO;
		SceFiosFH mFile;
		SceFiosOp mOpenOp;
		SceFiosOp mReadOp; //start with one... maybe more later...
		int mId;
		
		bool mIsDirect;
		uint32 mReadPos;
		uint32 mReadSize;

		//debug info
		uint32 mDirectReadCount;
		uint32 mLastReadPos;
	};
	
	
	class VitaFileSearch : public IFileSearch
	{
	public:
		SceUID mDir;
		std::string mPath;
		std::string mPattern;
		
		VitaFileSearch(std::string pattern, std::string path, SceUID dir) 
		{ 
			mPattern = pattern; 
			mPath = path;
			mDir = dir; 
		}
		
		virtual ~VitaFileSearch() {};
		
	};
	
	class VitaFileDriver : public IFileDriver
	{
	public:
		VitaFileDriver();
		
		virtual ~VitaFileDriver();
		
		virtual std::string FixPath(const std::string& inFileName);
		virtual bool InitFileDriver(SexyAppBase* theApp) override;
		virtual void InitSaveDataFolder() override;
		virtual std::string GetSaveDataPath() override;
		virtual std::string GetCurPath() override;
		virtual std::string GetLoadDataPath() override;
		virtual IFile* CreateFile(const std::string& path) override;
		virtual IFile* CreateFileDirect(const std::string& path) override;
		virtual IFile* CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		virtual IFile* CreateFileWithBufferAndAttrData(	const std::string& path, uint8* buffer, uint32 buffer_size,
														int64 theFileSize, bool delete_buffer);
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


		static std::string FixPathStatic( const std::string& inFileName );

		bool CacheFileFromHostToSD(const std::string &theFileName);
	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
		bool		mInitSaveData;
	};
}


#endif

