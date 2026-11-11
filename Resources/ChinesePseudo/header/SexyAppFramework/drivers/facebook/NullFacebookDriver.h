
#pragma once
#include "IFacebookDriver.h"
using namespace Sexy;

namespace Sexy
{
	
	class NullFacebookDriver : public IFacebookDriver
	{
	public:
        /**
		 */
		virtual void InitWithAppId( const std::string& appId ) {}
		
		/**
		 * Set which fields of Facebook user data will be retrieved for
		 * the logged in user.  Default is "id,name,gender,picture".
		 */
		virtual void SetUserDataFields( const std::string& userDataFields ) {}
		
		/**
		 * @return true if the session was opened synchronously without presenting UI to the user.
		 * This occurs when there is a cached token available from a previous run of the application.
		 * If false is returned, this indicates that the session was not immediately opened, via cache.
		 */
		virtual bool OpenSessionForRead( const std::string& readPermissions, bool allowLoginUI, SessionStateCallback callback ) { return false; }
        
		virtual void ReathorizeForRead( const std::string& readPermissions, ReauthorizeCallback callback ) {}
        
		virtual void ReathorizeForPublish( const std::string& publishPermissions, DefaultAudience audience, ReauthorizeCallback callback ) {}
        
		virtual void CloseAndClearSession() {}
		
		/**
		 * Call this method regularly to give the implementation a chance
		 * to process asynchronous activity.
		 */
		virtual void Update() {}
		
		virtual bool IsOpen() const { return false; }
		virtual bool IsOpening() const { return false; }
		virtual SessionState GetSessionState() const { return SessionClosed; }
		virtual std::string GetUserId() const { return ""; }
		virtual const StructuredData* GetUserData() const { return NULL; }
		virtual std::string GetAccessToken() const { return ""; }
		virtual time_t GetExpirationDate() const { return 0; }
		virtual const NetworkServiceProfile* ServiceProfile() const { return NULL; }
		
		virtual void Dialog( const std::string& name, IFBDialogListener* listener ) {}
		virtual void Dialog( const std::string& name, const StructuredData* params, IFBDialogListener* listener ) {}
        
#if defined(PRIME_FOR_BEJBLITZ) || defined(PRIME_FOR_PVZ2)
        int GetFriendCount() const { return 0; }
#endif
        
	};
	
}
