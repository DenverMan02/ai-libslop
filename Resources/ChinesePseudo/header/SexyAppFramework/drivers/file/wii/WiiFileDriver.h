#pragma once
#ifndef WIIFILEDRIVER_H_INCLUDED
#define WIIFILEDRIVER_H_INCLUDED

#include "Common.h"

#include "IFileDriver.h"

namespace Sexy
{
/*
 * Wii filesystem info as I learn it...
 *
 * The Wii console has a number of different file APIs for accessing data on 
 *	a number of different media types.  Unfortunately there doesn't seem to be
 * 	any unified way to access the different media, so this will be more 
 *	interesting than on the other platforms.  As possible I will try to route
 *  reads/writes to the logical API, but we'll have to have a toggle between 
 *	disc titles and NAND titles.
 *
 * DVD - the main optical drive is accessed with the DVD*() function calls in
 *	the RVL_SDK.
 *
 * CNT - the filthy package format for downloadable titles.  Read only access
 *	to the contents of WAD files. filthy.
 * 
 * NAND - the non-volatile system memory.  Where save games go.  NAND 
 *	applications should still only read game data using CNT.
 *
 * and finally...
 *
 * VF - Add on 'Virtual Filesystem' support found in the RevoEX extensions 
 *	package.  Looks like a filesystem abstraction layer, but it ain't.  We
 *	shouldn't need this since we have our own solution in PAK files.  
 *
 */

	//
	// BaseWiiFile
	//	A base class for Wii file implementations
	//
	class BaseWiiFile : public IFile
	{
	public:		
		virtual bool		HasError() override;
		
		virtual bool		IsLoaded() override;
		virtual bool		ForceLoad() override;
		
		virtual uint32		GetSize() override;
		virtual uint8*		GetBuffer() override;

	protected:
		//auto load & direct
		BaseWiiFile(const std::string& filename,bool direct);
		//external buffer
		BaseWiiFile(const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer);

		virtual ~BaseWiiFile();

		bool		mDeleteBuffer;
		uint8*		mBuffer;
		s32 		mBufferSize;
		s32 		mSize;
		bool		mIsLoaded;
		bool		mHasError;

		bool		mIsDirect;
		uint64		mReadSize;

		uint32		mReadPos;
	};

	//
	// WiiDVDFile
	//	File implementation for reading from the optical disc
	//
	class WiiDVDFile : public BaseWiiFile
	{		
		public:
			virtual void		AsyncLoad() override;

			virtual void		Close()	override;

			virtual void		DirectSeek(uint64 theSeekPoint) override;
			virtual bool		DirectRead(uint8* theBuffer, uint64 theReadSize) override;
			virtual Status		DirectReadStatus() override;
			virtual uint64		DirectReadBlockSize() override;

		protected:
			WiiDVDFile( const std::string& filename, bool direct );
			WiiDVDFile( const std::string& filename, uint8* buffer, uint32 buffer_size, bool delete_buffer);
			virtual ~WiiDVDFile();

			bool InitRead(const std::string& filename);
			
			friend class WiiDVDFileDriver;
			
		private:
			bool mFileOpen;
			DVDFileInfo mFileInfo;
		
	};
	
	//
	// WiiCNTFile
	//	File implementation for NAND Applications loading resources from a WAD
	class WiiCNTFile : public BaseWiiFile
	{		
	};


	
	//
	// BaseWiiFileDriver
	//
	class BaseWiiFileDriver : public IFileDriver
	{
	public:
		BaseWiiFileDriver();
		virtual ~BaseWiiFileDriver();


		virtual std::string		FixPath(const std::string& thePath);
		
		virtual bool			InitFileDriver(SexyAppBase* app) override;
		virtual void			InitSaveDataFolder() override;
		
		virtual std::string		GetSaveDataPath() override;
		virtual std::string		GetCurPath() override;
		
		virtual bool			MakeFolders(const std::string& folder) override;
		virtual bool			DeleteTree(const std::string& path) override;
		
		virtual bool			DeleteFile(const std::string& path) override;
		
	protected:
		SexyAppBase* mApp;
		std::string mSaveDataFolder;
	};


	//
	// WiiDVDFileSearch
	//
	class WiiDVDFileSearch : public IFileSearch
	{
	public:
		WiiDVDFileSearch(std::string pattern, std::string path,DVDDir &dir);
		
		DVDDir mDir;
		std::string mPattern;
		std::string mPath;
	};
	
	//
	// WiiDVDFileDriver
	//
	class WiiDVDFileDriver : public BaseWiiFileDriver 
	{
		public:
		WiiDVDFileDriver();
		virtual ~WiiDVDFileDriver();

		virtual bool			InitFileDriver(SexyAppBase* app) override;

		virtual std::string		GetLoadDataPath() override;
				
		virtual IFile*			CreateFile(const std::string& path) override;

		virtual IFile*			CreateFileDirect(const std::string& thePath) override;

		virtual IFile*			CreateFileWithBuffer(const std::string& path, uint8* buffer, uint32 buffer_size) override;
		
		virtual uint64			GetFileSize(const std::string& path) override;
		
		virtual FileTime		GetFileTime(const std::string& path) override;
		
		virtual bool			FileExists(const std::string& path, bool* isFolder=NULL) override;

		virtual IFileSearch*	FileSearchStart(const std::string& criteria, FileSearchInfo*) override;
		virtual bool			FileSearchNext(IFileSearch*, FileSearchInfo*) override;
		virtual bool			FileSearchEnd(IFileSearch*) override;
		
	};

	class WiiCNTFileDriver : public BaseWiiFileDriver
	{
		WiiCNTFileDriver();
		virtual ~WiiCNTFileDriver();
		
	};
}

#endif
