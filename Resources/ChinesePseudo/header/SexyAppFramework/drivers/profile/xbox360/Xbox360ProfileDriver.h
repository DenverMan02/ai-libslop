#ifndef XBOX360PROFILEDRIVER_H_INCLUDED
#define XBOX360PROFILEDRIVER_H_INCLUDED

#include "IProfileDriver.h"
#include "IAchievementDriver.h"

#include "DialogListener.h"

//this is how long (frames) we wait after an XN_SYS_SIGNINCHANGED to process the event.
//this works around a number of issues with xam where secondary users appear to 
// temporarily sign-out when a primary user signs in/out
#define SIGNIN_CHANGE_DELAY 100

namespace Sexy
{
	class UserProfile;
	class DeviceImage;
	class Xbox360AppDriver;

	class Xbox360ProfileData : public IProfileData
	{
		enum IOState
		{
			ERROR = -1,
			IDLE,
			LOADING,
			WRITE_TEST,//This is required due to an XDK bug: the game has to attempt to write to the profile to figure out if it's empty or the MU is not inserted
			SAVING,
		};

	public:
		static const int NUM_PLAYERS = 4;
		Xbox360ProfileData( UserProfile *player );

		bool SignedIn(){ return mSigninState != eXUserSigninState_NotSignedIn; };
		bool IsSigningIn(){ return mInitTimer > 0; };
		bool IsOnline(){ return mIsOnline; };

		uint32 GetId();
		const SexyString &GetName();
		
		uint8 GetGamepadIndex() const;
		void SetGamepadIndex(uint8 gamepad);

		EProfileIOState LoadDetails();
		bool IsLoading(){ return mIOState == LOADING; };
		bool IsLoaded(){ return mIsLoaded && !HasError(); };
		
		EProfileIOState SaveDetails();
		bool IsSaving(){ return mIOState == SAVING; };
		bool IsSaved(){ return mIsSaved; };

		bool HasError(){ return mIOState == ERROR; };

		void ClearError() { if( mIOState == ERROR ) mIOState = IDLE; };
		void ForceLoaded(){ mIsLoaded = true; };

		bool ReadSummary(const Buffer &theData);
		bool WriteSummary(Buffer &theData);
		
		void DeleteUserFiles();

		Image *GetPlayerIcon();

		bool IsAchievementUnlocked( AchievementId id );
		IAchievementContext* StartUnlockAchievement( AchievementId id );

		//Xbox specific functions
		XUID GetXuid(){ return mXUID; };

	protected:
		friend class Xbox360ProfileDriver;

		void Init(uint32 id);
		void Update();

		void QueueInit( int delay );

		bool LoggedInInternal();
		bool LoggedInToLIVEInternal();

		bool StartGamerPictureRead();

		void StartWriteTest();

	private:
		Xbox360ProfileDriver *mProfileDriver;

		uint32 mId;
		SexyString mGamertag;

		UserProfile *mPlayer;

		int mInitTimer;
		static const int MAX_PROFILE_SLOTS = 3;
		static const DWORD msProfileSettingIds[MAX_PROFILE_SLOTS];

		IOState mIOState;
		XOVERLAPPED mOverlapped;

		XUSER_SIGNIN_STATE mSigninState;
		XUID mXUID;
		XUID mOfflineXUID;

		XOVERLAPPED mGamerPictureOverlapped;
		D3DLOCKED_RECT mGamerpicRect;
		bool mReadingGamerPicture;
		bool mGamerPictureLoaded;
		DeviceImage *mGamerPicture;

		bool mLiveEnabled;
		bool mIsGuest;

		bool mIsLoaded;
		bool mIsSaved;

		bool mIsOnline;

		//reading
		DWORD mReadSize;
		XUSER_READ_PROFILE_SETTING_RESULT* pReadResults;

		//writing
		Buffer mWriteBuffer[MAX_PROFILE_SLOTS];
		XUSER_PROFILE_SETTING mWriteSettings[MAX_PROFILE_SLOTS];
	protected:
		friend class Xbox360AchievementContext;
		IAchievementContext* mAchievementRead;
		AchievementList mAchievements;

		void CheckAchievements();
	};

	class Xbox360ProfileDriver : public IProfileDriver, public Sexy::DialogListener
	{
		static const int NUM_PLAYERS = 4;
	public:

		bool Init();

		EProfileIOState Load();
		bool IsLoading(){ return false;};
		bool IsLoaded(){ return true;};

		EProfileIOState Save();
		bool IsSaving(){ return false; };
		bool IsSaved(){ return true; };

		bool HasError(){ return false; };

		void Update();

		uint32 GetNumProfiles();

		UserProfile* GetProfile(int index);
		UserProfile* GetProfile(const SexyString &theName);
		UserProfile* GetAnyProfile();

		UserProfile* AddProfile(const SexyString &theName);
		bool DeleteProfile(const SexyString &theName);
		bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName);
		void ClearProfiles();

		void SetDelaySignInChange( bool delay ){ mDelaySignInChange = delay; };

		Image *GetDefaultGamerPicture(){ return mDefaultGamerpic; };

	protected:
		friend class Xbox360ProfileData;
		friend class IProfileDriver;

		Xbox360ProfileDriver();

		void OnProfileChange( UserProfile *p );

	private:
		Xbox360AppDriver *mAppDriver;

		bool mInitialized;
		bool mDelaySignInChange;
		HANDLE mNotificationHandle;
		UserProfile *mPlayers[NUM_PLAYERS];

		Image *mDefaultGamerpic;
	};
}

#endif
