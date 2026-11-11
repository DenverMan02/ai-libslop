#ifndef __PROFILEMGR_H__
#define __PROFILEMGR_H__

#include "Common.h"
#include "UserProfile.h"
#include "IProfileDriver.h"



namespace Sexy
{
	class ProfileEventListener;

	//
	// Public interface for cross platform profile management.
	//
	// ProfileMgr manages a set of profiles, each representing an individual
	// user.  The game app supplies a ProfileEventListener for providing concrete
	// UserProfile objects, and handling notification and error callbacks.
	//
	// Most functions of the ProfileManager are delegated to a platform specific
	// driver implementing the IProfileDriver interface referenced from SexyAppBase::mProfileDriver.
	//
	class ProfileManager
	{
	public:
		ProfileManager( ProfileEventListener *listener );
		virtual ~ProfileManager();

		virtual bool Init();
		virtual void Update();

		virtual uint32 GetNumProfiles();

		virtual UserProfile* GetProfile(int index);
		virtual UserProfile* GetProfile(const SexyString &theName);
		virtual UserProfile* GetAnyProfile();
		
		virtual void ClearProfiles();
		virtual UserProfile* AddProfile(const SexyString &theName);
		virtual bool DeleteProfile(const SexyString &theName);
		virtual bool RenameProfile(const SexyString &theOldName, const SexyString &theNewName);

		uint32 GetProfileVersion();

		ProfileEventListener *GetListener();

		//this is only for driver use -- not to be called by game code.
		UserProfile *CreateUserProfile();
	protected:
		ProfileEventListener *mListener;
	};

	//
	// Data provider, and notification listener for profile events.
	//
	// Allows the Game app to instantiate it's own extended UserProfile objects, 
	// and recieve callbacks for profile changes and error states.
	//
	class ProfileEventListener
	{
	public:
		//Override to specify your current profile version.
		virtual uint32 GetProfileVersion(){return 0;};

		//Notification of profile changes
		virtual void NotifyProfileChanged( UserProfile *player ){};

		//If you extend UserProfile, override this function to return your custom UserProfile type.
		virtual UserProfile* CreateUserProfile(){ return new UserProfile(); };

		//Global profile load/save callbacks (in case you aren't extending UserProfile)
		virtual void OnProfileLoad( UserProfile *player, const Buffer &buffer ){};
		virtual void OnProfileSave( UserProfile *player, Buffer &buffer ){};
	};
}



#endif
