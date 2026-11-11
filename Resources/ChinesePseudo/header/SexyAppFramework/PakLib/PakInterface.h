#ifndef __PAKINTERFACE_H__
#define __PAKINTERFACE_H__

#include "Common.h"
#include "Debug.h"
#include "IFileDriver.h"

namespace Sexy 
{
	extern IFileDriver* gFileDriver;
}

#include <map>
#include <list>
#include <string>
#include <vector>


class PakCollection;

enum
{
	PSEARCH_PAK_THEN_FILES,
	PSEARCH_FILES_THEN_PAK,
	PSEARCH_JUST_PAK,
	PSEARCH_JUST_FILES
};

class PakRecord
{
public:
	PakCollection*			mCollection;
	std::string				mFileName;
	Sexy::FileTime			mFileTime;
	int						mStartPos;
	int						mSize;
};

//The PakFileTime looks exactly like the windows filetime (b/c that's what
// the Pak format embeds)
struct PakFileTime 
{
	uint32 LowDateTime;
    uint32 HighDateTime;
};

Sexy::FileTime ConvertPakFileTimeToSexyFileTime(PakFileTime& ft);
PakFileTime ConvertSexyFileTimeToPakFileTime(Sexy::FileTime& ft);


typedef std::map<std::string, PakRecord> PakRecordMap;
typedef std::vector<PakRecord*> PakRecordPtrList;

class PakFileDesc
{
public:
	std::string filename;
	uint8* buffer;
	uint32 size;
	uint32 actual_size;

	Sexy::IFile* f;
};

class PakCollection
{
public:
//  JVW - maybe windows/mac prime will support MMAP pak files, 
//    but this will likely be through the FileDriver interface.
//  
	Sexy::IFile*			mFile;
	void*					mDataPtr;

};
typedef std::list<PakCollection> PakCollectionList;

struct PFILE
{
	PakRecord*				mRecord;
	int						mPos;
	Sexy::IFile*			mFile;
	uint8*					mBuffer;
	uint32					mSize;
	uint32					mPointer;
	bool					mBufferOwner;
};




class PakInterfaceBase
{
public:
	virtual ~PakInterfaceBase() {}
	virtual void				Cleanup() = 0;
	virtual PFILE*				FOpen(const char* theFileName, const char* theAccess, int theSearchOrder = -1) = 0;
	virtual PFILE*				FOpen(const wchar_t* theFileName, const wchar_t* theAccess, int theSearchOrder = -1) = 0;
	virtual int					FClose(PFILE* theFile) = 0;
	virtual int					FSeek(PFILE* theFile, long theOffset, int theOrigin) = 0;
	virtual int					FTell(PFILE* theFile) = 0;
	virtual size_t				FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile) = 0;
	virtual size_t				DecryptFRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile) = 0;
	virtual int					FGetC(PFILE* theFile) = 0;
	virtual int					UnGetC(int theChar, PFILE* theFile) = 0;
	virtual char*				FGetS(char* thePtr, int theSize, PFILE* theFile) = 0;
	virtual wchar_t*			FGetS(wchar_t* thePtr, int theSize, PFILE* theFile) { return thePtr; }
	virtual int					FEof(PFILE* theFile) = 0;

	virtual Sexy::IFileSearch*	FindFirstFile(const char* theFileName, Sexy::FileSearchInfo* findFileData) = 0;	
	virtual bool				FindNextFile(Sexy::IFileSearch* fileSearch, Sexy::FileSearchInfo* findFileData) = 0;
	virtual bool				FindClose(Sexy::IFileSearch* fileSearch) = 0;

	virtual int					SetFileSearchOrder(int theOrder) = 0;
	virtual int					GetFileSearchOrder() = 0;
	
	virtual bool				GetFileTime(Sexy::FileTime& outFileTime, const char* theFileName, int theSearchOrder = -1) = 0;
	//virtual bool				GetFileTime(Sexy::FileTime& outFileTime, const wchar_t* theFileName, int theSearchOrder = -1) = 0;

	/**
	 * The Pak Passcode is the byte that the contents get xor'd with to prevent casual data-snooping.
	 * This has to be the same as the passcode used when generating the pak.
	 * A passcode of 0 (no xoring) allows for certain optimizations.
	 */
	virtual void				SetPassCode(uint8 thePassCode) = 0;
};

