#pragma once
#ifndef AIRPLAYFILEDRIVER_H_INCLUDED
#define AIRPLAYFILEDRIVER_H_INCLUDED


#include "IFileDriver.h"



namespace Sexy 
{
	class AirplayFile : public IFile
	{
	public:
		AirplayFile(const std::string& theFilename, int64 theFileSize);
		AirplayFile(const std::string& theFilename, uint8* buffer, uint32 buffer_size, bool delete_buffer, int64 theFileSize);
		virtual ~AirplayFile();
		
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
		bool				InitRead(const std::string& filename, int64 theFileSize);
	private:
		bool				mDeleteBuffer;
		uint8*				mBuffer;
		uint32				mBufferSize;
		uint32				mSize;
		bool				mIsLoaded;
		bool				mHasError;
		

		//
		s3eFile*			mHandle;
		
		bool				mIsDirect;
		uint32				mReadPos;
		uint32				mReadSize;
	};
	
	class AirplayFileSearch : public IFileSearch
	{
	public:
		s3eFileList* mFileList;
		std::string mPath;
		std::string mPattern;
		
		AirplayFileSearch(std::string thePattern, std::string thePath, s3eFileList* theFileList) 
		{ 
			mPattern = thePattern; 
			mPath = thePath;
			mFileList = theFileList; 
		}
		
		virtual ~AirplayFileSearch() {};
		
	};
	
	class AirplayFileDriver : public IFileDriver
	{
	public:
		AirplayFileDriver();
		
		virtual ~AirplayFileDriver();
		
		virtual	std::string		FixPath(const std::string& thePath);
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		
		virtual std::string		GetSaveDataPath() override;
		
		virtual std::string		GetCurPath() override;
		
		virtual std::string		GetLoadDataPath() override;
		
		virtual IFile*			CreateFile(const std::string& path) override;
		
		virtual IFile*			CreateFileDirect(const std::string& thePath) override;
		
		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																int64 theFileSize, bool delete_buffer);
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual FileTime		GetFileTime(const std::string& path) override;
		
		virtual bool			FileExists(const std::string& path, bool* isFolder=NULL) override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
		
		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;
	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
	};
}


#endif

