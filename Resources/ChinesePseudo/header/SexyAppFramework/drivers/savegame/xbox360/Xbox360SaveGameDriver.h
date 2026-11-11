#ifndef XBOX360SAVEGAMEDRIVER_H_INCLUDED
#define XBOX360SAVEGAMEDRIVER_H_INCLUDED

#include "ISaveGameDriver.h"

#include "Buffer.h"
#include <vector>

namespace Sexy
{
	class Xbox360AppDriver;
	class Xbox360SaveGameContext;

	class Xbox360SaveGameDriver : public ISaveGameDriver
	{
		enum IOState
		{
			STATE_ERROR = -1,
			STATE_IDLE,
			STATE_DEVICE_SELECT,
			STATE_DEVICE_SELECT_ERROR,
			STATE_DEVICE_SELECT_WAIT,
			STATE_DEVICE_SELECT_CHECK_SAVEGAME,
			STATE_DEVICE_SELECT_CLOSING_SAVEGAME,
			STATE_DEVICE_SELECT_DIALOG
		};
	public:
		Xbox360SaveGameDriver();

		bool Init();

		void Update();

		//create a context for a save game operation
		ISaveGameContext *CreateSaveGameContext( UserProfile *player, const std::string &filename, uint64 requiredBytes = 0 );

		//enumerate existing savegames
//		virtual ISaveGameIterator *CreateSaveGameIterator( UserProfile *player );

		//start a load or save operation
		virtual bool BeginLoad( ISaveGameContext *context, const std::string &segment, bool checkOnly = false );
		virtual bool BeginSave( ISaveGameContext *context, const std::string &segment, const Buffer &data );
		virtual bool BeginDelete( ISaveGameContext *context, const std::string &segment );
		virtual bool BeginSaveGameDelete( ISaveGameContext *context );


		void ReleaseContext( Xbox360SaveGameContext *context );
//		void ReleaseIterator( Xbox360SaveGameIterator *iter );

		//Xbox specific functions

		bool IsDeviceSelected();
		bool InDeviceSelection();
		bool StartDeviceSelection( UserProfile *p, bool force = false, uint64 bytesRequired = 0 );
		XCONTENTDEVICEID GetDeviceSelection(){ return mDeviceId; };

		void OnStorageDeviceChange();

		void SetSaveGameName( const std::string &name ){ mSaveGameName = name; };

	private:
		friend class Xbox360SaveGameContext;
		friend class Xbox360SaveGameIterator;

		Xbox360AppDriver* mAppDriver;
		IOState mState;

		XOVERLAPPED	mOverlapped;

		UserProfile *mDeviceSelectProfile;
		XCONTENTDEVICEID mDeviceId;

		std::string mSaveGameName;
		XCONTENT_DATA mData;
		bool mDeviceRemoved;
		bool mSelectDeviceOnClose;

		typedef std::vector<ISaveGameContext*> ContextList;
//		typedef std::vector<ISaveGameIterator*> IteratorList;
		ContextList mContexts;
//		IteratorList mIterators;
	};

	class Xbox360SaveGameContext : public ISaveGameContext
	{
		enum IOState
		{
			STATE_ERROR = -1,
			STATE_IDLE,
			STATE_WAITING_FOR_DEVICE,
			STATE_MOUNTING,
			STATE_LOADING,
			STATE_SAVING,
			STATE_CLOSING,
			STATE_DELETING_SAVEGAME,
			STATE_DELETING_SEGMENT,
			STATE_DIALOG,
			STATE_DONE
		};
	public:
		Xbox360SaveGameContext( UserProfile *player, const std::string &filename );

		UserProfile *GetPlayer(){ return mPlayer; };
		const std::string &GetSaveName(){ return mSaveName; };
		const std::string &GetSegmentName(){ return mSegmentName; };

		virtual void Update();

		virtual bool IsLoading(){ return mState == STATE_LOADING; };
		virtual bool IsSaving(){ return mState == STATE_SAVING; };
		virtual bool IsDeleting(){ return mState == STATE_DELETING_SAVEGAME || mState == STATE_DELETING_SEGMENT; };

		virtual bool HasError(){ return mState == STATE_ERROR; };
		virtual bool IsDone(){ return mState == STATE_DONE && !HasError(); };

		virtual void SetDisplayName(const SexyString &name){ mDisplayName = name; };
		virtual const SexyString &GetDisplayName(){ return mDisplayName; };

		virtual void SetDisplayDetails(const SexyString &details){ mDisplayDetails = details; };
		virtual const SexyString &GetDisplayDetails(){ return mDisplayDetails; };

		virtual void SetIconFilename( const std::string &icon ){ mIconFilename = icon; };
		virtual const std::string &GetIconFilename(){ return mIconFilename; };

		virtual const Buffer &GetBuffer(){ return mBuffer; };

		virtual void Destroy();
	protected:
		bool StartContentMount( bool create );
		bool StartContentDelete();
		bool StartSegmentDelete();

		bool StartLoading();
		bool StartSaving();

		bool StartClosing( IOState nextState = STATE_DONE );
	private:
		friend class Xbox360SaveGameDriver;
		Xbox360SaveGameDriver* mSaveGameDriver;
		IOState mState;

		bool mCheckOnly;

		//this is our intended state after initialization/device selection completes.
		IOState mIOOperation;

		UserProfile *mPlayer;
		std::string mSaveName;
		std::string mSegmentName;
		std::string mIconFilename;

		SexyString	mDisplayName;
		SexyString	mDisplayDetails;

		Buffer mBuffer;

		HANDLE mFileHandle;
		OVERLAPPED mFileOverlapped;

		DWORD mContentCreateFlags;

		XCONTENT_DATA mData;
		XOVERLAPPED mOverlapped;
	};

};

#endif