class PakInterface : public PakInterfaceBase
{
public:
	PakCollectionList		mPakCollectionList;	
	PakRecordMap			mPakRecordMap;
	int						mSearchOrder;
	uint8					mPassCode;
	bool					mIsMMapped;

protected:
	bool					PFindNext(Sexy::IFileSearch* theFindData, Sexy::FileSearchInfo* findFileData);

public:
	PFILE*					FOpen_Pak(const char* theFileName, const char* theAccess);
	static PFILE*			FOpen_File(const char* theFileName, const char* theAccess);
	static PFILE*			FOpen_File(const wchar_t* theFileName, const wchar_t* theAccess);

	bool					FGetBuffer_Pak(const char* theFileName, uint8** theOutBuffer, uint32* theOutSize, PFILE** theOutFile);
	static bool				FGetBuffer_File(const char* theFileName, uint8** theOutBuffer, uint32* theOutSize, PFILE** theOutFile);
	
	bool					GetFileTime_Pak(Sexy::FileTime& outFileTime, const char* theFileName);
	static bool				GetFileTime_File(Sexy::FileTime& outFileTime, const char* theFileName);

public:
	PakInterface();
	~PakInterface();

	void					Cleanup();


	bool					PreparePakFile(const std::string& theFileName, PakFileDesc& out);
	bool					IsPakFileLoaded(PakFileDesc&);
	bool					HasPakFileFailed(PakFileDesc&);

	//do this after a load, or a failure to close off the file handle
	bool					ClosePakFile(PakFileDesc&);


	bool					AddPakFile(const std::string& theFileName);
	bool					AddPakFile(PakFileDesc&);
	bool					RemovePakFile(PakFileDesc&);

	PFILE*					FOpen(const char* theFileName, const char* theAccess, int theSearchOrder = -1);
	PFILE*					FOpen(const wchar_t* theFileName, const wchar_t* theAccess, int theSearchOrder = -1) { return NULL; }
	int						FClose(PFILE* theFile);
	int						FSeek(PFILE* theFile, long theOffset, int theOrigin);
	int						FTell(PFILE* theFile);
	size_t					FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile);
	size_t					DecryptFRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile);
	int						FGetC(PFILE* theFile);
	int						UnGetC(int theChar, PFILE* theFile);
	char*					FGetS(char* thePtr, int theSize, PFILE* theFile);
	int						FEof(PFILE* theFile);

	bool					FGetBuffer(const char* theFileName, uint8** theOutBuffer, uint32* theOutSize, PFILE** theOutFile, int theSearchOrder = -1);

	Sexy::IFileSearch*		FindFirstFile(const char* theFileName, Sexy::FileSearchInfo* findFileData);	
	bool					FindNextFile(Sexy::IFileSearch* fileSearch, Sexy::FileSearchInfo* findFileData);
	bool					FindClose(Sexy::IFileSearch* fileSearch);
	
	virtual int				SetFileSearchOrder(int theOrder);
	virtual int				GetFileSearchOrder();
	
	bool					GetFileTime(Sexy::FileTime& outFileTime, const char* theFileName, int theSearchOrder = -1);
	//bool					GetFileTime(Sexy::FileTime& outFileTime, const wchar_t* theFileName, int theSearchOrder = -1);


	virtual void			SetPassCode(uint8 thePassCode);
};

extern PakInterface* gPakInterface;

//static PakInterfaceBase** gPakInterfaceP = NULL;

static PakInterfaceBase* GetPakPtr()
{
	return gPakInterface;
}

static inline PFILE* p_fopen(const char* theFileName, const char* theAccess, int theSearchOrder = -1) 
{
	DBG_ASSERTE(theAccess!=NULL && theAccess[0]=='r');
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FOpen(theFileName, theAccess,PSEARCH_JUST_PAK);	
	return NULL;
#else	
	if (GetPakPtr() != NULL)
		return gPakInterface->FOpen(theFileName, theAccess,theSearchOrder);	
	
	return PakInterface::FOpen_File(theFileName, theAccess);
#endif
}

