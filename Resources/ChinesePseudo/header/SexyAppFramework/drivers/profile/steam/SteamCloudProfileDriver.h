#ifndef STEAMCLOUDPROFILEDRIVER_H_INCLUDED
#define STEAMCLOUDPROFILEDRIVER_H_INCLUDED

#include "IProfileDriver.h"
#include "PlayerInfo.h"

#include "SmartPtr.h"

#include <string>
#include <map>

/*
	This is a rough first pass at a Steam backed cloud profile storage...
	Currently files are stored simliarly to the windows profile driver 
	(one manifest file listing users, and a file per user ).

	According to the Steam docs, the preferred method would be to have all the 
	users profile data in a single file, but this method should work too.
*/
namespace Sexy
{
	class SteamCloudProfileData : public IProfileData
	{
	public:
		SteamCloudProfileData( PlayerInfo *player );

		uint32 GetId(){ return mId; };
		std::string GetName(){ return mName; };

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
	private:
		friend class SteamCloudProfileDriver;

		PlayerInfo *mPlayer;

		void SetId( uint32 id){ mId = id; };
		void SetUseSeq( uint32 useSeq ){ mUseSeq = useSeq; };
		void SetName(std::string name){ mName = name; };

		DWORD mId;
		DWORD mUseSeq;
		std::string mName;

		bool mLoaded;
		bool mSaved;
	};

	class SteamCloudProfileDriver : public IProfileDriver
	{
		typedef std::map<std::string, SmartPtr<PlayerInfo>, Sexy::StringLessNoCase> ProfileMap;

	public:
		SteamCloudProfileDriver();

		bool Init();

		EProfileIOState Load();
		bool IsLoading(){ return false; };
		bool IsLoaded(){ return mIsLoaded; };

		EProfileIOState Save();
		bool IsSaving(){ return false; };
		bool IsSaved(){ return mIsSaved; };

		bool HasError(){ return mError; };

		void Update();

		uint32 GetNumProfiles();

		PlayerInfo* GetProfile(int index);
		PlayerInfo* GetProfile(const std::string &theName);
		PlayerInfo* GetAnyProfile();

		PlayerInfo* AddProfile(const std::string &theName);
		bool DeleteProfile(const std::string &theName);
		bool RenameProfile(const std::string &theOldName, const std::string &theNewName);
		void ClearProfiles();

		uint32 GetProfileVersion();
	protected:
		void DeleteOldestProfile();
		void DeleteOldProfiles();
		void DeleteProfile(ProfileMap::iterator theItr);

		bool ReadState(const Buffer &data);
		bool WriteState(Buffer &data);

	private:
		bool mIsLoaded;
		bool mIsSaved;
		bool mError;

		ProfileMap mProfileMap;
		DWORD mNextProfileId;
		DWORD mNextProfileUseSeq;
	};
};

#endif
