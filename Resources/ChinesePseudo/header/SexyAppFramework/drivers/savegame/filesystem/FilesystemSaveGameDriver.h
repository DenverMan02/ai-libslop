#ifndef FILESYSTEMSAVEGAMEDRIVER_H_INCLUDED
#define FILESYSTEMSAVEGAMEDRIVER_H_INCLUDED

#include "ISaveGameDriver.h"
#include "Buffer.h"

namespace Sexy
{
	class FilesystemSaveGameDriver : public ISaveGameDriver
	{
	public:
		FilesystemSaveGameDriver();

		bool Init();
		virtual void Update();

		//create a context for a save game operation
		ISaveGameContext *CreateSaveGameContext( UserProfile *player, const std::string &filename, uint64 requiredBytes = 0 );

		//start a load or save operation
		virtual bool BeginLoad( ISaveGameContext *context, const std::string &segment, bool checkOnly = true );
		virtual bool BeginSave( ISaveGameContext *context, const std::string &segment, const Buffer &b );
		virtual bool BeginDelete( ISaveGameContext *context, const std::string &segment );
		virtual bool BeginSaveGameDelete( ISaveGameContext *context );
	};

	class FilesystemSaveGameContext : public ISaveGameContext
	{
	public:
		FilesystemSaveGameContext( UserProfile *player, const std::string &filename );

		virtual UserProfile *GetPlayer(){ return mPlayer;};
		virtual const std::string &GetSaveName(){return mSaveName;};
		virtual const std::string &GetSegmentName(){return mSegmentName;};

		virtual void Update(){};

		virtual bool IsLoading(){return false;};
		virtual bool IsSaving(){return false;};
		virtual bool IsDeleting(){return false;};

		virtual bool HasError(){return mError;};
		virtual bool IsDone(){return !mError && mDone;};

		virtual const Buffer &GetBuffer(){ return mBuffer; };

		//None of these meta-data functions are currently implemented.
		virtual void SetDisplayName(const SexyString &name){};
		virtual const SexyString &GetDisplayName(){ return mEmptySexyString; };

		virtual void SetDisplayDetails(const SexyString &name){};
		virtual const SexyString &GetDisplayDetails(){ return mEmptySexyString; };

		virtual void SetIconFilename( const std::string &icon ){};
		virtual const std::string &GetIconFilename(){ return mEmptyString; };

		virtual void Destroy();
	private:
		friend class FilesystemSaveGameDriver;
		static std::string mEmptyString;
		static SexyString mEmptySexyString;

		bool mDone;
		bool mError;

		UserProfile *mPlayer;
		std::string mSaveName;
		std::string mSegmentName;
		
		Buffer mBuffer;
	};
};

#endif