static inline bool p_fgetbuffer(const char* theFileName,uint8** theOutBuffer, uint32* theOutSize, PFILE** theOutFile, int theSearchOrder = -1)
{
	if (theOutFile != NULL)
		*theOutFile = NULL;

#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FGetBuffer(theFileName,theOutBuffer,theOutSize,theOutFile, PSEARCH_JUST_PAK);
#else
	if (GetPakPtr() != NULL)
		return gPakInterface->FGetBuffer(theFileName,theOutBuffer,theOutSize,theOutFile, theSearchOrder);
	
	return PakInterface::FGetBuffer_File(theFileName,theOutBuffer,theOutSize,theOutFile);
#endif


	
}

static inline bool p_filetime(Sexy::FileTime& outFileTime, const char* theFileName, int theSearchOrder = -1)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->GetFileTime(outFileTime, theFileName, PSEARCH_JUST_PAK);
#else
	if (GetPakPtr() != NULL)
		return gPakInterface->GetFileTime(outFileTime, theFileName, theSearchOrder);
	
	return PakInterface::GetFileTime_File(outFileTime,theFileName);
#endif
	
	
	
}


static inline PFILE* p_fopen(const wchar_t* theFileName, const wchar_t* theAccess, int theSearchOrder = -1) 
{
	DBG_ASSERTE(theAccess!=NULL && theAccess[0]=='r');
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FOpen(theFileName, theAccess,PSEARCH_JUST_PAK);	
	return NULL;
#else	
	if (GetPakPtr() != NULL)
		return gPakInterface->FOpen((const wchar_t*)theFileName, theAccess, theSearchOrder);	
	
	return PakInterface::FOpen_File(theFileName, theAccess);
#endif
}

static inline int p_fclose(PFILE* theFile)
{
	if (theFile==NULL) return 0;
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FClose(theFile);
	bool success=true;
	delete theFile;
	return success?0:EOF;
#else	
	if (theFile->mRecord==NULL && theFile->mFile!=NULL)
	{
		//allocated as a loose file not from a pak
		//_aligned_free(theFile->mBuffer);
		
		delete theFile->mFile;
		
	}
	
	if (theFile->mBufferOwner)
	{
		delete theFile->mBuffer;
	}

	delete theFile;

	
	return 0;
	//if( CloseHandle( theFile->mHandle ) )
	//{
	//	delete theFile;
	//	return 0;
	//}
	//if( GetPakPtr() != NULL )
	//	return gPakInterface->FClose(theFile);

	//return EOF;
#endif
}

static inline int p_fseek(PFILE* theFile, long theOffset, int theOrigin)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FSeek(theFile, theOffset, theOrigin);
	return 0;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->FSeek(theFile, theOffset, theOrigin);
	
	switch (theOrigin)
	{
	case SEEK_CUR:
		theFile->mPointer += theOffset;
		break;
	case SEEK_END:
		theFile->mPointer = static_cast<uint32>(theFile->mSize + theOffset);
		break;
	case SEEK_SET:
        theFile->mPointer = static_cast<uint32>(theOffset);
		break;
	default:
		DBG_ASSERT(false);
	}

	return theFile->mPointer;
#endif
}

static inline int p_ftell(PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FTell(theFile);
	return 0;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->FTell(theFile);
	
	//_ASSERTE(false);
	return theFile->mPointer; //ftell(theFile->mFP);
#endif
}

static inline size_t p_fread(void* thePtr, int theSize, int theCount, PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FRead(thePtr, theSize, theCount, theFile);
	return 0;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->FRead(thePtr, theSize, theCount, theFile);
	
	uint32 size = theSize * theCount;
	uint32 num_read = theCount;
	if ((theFile->mPointer + size) > theFile->mSize)
	{
		num_read = (theFile->mSize-theFile->mPointer) / theSize;
		size = num_read * theSize;
	}
	memcpy(thePtr,theFile->mBuffer + theFile->mPointer, size);
	theFile->mPointer += size;
	return num_read;

#endif
}

