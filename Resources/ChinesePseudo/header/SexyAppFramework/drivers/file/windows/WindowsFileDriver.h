#pragma once
#ifndef WINDOWSFILEDRIVER_H_INCLUDED
#define WINDOWSFILEDRIVER_H_INCLUDED


#include "IFileDriver.h"

namespace Sexy 
{
	class WindowsFile : public IFile
	{
	public:
		WindowsFile(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer);
		WindowsFile(const std::string& filename); //direct mode
		virtual ~WindowsFile();
		
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
		uint32		mTotalReadSize; 
		uint32		mSize;
		bool		mIsLoaded;
		bool		mHasError;

		bool		mIsDirect;
		uint64		mReadSize;


		HANDLE		mHandle;
		OVERLAPPED	mOverlapped;

		uint32		mReadPos;

	};


	class WindowsMMapFile : public IFile
	{
	public:
		WindowsMMapFile(const std::string& theFilename, bool isDirect);

		virtual ~WindowsMMapFile();
		
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
		uint8*		mBuffer;
		uint32		mBufferSize;
		bool		mIsLoaded;
		bool		mHasError;

		bool		mIsDirect;
		uint64		mReadSize;


		HANDLE		mHandle;
		HANDLE		mMapping;
		uint32		mReadPos;
	};

	class WindowsFileSearch : public IFileSearch
	{
	public:
		HANDLE mSearchHandle;

		WindowsFileSearch(HANDLE searchHandle) { mSearchHandle = searchHandle; }
		virtual ~WindowsFileSearch() {};
	
	};
	
	class WindowsFileDriver : public IFileDriver
	{
	public:
		WindowsFileDriver();
		
		virtual ~WindowsFileDriver();
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;

		virtual void			InitSaveDataFolder() override;
		
		virtual std::string		FixPath(const std::string& inFileName) override;

		virtual std::string		GetSaveDataPath() override;

		virtual std::string		GetSysFontPath() override;	//PVZ2_CHINESE
		
		virtual std::string		GetCacheDataPath() override;
		//PVZ2_CHINESE_BEGIN
		virtual std::string		GetDataPath( PathType inPathType ) override {return "";}
		virtual std::string		GetDataPathSaveData() override{return "";}
		virtual std::string		GetDataPathLoadData() override{return "";}
        virtual std::string		GetDataPathCacheData() override{return "";}
        virtual std::string		GetDataPathSupportDataNoBackup() override{return "";}
        virtual std::string		GetDataPathSupportDataBackup() override{return "";}
        virtual bool            IsDataPathValid( const std::string& inPath ) override{return false;}
		//PVZ2_CHINESE_END

		virtual std::string		GetCurPath() override;

		virtual void			SetLoadDataPath(const std::string& path);
		virtual std::string		GetLoadDataPath() override;
				
		virtual IFile*			CreateFile(const std::string& path) override;

		virtual IFile*			CreateFileDirect(const std::string& path) override;

		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;

		virtual IFile*			CreateFileWithBufferAndAttrData(const std::string& path, uint8* buffer, uint32 buffer_size, 
																WIN32_FILE_ATTRIBUTE_DATA* attrData, bool delete_buffer);

		virtual bool			SupportsMemoryMappedFiles() { return true; }

		virtual IFile*			CreateFileMemoryMapped(const std::string& thePath);
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual FileTime		GetFileTime(const std::string& path) override;

		//PVZ2_CHINESE_BEGIN
		virtual FileTime		GetFileCreateTime(const std::string& thePath) override;
		virtual std::string		GetFileCreateTimeReadable(const std::string& thePath) override;
		virtual FileTime		GetFileLastAccessTime(const std::string& thePath) override;
		virtual std::string		GetFileLastAccessTimeReadable(const std::string& thePath) override;
		virtual std::string		GetFileTimeReadable(const std::string& thePath) override;
		virtual FileTime		GetFileBirthTime(const std::string& thePath) override;
		virtual std::string		GetFileBirthTimeReadable(const std::string& thePath) override;
		//PVZ2_CHINESE_END
		
		virtual bool			FileExists(const std::string& path, bool* isFolder=NULL) override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
	
		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;

		virtual bool            GetVolumeStatistics(const std::string &pathOnVolume, VolumeStatistics *stats) override; //PVZ2_CHINESE CJD_RSG3
	private:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
		std::string mLoadDataFolder;
	};
}


#endif

