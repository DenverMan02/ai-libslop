#ifndef NULLSAVEGAMEDRIVER_H_INCLUDED
#define NULLSAVEGAMEDRIVER_H_INCLUDED

#include "ISaveGameDriver.h"

#include "Buffer.h"

namespace Sexy
{
	class NullSaveGameDriver : public ISaveGameDriver
	{
	public:
		NullSaveGameDriver();

		bool Init();
		virtual void Update(){};

		//create a context for a save game operation
		ISaveGameContext *CreateSaveGameContext( UserProfile *player, const std::string &filename, uint64 requiredBytes = 0 );

		//start a load or save operation
		virtual bool BeginLoad( ISaveGameContext *context, const std::string &segment, bool checkOnly = true){ return false; };
		virtual bool BeginSave( ISaveGameContext *context, const std::string &segment, const Buffer &b ){ return false; };
		virtual bool BeginDelete( ISaveGameContext *context, const std::string &segment ){ return false; };
		virtual bool BeginSaveGameDelete( ISaveGameContext *context ){ return false; };
	};

	class NullSaveGameContext : public ISaveGameContext
	{
	public:
		NullSaveGameContext( UserProfile *player, const std::string &filename );

		virtual UserProfile *GetPlayer(){ return NULL;};
		virtual const std::string &GetSaveName(){return mDummyString;};
		virtual const std::string &GetSegmentName(){return mDummyString;};

		virtual void Update(){};

		virtual bool IsLoading(){ return false; };
		virtual bool IsSaving(){ return false; };
		virtual bool IsDeleting(){ return false; };

		virtual bool HasError(){ return false; };
		virtual bool IsDone(){ return true; };

		virtual void SetDisplayName(const SexyString &name){ };
		virtual const SexyString &GetDisplayName(){ return mSexyString; };

		virtual void SetDisplayDetails(const SexyString &name){};
		virtual const SexyString &GetDisplayDetails(){ return mSexyString; };

		virtual void SetIconFilename( const std::string &icon ){ };
		virtual const std::string &GetIconFilename(){ return mDummyString; };

		virtual const Buffer &GetBuffer(){ return mBuffer; };

		virtual void Destroy();
	private:
		std::string mDummyString;
		SexyString mSexyString;
		Buffer mBuffer;
	};
};

#endif
