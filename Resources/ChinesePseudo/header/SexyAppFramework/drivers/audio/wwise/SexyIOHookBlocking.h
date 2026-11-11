//////////////////////////////////////////////////////////////////////
//
// SexyIOHookBlocking.h
//
// Framework implementation of blocking low level IO hook (AK::StreamMgr::IAkIOHookBlocking) 
// and file system (AK::StreamMgr::IAkFileLocationResolver) implementation 
// on OS X.
// 
//
//////////////////////////////////////////////////////////////////////

#ifndef _SEXY_IO_HOOK_BLOCKING_H_
#define _SEXY_IO_HOOK_BLOCKING_H_

#include "Common.h"

#if SEXY_IS_WWISE_ENABLED

#include "POSIX/AkDefaultIOHookBlocking.h"

#include <list>
#include "ResStreamsManager.h"
#include "CritSect.h"

//-----------------------------------------------------------------------------
// Name: class SexyIOHookBlocking.
// Desc: Overides CAkDefaultIOHookBlocking implementation of low-level I/O hook.
//-----------------------------------------------------------------------------
class SexyIOHookBlocking : public CAkDefaultIOHookBlocking
{
public:

	SexyIOHookBlocking();
	virtual ~SexyIOHookBlocking();

	//
	// IAkFileLocationAware interface.
	//-----------------------------------------------------------------------------

	// Returns a file descriptor for a given file name (string).
    virtual AKRESULT Open( 
        const AkOSChar*			in_pszFileName,		// File name.
		AkOpenMode				in_eOpenMode,		// Open mode.
        AkFileSystemFlags *		in_pFlags,			// Special flags. Can pass NULL.
		bool &					io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
        AkFileDesc &			out_fileDesc        // Returned file descriptor.
        );

    // Returns a file descriptor for a given file ID.
    virtual AKRESULT Open( 
        AkFileID				in_fileID,          // File ID.
        AkOpenMode				in_eOpenMode,       // Open mode.
        AkFileSystemFlags *		in_pFlags,			// Special flags. Can pass NULL.
		bool &					io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
        AkFileDesc &			out_fileDesc        // Returned file descriptor.
        );

	//
	// IAkIOHookBlocking interface.
	//-----------------------------------------------------------------------------

	// Reads data from a file (synchronous). 
	virtual AKRESULT Read(
        AkFileDesc &			in_fileDesc,        // File descriptor.
		const AkIoHeuristics &	in_heuristics,		// Heuristics for this data transfer.
        void *					out_pBuffer,        // Buffer to be filled with data.
        AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
        );

    // Writes data to a file (synchronous). 
	virtual AKRESULT Write(
		AkFileDesc &			in_fileDesc,        // File descriptor.
		const AkIoHeuristics &	in_heuristics,		// Heuristics for this data transfer.
        void *					in_pData,           // Data to be written.
        AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
        );

	// Cleans up a file.
    virtual AKRESULT Close(
        AkFileDesc &			in_fileDesc			// File descriptor.
        );

#if defined(HOST_ANDROID)
	AkUInt32            mRSBOffset;
    std::string         mAPKFilename;
    bool				mbDataIsInAPK;
#endif

    std::map<std::string, std::string> mFileIdToPathMap;

private:
	// Returns a file descriptor for a given path name (std::string).
    virtual AKRESULT Open_Aux( 
		std::string				thePathName,		// pATH name.
		AkOpenMode				in_eOpenMode,		// Open mode.
        AkFileSystemFlags *		in_pFlags,			// Special flags. Can pass NULL.
		bool &					io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
        AkFileDesc &			out_fileDesc        // Returned file descriptor.
        );

};

#endif  // SEXY_IS_WWISE_ENABLED

#endif //_SEXY_IO_HOOK_BLOCKING_H_
