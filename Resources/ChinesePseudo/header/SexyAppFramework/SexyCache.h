#ifndef __SEXYCACHE_H__
#define __SEXYCACHE_H__

#include "Common.h"
#include "CritSect.h"

namespace Sexy
{

#ifdef SUPPORT_SEXY_CACHE
struct SexyCacheData
{
	int						mVersion;
	HWND					mHWnd;	
	int						mCachedItemCount;
	int						mCacheSize;
};

struct SexyDataHeader
{
	char					mSrcFile[256];
	char					mDataType[512];
	int						mSize;
};

enum
{
	SEXYCACHE_GETDATA,
	SEXYCACHE_SETDATA,
	SEXYCACHE_SETFILEDEPS,
	SEXYCACHE_CHECKFILECHANGES,
	SEXYCACHE_SET_UP_TO_DATE
};

typedef std::map<void*, HANDLE> PtrToHandleMap;

class SexyCache
{
public:
	CritSect				mCritSect;
	SexyCacheData			mSexyCacheData;
	UINT					mSexyCacheMessage;	
	PtrToHandleMap			mAllocDataMap;

public:
	SexyCache();

	bool					Connected();
	void					Disconnect();
	bool					HadCachedObjects();
	void					CheckFileChanges();

	bool					CheckData(const std::string& theSrcFile, const std::string& theDataType);
	bool					SetUpToDate(const std::string& theSrcFile, const std::string& theDataType);
	bool					GetData(const std::string& theSrcFile, const std::string& theDataType, void** thePtr, int* theSize);
	void					FreeGetData(void* theGetDataPtr);
	void					SetFileDeps(const std::string& theSrcFile, const std::string& theDataType, const std::string& theFileDeps);

	void*					AllocSetData(const std::string& theSrcFile, const std::string& theDataType, int theSize);
	void					FreeSetData(void* theSetDataPtr);
	bool					SetData(void* theSetDataPtr);
};

#else

class SexyCache
{
public:
public:
	SexyCache() {};

	bool					Connected() { return false; };
	void					Disconnect() {};
	bool					HadCachedObjects() { return false; };
	void					CheckFileChanges() {} ;

	bool					CheckData(const std::string& theSrcFile, const std::string& theDataType) { return false; };
	bool					SetUpToDate(const std::string& theSrcFile, const std::string& theDataType) { return false; };
	bool					GetData(const std::string& theSrcFile, const std::string& theDataType, void** thePtr, int* theSize) { return false; };
	void					FreeGetData(void* theGetDataPtr) {};
	void					SetFileDeps(const std::string& theSrcFile, const std::string& theDataType, const std::string& theFileDeps) {};

	void*					AllocSetData(const std::string& theSrcFile, const std::string& theDataType, int theSize) { return NULL; };
	void					FreeSetData(void* theSetDataPtr) {};
	bool					SetData(void* theSetDataPtr) { return false; };
};


#endif

void SMemW(void** theDest, const void* theSrc, int theSize);
void SMemWStr(void** theDest, const std::string& theStr);
void SMemR(void** theSrc, void* theDest, int theSize);
void SMemRStr(void** theDest, std::string* theStr);



extern SexyCache gSexyCache;

}

#endif //__SEXYCACHE_H__