static inline int p_fgetc(PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FGetC(theFile);
	return 0;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->FGetC(theFile);
	
	if (theFile->mPointer >= theFile->mSize) return EOF;
	int c = *(theFile->mBuffer+theFile->mPointer);
	theFile->mPointer++;
	return c;
#endif
}

static inline int p_ungetc(int theChar, PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->UnGetC(theChar, theFile);
	return 0;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->UnGetC(theChar, theFile);

	theFile->mPointer--;
	return theChar;

#endif
}

static inline char* p_fgets(char* thePtr, int theSize, PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FGetS(thePtr, theSize, theFile);
	return NULL;
#else
	if (GetPakPtr() != NULL && theFile->mRecord!=NULL)
		return gPakInterface->FGetS(thePtr, theSize, theFile);
	
	//TODO: Lame implementation?
	for (int i = 0; i < theSize-1; i++)
	{
		if (p_fread(thePtr+i, 1, 1, theFile) != 1)
		{
			thePtr[i] = 0;
			return NULL;
		}
	
		// We're ignoring the \r in \r\n
		if (thePtr[i] == '\r')
			i--;
		else if (thePtr[i] == '\n')
		{
			thePtr[i+1] = 0;
			break;
		}
	}
	
	return thePtr;
#endif
}

static inline wchar_t* p_fgets(wchar_t* thePtr, int theSize, PFILE* theFile)
{
	//if (GetPakPtr() != NULL)
	//	return gPakInterface->FGetS(thePtr, theSize, theFile);

	DBG_ASSERT("Not Implemented"==NULL);
	return NULL;
	//return fgetws(thePtr, theSize, theFile->mFP);
}

static inline int p_feof(PFILE* theFile)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FEof(theFile);
	return 0;
#else
	if ( GetPakPtr() != NULL && theFile->mRecord != NULL )
		return gPakInterface->FEof(theFile);

	return theFile->mPointer >= theFile->mSize;
#endif
}

static inline Sexy::IFileSearch* p_FindFirstFile(const char* theFileName, Sexy::FileSearchInfo* theFindFileData)
{
#ifdef PAK_ONLY
	if (GetPakPtr() != NULL)
		return gPakInterface->FindFirstFile(theFileName, theFindFileData);
	return NULL;
#else
	if (GetPakPtr() != NULL)
	{
		Sexy::IFileSearch* aFileSearch = gPakInterface->FindFirstFile(theFileName, theFindFileData);
		if (aFileSearch != NULL)
			return aFileSearch;
	}
	
	return Sexy::gFileDriver->FileSearchStart(theFileName,theFindFileData);
#endif

}

static inline bool p_FindNextFile(Sexy::IFileSearch* theFileSearch, Sexy::FileSearchInfo* theFindFileData)
{
	if (theFileSearch->GetSearchType() == Sexy::IFileSearch::PAK_FILE_INTERNAL)
	{
		if (GetPakPtr() != NULL)
			return gPakInterface->FindNextFile(theFileSearch, theFindFileData);
		return false; //shouldn't happen
	}
	else
	{
		return Sexy::gFileDriver->FileSearchNext(theFileSearch,theFindFileData);
	}
}

static inline bool p_FindClose(Sexy::IFileSearch* theFileSearch)
{
	if (theFileSearch->GetSearchType() == Sexy::IFileSearch::PAK_FILE_INTERNAL)
	{
		if (GetPakPtr() != NULL)
			return gPakInterface->FindClose(theFileSearch);
		return true;
	}
	else
	{
		Sexy::gFileDriver->FileSearchEnd(theFileSearch);
		return true;
	}
}

static inline int p_SetFileSearchOrder(int theOrder)
{
	if (GetPakPtr() != NULL)	
		return GetPakPtr()->SetFileSearchOrder(theOrder);	
	else
		return PSEARCH_JUST_FILES;
}

static inline int p_GetFileSearchOrder()
{
	if (GetPakPtr() != NULL)
		return gPakInterface->GetFileSearchOrder();
	else
		return PSEARCH_JUST_FILES;
}

#endif //__PAKINTERFACE_H__
