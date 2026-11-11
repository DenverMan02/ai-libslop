
#pragma once
#include <string>
#include <vector>
#include <map>
#include "Common.h"
#include "RtDelegate.h"

namespace Sexy
{
	class IFacebookDriver;
	class StructuredData;
	class NetworkServiceProfile;
	
	class IFBDialogListener
	{
	public:
		virtual void DialogDidComplete( const std::string& name, const StructuredData* results ) {}
		virtual void DialogWasCanceled( const std::string& name ) {}
		virtual void DialogDidFail( const std::string& name,  const StructuredData* error ) {}
		virtual bool DialogShouldOpenURLInExternalBrowser( const std::string& name, const std::string& url )
		{
			return false;
		}
	};
	
	/**
	 * () Interface Version 2.0
	 *    Significant update to the Facebook Driver interface to reflect
	 *    the Facebook SDK v3.x for iOS and Android.
	 */
	class IFacebookDriver
	{
	public:
		
		static IFacebookDriver* CreateFacebookDriver();

		enum SessionStateFlags
		{
			SessionTerminalFlag = 1 << 8,
			SessionOpenFlag = 1 << 9,
		};

		enum SessionState
		{
			SessionCreated                   = 0,
			SessionCreatedTokenLoaded        = 1,
			SessionCreatedOpening            = 2,
			SessionOpen                      = 1 | SessionOpenFlag,
			SessionOpenTokenExtended         = 2 | SessionOpenFlag,
			SessionClosedLoginFailed         = 1 | SessionTerminalFlag,
			SessionClosed                    = 2 | SessionTerminalFlag,

            SessionClosedNoPermissions       = 3 | SessionTerminalFlag,
		};

		enum DefaultAudience
		{
			AudienceNone,
			AudienceOnlyMe,
			AudienceFriends,
			AudienceEveryone,
		};

		typedef Delegate2<IFacebookDriver*,SessionState> SessionStateCallback;

		typedef Delegate2<IFacebookDriver*,bool> ReauthorizeCallback;

		static bool SessionIsOpenForState( SessionState state )
		{
			return 0 != ( static_cast<int>(state) & static_cast<int>(SessionOpenFlag) );
		}

		static bool SessionIsTerminalForState( SessionState state )
		{
			return 0 != ( static_cast<int>(state) & static_cast<int>(SessionTerminalFlag) );
		}

		virtual ~IFacebookDriver() {}
		
		/**
		 */
		virtual void InitWithAppId( const std::string& appId ) = 0;
		
		/**
		 * Set which fields of Facebook user data will be retrieved for
		 * the logged in user.  Default is "id,name,gender,picture".
		 */
		virtual void SetUserDataFields( const std::string& userDataFields ) = 0;
		
		/**
		 * @return true if the session was opened synchronously without presenting UI to the user.
		 * This occurs when there is a cached token available from a previous run of the application.
		 * If false is returned, this indicates that the session was not immediately opened, via cache.
		 */
		virtual bool OpenSessionForRead( const std::string& readPermissions, bool allowLoginUI, SessionStateCallback callback ) = 0;

		virtual void ReathorizeForRead( const std::string& readPermissions, ReauthorizeCallback callback ) = 0;

		virtual void ReathorizeForPublish( const std::string& publishPermissions, DefaultAudience audience, ReauthorizeCallback callback ) = 0;

		virtual void CloseAndClearSession() = 0;
		
		/**
		 * Call this method regularly to give the implementation a chance
		 * to process asynchronous activity.
		 */
		virtual void Update() = 0;
		
		virtual bool IsOpen() const = 0;
		virtual bool IsOpening() const = 0;
		virtual SessionState GetSessionState() const = 0;
		virtual std::string GetUserId() const = 0;
		virtual const StructuredData* GetUserData() const = 0;
		virtual std::string GetAccessToken() const = 0;
		virtual time_t GetExpirationDate() const = 0;
		virtual const NetworkServiceProfile* ServiceProfile() const = 0;
		
		virtual void Dialog( const std::string& name, IFBDialogListener* listener ) = 0;
		virtual void Dialog( const std::string& name, const StructuredData* params, IFBDialogListener* listener ) = 0;
		
#if defined(PRIME_FOR_BEJBLITZ) || defined(PRIME_FOR_PVZ2)
        virtual int GetFriendCount() const = 0;
#endif
	};

	RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(IFacebookDriver::SessionState);
}

