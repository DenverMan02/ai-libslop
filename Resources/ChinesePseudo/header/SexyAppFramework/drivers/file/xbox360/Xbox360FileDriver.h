#pragma once
#ifndef XBOX360FILEDRIVER_H_INCLUDED
#define XBOX360FILEDRIVER_H_INCLUDED


#include "IFileDriver.h"

namespace Sexy 
{
	class Xbox360File : public IFile
	{
	public:
		Xbox360File(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer);
		Xbox360File(const std::string& filename); //direct mode
		virtual ~Xbox360File();
		
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
		bool		mDeleteBuffer;
		uint8*		mBuffer;
		uint32		mBufferSize;
		uint32		mSize;
		bool		mIsLoaded;
		bool		mHasError;

		bool		mIsDirect;
		uint64		mReadSize;


		HANDLE		mHandle;
		OVERLAPPED	mOverlapped;

		uint32		mReadPos;
	};

	class Xbox360FileSearch : public IFileSearch
	{
	public:
		HANDLE mSearchHandle;

		Xbox360FileSearch(HANDLE searchHandle) { mSearchHandle = searchHandle; mSearchType = DRIVER_INTERNAL; }
		
	
	};
	
	class Xbox360FileDriver : public IFileDriver
	{
	public:
		Xbox360FileDriver();
		
		virtual ~Xbox360FileDriver();

		virtual std::string		FixPath(const std::string& thePath);
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		virtual void InitSaveDataFolder(void);
		virtual std::string		GetSaveDataPath() override;
		
		virtual std::string		GetCurPath() override;

		virtual std::string		GetLoadDataPath() override;
				
		virtual IFile*			CreateFile(const std::string& path) override;

		virtual IFile*			CreateFileDirect(const std::string& thePath) override;

		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;

		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																WIN32_FILE_ATTRIBUTE_DATA* attrData, bool delete_buffer);
		
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

