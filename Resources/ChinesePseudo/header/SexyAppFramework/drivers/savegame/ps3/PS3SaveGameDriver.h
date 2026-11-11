#ifndef PS3SAVEGAMEDRIVER_H_INCLUDED
#define PS3SAVEGAMEDRIVER_H_INCLUDED

#include "ISaveGameDriver.h"
#include "IFileDriver.h"

#include "SexyThread.h"
#include "Buffer.h"

#include <sysutil/sysutil_savedata.h>

#include <vector>

namespace Sexy
{
	class PS3SaveGameContext;
	class PS3AppDriver;

	class PS3SaveGameDriver : public ISaveGameDriver
	{
		enum IOState
		{
			STATE_ERROR = -1,
			STATE_IDLE,
		};
	public:
		PS3SaveGameDriver();
		~PS3SaveGameDriver();

		bool Init();
		void Update();

		//create a context for a save game operation
		ISaveGameContext *CreateSaveGameContext( UserProfile *player, const std::string &saveName, uint64 requiredBytes = 0 );

		//start a load or save operation
		virtual bool BeginLoad( ISaveGameContext *context, const std::string &segment, bool checkOnly = false );
		virtual bool BeginSave( ISaveGameContext *context, const std::string &segment, const Buffer &data );
		virtual bool BeginDelete( ISaveGameContext *context, const std::string &segment );
		virtual bool BeginSaveGameDelete( ISaveGameContext *context );


		void SetDefaultIconFilename( const std::string& png ){ mDefaultIconFilename = png; }
	protected:
		friend class PS3SaveGameContext;
		static std::string FixSaveName(const std::string &saveName);
		void ReleaseContext( PS3SaveGameContext *context );
	private:
		IOState mState;

		PS3AppDriver* mAppDriver;

		std::string mDefaultIconFilename;

		typedef std::vector<ISaveGameContext*> ContextList;
		ContextList mContexts;
	};

	class PS3SaveGameContext : public ISaveGameContext
	{
		enum IOState
		{
			STATE_ERROR_CORRUPT = -2,
			STATE_ERROR = -1,
			STATE_IDLE,
			STATE_LOADING,
			STATE_SAVING,
			STATE_DELETING_SEGMENT,
			STATE_DELETING_SAVEGAME,
			STATE_ERROR_RETRY,
			STATE_ERROR_RETRY_CORRUPT,
			STATE_DIALOG,
			_NUM_STATES
		};

		enum SaveMode
		{
			SAVE_MODE_AUTO,
			SAVE_MODE_FIXED,
			SAVE_MODE_LIST
		};

		enum FileState
		{
			FILE_STATE_INIT,
			FILE_STATE_ICON,
			FILE_STATE_PROFILE,
			FILE_STATE_GAME_DATA_START = FILE_STATE_PROFILE,
			FILE_STATE_SEGMENT,
			FILE_STATE_DONE
		};
	public:
		PS3SaveGameContext( UserProfile *player, const std::string &saveName );
		~PS3SaveGameContext();

		UserProfile *GetPlayer(){ return mPlayer; };
		const std::string &GetSaveName(){ return mSaveName; };
		const std::string &GetSegmentName(){ return mSegmentName; };

		virtual void Update();

		virtual bool IsLoading(){ return mState == STATE_LOADING; };
		virtual bool IsSaving(){ return mState == STATE_SAVING; };
		virtual bool IsDeleting(){ return mState == STATE_DELETING_SAVEGAME || mState == STATE_DELETING_SEGMENT; };

		virtual bool HasError(){ return mState < 0; };
		virtual bool IsDone(){ return mState == STATE_IDLE; };
		virtual bool IsCorrupt(){ return mState == STATE_ERROR_CORRUPT; };

		virtual void SetDisplayName(const SexyString &name){ mDisplayName = name; };
		virtual const SexyString &GetDisplayName(){ return mDisplayName; };

		virtual void SetDisplaySubTitle(const SexyString &subtitle){ mDisplaySubTitle = subtitle; };
		virtual const SexyString &GetDisplaySubTitle(){ return mDisplaySubTitle; };

		virtual void SetDisplayDetails(const SexyString &details){ mDisplayDetails = details; };
		virtual const SexyString &GetDisplayDetails(){ return mDisplayDetails; };

		virtual void SetIconFilename( const std::string &icon ){ mIconFilename = icon; };
		virtual const std::string &GetIconFilename(){ return mIconFilename; };

		virtual void SetEmbedProfileSave( bool saveProfile ){ mSaveProfile = saveProfile; };
		virtual bool GetEmbedProfileSave(){ return mSaveProfile; };

		virtual const Buffer &GetBuffer(){ return mBuffer; };

		virtual void Destroy();
	public:
		static void SaveGameThreadProc( void *param );

		static void DataSaveFixedCallback( CellSaveDataCBResult *cbResult, CellSaveDataListGet *get, CellSaveDataFixedSet *set );
		static void DataLoadFixedCallback( CellSaveDataCBResult *cbResult, CellSaveDataListGet *get, CellSaveDataFixedSet *set );

		static void DataSaveStatCallback( CellSaveDataCBResult *cbResult, CellSaveDataStatGet *get, CellSaveDataStatSet *set );
		static void DataLoadStatCallback( CellSaveDataCBResult *cbResult, CellSaveDataStatGet *get, CellSaveDataStatSet *set );
		static void DataSaveFileCallback( CellSaveDataCBResult *cbResult, CellSaveDataFileGet *get, CellSaveDataFileSet *set );
		static void DataLoadFileCallback( CellSaveDataCBResult *cbResult, CellSaveDataFileGet *get, CellSaveDataFileSet *set );

		static void DataSaveDoneCallback( CellSaveDataCBResult *cbResult, CellSaveDataDoneGet *get );
	protected:
		void Init();

		bool StartLoading();
		bool StartSaving();
		bool StartDeleteSegment();
		bool StartDelete();

	private:
		friend class PS3SaveGameDriver;
		friend class PS3ProfileData;

		PS3SaveGameDriver* mDriver;

		bool mIsNewData;
		bool mSegmentNotFound;
		bool mIsNotOwner;

		//true if abandoned by owner (in case of shutdown, etc)
		bool mZombie;

		IOState mState;
		IOState mPrevState;
		SaveMode mSaveMode;
		FileState mFileState;

		UserProfile *mPlayer;
		std::string mSaveName;
		std::string mSegmentName;

		SexyString	mDisplayName;
		SexyString	mDisplaySubTitle;
		SexyString	mDisplayDetails;

		std::string mIconFilename;

		bool mSaveProfile;

		Buffer mBuffer;
		Buffer mProfileBuffer;
		Buffer mIconBuffer;

		SexyThreadId mThreadId;
	};
};

#endif
