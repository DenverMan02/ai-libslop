#ifndef __USERPROFILE_H__
#define __USERPROFILE_H__

#include "Common.h"
#include "Buffer.h"

#include "IProfileDriver.h"
#include "IAchievementDriver.h"

#include "IAsyncTask.h"

namespace Sexy
{
	/*
	 * Base player info class, typically extended in game code to represent a player.
	 *
	 * Provides an integer id and name for the player (Games should not save these as they are handled differently per platform).
     *
	 * Supports loading and saving game settings and progress in a cross platform manner via a platform
	 * specific IProfileData delegate.  Also supports larger 'GameSave' reads/writes which are stored separately
	 * from profile data.
	 *
	 * Classes extending UserProfile should implement ReadProfileSettings and WriteProfileSettings
	 * to load and save game state from the supplied buffer.  Similarly the GameSave functions can read/write
	 * from a save game based on the supplied context.
	 */
	class UserProfile
	{
	public:
		UserProfile();
		virtual ~UserProfile();
		
		virtual uint32 GetId() const;
		virtual const SexyString &GetName() const;
		
		virtual uint8 GetGamepadIndex() const;
		virtual void SetGamepadIndex( uint8 gamepad );

		virtual void Reset(){};
		virtual void DeleteUserFiles();
		
		virtual EProfileIOState LoadDetails();
		virtual bool IsLoading();
		virtual bool IsLoaded();

		virtual EProfileIOState SaveDetails();
		virtual bool IsSaving();
		virtual bool IsSaved();

		virtual bool HasError();

		virtual bool SignedIn();
		virtual bool IsSigningIn();

		virtual bool IsOnline();

		//Override to read/write game specific data from the supplied buffer
		virtual bool ReadProfileSettings( const Buffer &theData ){ return true;};
		virtual bool WriteProfileSettings( Buffer &theData ){ return true;};

		//Achievement functions
		bool IsAchievementUnlocked( AchievementId id );
		IAchievementContext* StartUnlockAchievement( AchievementId id );

		//Driver specific profile data, only drivers should need to use this.
		IProfileData *GetPlatformData(){return mPlatformData;};

	private:
		IProfileData *mPlatformData;
	};
}

#endif //__USERPROFILE_H__
