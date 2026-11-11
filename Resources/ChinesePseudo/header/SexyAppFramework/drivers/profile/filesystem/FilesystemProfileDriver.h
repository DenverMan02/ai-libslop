#pragma once
#ifndef FILESYSTEMPROFILEDRIVER_H_INCLUDED
#define FILESYSTEMPROFILEDRIVER_H_INCLUDED

#include "IProfileDriver.h"
#include "UserProfile.h"

#include <string>
#include <map>

namespace Sexy
{
	class FilesystemProfileData : public IProfileData
	{
	public:
		FilesystemProfileData( UserProfile *player );

		uint32 GetId(){ return mId; };
		const SexyString &GetName(){ return mName; };

		uint8 GetGamepadIndex() const {return mGamepad;}
		void SetGamepadIndex(uint8 gamepad){mGamepad = gamepad;};

		bool SignedIn(){ return true; };
		bool IsSigningIn(){ return false; };
		bool IsOnline(){ return false; };

		void DeleteUserFiles();

		EProfileIOState LoadDetails();
		bool IsLoading();
		bool IsLoaded();

		EProfileIOState SaveDetails();
		bool IsSaving();
		bool IsSaved();

		bool HasError();

		bool ReadSummary( const Buffer &data );
		bool WriteSummary( Buffer &data );

		Image *GetPlayerIcon();

		bool IsAchievementUnlocked( AchievementId id ){ return false; };
		IAchievementContext* StartUnlockAchievement( AchievementId id ){ return NULL; };

	private:
		friend class FilesystemProfileDriver;

		UserProfile *mPlayer;

		void SetId( uint32 id){ mId = id; };
		void SetUseSeq( uint32 useSeq ){ mUseSeq = useSeq; };
		void SetName(const SexyString &name){ mName = name; };

		uint32 mId;
		uint32 mUseSeq;
		SexyString mName;

		uint8 mGamepad;

		bool mLoaded;
		bool mSaved;
	};

	class FilesystemProfileDriver : public IProfileDriver
	{
		typedef std::map<SexyString, UserProfile*, Sexy::SexyStringLessNoCaseFunctor> ProfileMap;

	public:
		FilesystemProfileDriver();

		bool Init();
		void Update();
		bool HasError();

		uint32 GetNumProfiles();

		UserProfile* GetProfile(int index);
		UserProfile* GetProfile(const SexyString &theName);
		UserProfile* GetAnyProfile();

		UserProfile* AddProfile(const SexyString &theName);
		bool DeleteProfile(const SexyString &theName);
		bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName);
		void ClearProfiles();

		uint32 GetProfileVersion();
	protected:
		void Load();
		void Save();

		void DeleteOldestProfile();
		void DeleteOldProfiles();
		void DeleteProfile(ProfileMap::iterator theItr);

		bool ReadState(const Buffer &data);
		bool WriteState(Buffer &data);

	private:
		ProfileMap mProfileMap;
		uint32 mNextProfileId;
		uint32 mNextProfileUseSeq;
	};
};

#endif
