#ifndef NULLPROFILEDRIVER_H_INCLUDED
#define NULLPROFILEDRIVER_H_INCLUDED

#include "IProfileDriver.h"

#include <map>

namespace Sexy
{
	class UserProfile;

	class NullProfileData : public IProfileData
	{
		SexyString mName;
		uint8 mGamepadIndex;
	public:
		NullProfileData();

		bool SignedIn(){return false;};
		bool IsSigningIn(){return false;};
		bool IsOnline(){return false;};

		uint32 GetId();
		const SexyString &GetName();

		uint8 GetGamepadIndex() const;
		void SetGamepadIndex(uint8 gamepad);
		
		EProfileIOState LoadDetails();
		bool IsLoading();
		bool IsLoaded();
		
		EProfileIOState SaveDetails();
		bool IsSaving();
		bool IsSaved();

		bool HasError(){ return false; };
		
		bool ReadSummary(const Buffer &theData);
		bool WriteSummary(Buffer &theData);
		
		void DeleteUserFiles();

		Image *GetPlayerIcon();

		virtual bool IsAchievementUnlocked( AchievementId id ) { return false; }
		virtual IAchievementContext* StartUnlockAchievement( AchievementId id ) { return NULL; }
	};

	class NullProfileDriver : public IProfileDriver
	{
	public:
		NullProfileDriver();

		bool Init();

		bool HasError();

		void Update();

		uint32 GetNumProfiles();

		UserProfile* GetProfile(int index);
		UserProfile* GetProfile(const SexyString &theName);
		UserProfile* GetAnyProfile();

		UserProfile* AddProfile(const SexyString &theName);
		bool DeleteProfile(const SexyString &theName);
		bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName);
		void ClearProfiles();

	private:
		typedef std::map<SexyString,UserProfile *> ProfileMap;
		ProfileMap mProfileMap;
	};
}

#endif
