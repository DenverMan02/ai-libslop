#ifndef PS3PROFILEDRIVER_H_INCLUDED
#define PS3PROFILEDRIVER_H_INCLUDED

#include "IProfileDriver.h"
#include "DialogListener.h"

#include "drivers/savegame/ps3/PS3SaveGameDriver.h"

#include <np.h>
#include <netex/libnetctl.h>

namespace Sexy
{
	class UserProfile;
	class DeviceImage;

	class PS3AppDriver;

	class PS3ProfileDriver : public IProfileDriver, public Sexy::DialogListener
	{
		static const int MAX_PROFILES = 4;
	public:
		PS3ProfileDriver();

		bool Init();

		void Update();
		bool HasError(){ return false;};

		uint32 GetNumProfiles();

		UserProfile* GetProfile(int index);
		UserProfile* GetProfile(const SexyString &theName);
		UserProfile* GetAnyProfile();

		UserProfile* AddProfile(const SexyString &theName);
		bool DeleteProfile(const SexyString &theName);
		bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName);
		void ClearProfiles();

		void SetDelaySignInChange( bool delay ){ mDelaySignInChange = delay; };

		void SetSaveGameName( const std::string &name ){ mSaveGameName = name; };

		static void NpManagerCallback( int eventId, int result, void *arg );

		void OnProfileChange( UserProfile *p );

		const std::string& GetProfileSegmentName(){ return mProfileSegmentName; };
	public:

		static bool gSignInDismissed;
		static void SysutilCallback( uint64_t status, uint64_t param, void *userData );

	protected:
		friend class PS3ProfileData;


		std::string mSaveGameName;
		std::string mProfileSegmentName;

		void UpdateSigninState();

	private:
		PS3AppDriver *mAppDriver;

		bool mInitialized;
		bool mDelaySignInChange;

		std::vector<UserProfile*> mPlayers;

		#define NP_POOL_SIZE (128*1024)
		uint8_t mNPPool[NP_POOL_SIZE];

	};



	class PS3ProfileData : public IProfileData
	{
		enum IOState
		{
			ERROR = -1,
			IDLE,
			LOADING,
			SAVING,
		};

	public:
		PS3ProfileData( UserProfile *player );

		//XXX: I think these should be in the driver now instead of the profile
		void StartSignIn();
		void EndSignIn();

		bool SignedIn();
		bool IsSigningIn();
		bool IsOnline();
		bool WantsOffline(){ return PS3ProfileDriver::gSignInDismissed; };

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

		SceNpId *GetNPId(){ return &mNPId; }

	protected:
		friend class PS3ProfileDriver;

		void Init(uint32 id);
		void Update();

	private:
		PS3ProfileDriver *mProfileDriver;

		uint32 mId;
		SexyString mName;
		SexyString mOnlineName;

		uint8 mGamepadIndex;

		int mNpState;
		SceNpId mNPId;

		//XXX: I think these should be in the driver now instead of the profile
		CellNetCtlNetStartDialogParam mNetStartParam;
		CellNetCtlNetStartDialogResult mNetStartResult;

		UserProfile *mPlayer;

		IOState mIOState;

		PS3SaveGameContext *mSaveGameContext;
		bool mIsLoaded;
		bool mIsSaved;

		bool mIsOnline;
	protected:
		friend class PS3AchievementDriver;
		IAchievementContext* mAchievementRead;
		AchievementList mAchievements;

		void CheckAchievements();
	};
}

#endif
