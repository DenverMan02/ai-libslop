#ifndef ISAVEGAMEDRIVER_H_INCLUDED
#define ISAVEGAMEDRIVER_H_INCLUDED

#include "Common.h"

namespace Sexy
{
	class Buffer;
	class UserProfile;
	class MemoryImage;

	class ISaveGameContext;

	//
	// The save game driver allows for cross platform save game management.
	// Supports reading, writing, and deleting of savegame data.
	//
	// On some platforms it also handles storage device selection, or other 
	//  integration with platform specific save game UIs.
	//
	// Each save game can have a number of 'segments'.  Each segment can be 
	//  read/written without impacting the other segments in the save game.
	//
	class ISaveGameDriver
	{
	public:
		static ISaveGameDriver *CreateSaveGameDriver();

		virtual ~ISaveGameDriver() {};

		virtual bool Init() = 0;
		virtual void Update() = 0;

		//create a context for a save game operation.  
		virtual ISaveGameContext *CreateSaveGameContext( UserProfile *player, const std::string &saveName, uint64 requiredBytes = 0 ) = 0;

		//start a load,save or delete operation.  Returns true if the operation was started successfully.  The operation is not complete until
		// one of the context IsDone() or HasError() functions return true.
		virtual bool BeginLoad( ISaveGameContext *context, const std::string &segment, bool checkOnly = true ) = 0;
		virtual bool BeginSave( ISaveGameContext *context, const std::string &segment, const Buffer &data ) = 0;
		virtual bool BeginDelete( ISaveGameContext *context, const std::string &segment ) = 0;
		virtual bool BeginSaveGameDelete( ISaveGameContext *context ) = 0;
	};

	//
	// A context for savegame read/write/delete operations.
	// Create a context using ISaveGameDriver::CreateSaveGameContext and 
	// then start an operation using one of BeginSaveGameRead, BeginSaveGameWrite, or BeginSaveGameDelete
	//
	class ISaveGameContext
	{
	public:
		virtual ~ISaveGameContext() {}
		//The required context fields for the savegame operation.
		virtual UserProfile *GetPlayer() = 0;
		virtual const std::string &GetSaveName() = 0;
		virtual const std::string &GetSegmentName() = 0;

		//Status and Async IO polling functions
		virtual bool IsLoading() = 0;
		virtual bool IsSaving() = 0; 
		virtual bool IsDeleting() = 0;

		virtual void Update() = 0;
		virtual bool HasError() = 0;
		virtual bool IsDone() = 0;

		//get the buffer being used for reads/writes
		virtual const Buffer &GetBuffer() = 0;

		//Additional non-required fields for reading/writing operations.
		// You can set additional meta data after the context is created, and
		// before the operation is started.  It is invalid to 'Set' the below
		// fields once a read/write/delete operation has started.
		virtual void SetDisplayName(const SexyString &name) = 0;
		virtual const SexyString &GetDisplayName() = 0;

		virtual void SetDisplayDetails(const SexyString &name) = 0;
		virtual const SexyString &GetDisplayDetails() = 0;

		virtual void SetIconFilename( const std::string &iconFile ) = 0;
		virtual const std::string &GetIconFilename() = 0;

		// When you are done using a context, call Destroy() to clean it up.
		// this will delete the object, so don't access it after calling Destroy()
		virtual void Destroy() = 0;
	};
};

#endif
