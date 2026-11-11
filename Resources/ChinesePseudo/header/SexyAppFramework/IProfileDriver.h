#ifndef IPROFILEDRIVER_H_INCLUDED
#define IPROFILEDRIVER_H_INCLUDED

#include "Common.h"
#include "Buffer.h"

#include "IAchievementDriver.h"

namespace Sexy
{
	class UserProfile;
	class ProfileManager;
	class Image;

	enum EProfileIOState
	{
		PROFILE_IO_ERROR = -1,
		PROFILE_IO_SUCCESS, //Profile data was already loaded, or could be loaded without an async operation. 
		PROFILE_IO_PENDING, //Profile operation is being preformed asynchronously.  Wait for IsLoaded(), IsSaved(), or HasError() to return true.
	};

	/*
		The ProfileDriver backs the ProfileManager for creating and managing
		a set of UserProfile objects.  On some platforms the driver will manage 
		a list of players, on others players might map directly to the signed in
		profile on a gamepad index.
	*/
	class IProfileDriver
	{
	public:
		//each concrete profile diver will implement this to return an instance of itself.
		static IProfileDriver* CreateProfileDriver();

		virtual ~IProfileDriver(){}

		//initialize the driver before use.
		virtual bool Init() = 0;

		virtual void Update() = 0;

		virtual uint32 GetNumProfiles() = 0;

		virtual UserProfile* GetProfile(int index) = 0;
		virtual UserProfile* GetProfile(const SexyString &theName) = 0;
		virtual UserProfile* GetAnyProfile() = 0;

		virtual UserProfile* AddProfile(const SexyString &theName) = 0;
		virtual bool DeleteProfile(const SexyString &theName) = 0;
		virtual bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName) = 0;
		virtual void ClearProfiles() = 0;
	};

	/*
		The interface for platform specific UserProfile delegate classes.
		Responsible for profile storage, achievement functions and more to come.

		Each UserProfile object holds a platform specific IProfileData instance.

		@see UserProfile.h
	*/
	class IProfileData
	{
	public:
		static IProfileData* CreateProfileData( UserProfile *player );

		virtual ~IProfileData() {};

		virtual uint32 GetId() = 0;
		virtual const SexyString &GetName() = 0;
		virtual Image *GetPlayerIcon() = 0;

		virtual uint8 GetGamepadIndex() const = 0;
		virtual void SetGamepadIndex( uint8 gamepad ) = 0;

		virtual bool SignedIn() = 0;
		virtual bool IsSigningIn() = 0;
		virtual bool IsOnline() = 0;
		
		virtual EProfileIOState LoadDetails() = 0;
		virtual bool IsLoading() = 0;
		virtual bool IsLoaded() = 0;
		
		virtual EProfileIOState SaveDetails() = 0;
		virtual bool IsSaving() = 0;
		virtual bool IsSaved() = 0;

		virtual bool HasError() = 0;
		
		virtual void DeleteUserFiles() = 0;

		virtual bool IsAchievementUnlocked( AchievementId id ) = 0;
		virtual IAchievementContext* StartUnlockAchievement( AchievementId id ) = 0;
	};
};

#endif
