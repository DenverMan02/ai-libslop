
#pragma once
#include "IFacebookDriver.h"
#include "NetworkServiceManager.h"
#import "FacebookSDK.framework/Versions/Current/DeprecatedHeaders/Facebook.h"
using namespace Sexy;

namespace Sexy
{
	class IOSFacebookDriver;
}

@interface FBDriverDelegate : NSObject<UIApplicationDelegate,FBDialogDelegate>
{
	IOSFacebookDriver* mDriver;
}
@end

@interface CacheyMonster : FBSessionTokenCachingStrategy
{
	NSString* mUserDataKeyName;
	NSDictionary* mUserDataDict;
}
@property (copy) NSString* userDataKeyName;
@property (retain) NSDictionary* userDataDict;
@end

namespace Sexy
{
	
	class IOSFacebookDriver : public IFacebookDriver
	{
		typedef IFacebookDriver super;
		
	public:
		
		IOSFacebookDriver();
		~IOSFacebookDriver();

		void InitWithAppId( const std::string& appId );
		void SetUserDataFields( const std::string& userDataFields );
		bool OpenSessionForRead( const std::string& readPermissions, bool allowLoginUI, SessionStateCallback callback );
		void ReathorizeForRead( const std::string& readPermissions, ReauthorizeCallback callback );
		void ReathorizeForPublish( const std::string& publishPermissions, DefaultAudience audience, ReauthorizeCallback callback );
		void CloseAndClearSession();

		bool IsOpen() const;
		bool IsOpening() const;
		SessionState GetSessionState() const;
		std::string GetUserId() const;
		const StructuredData* GetUserData() const;
		std::string GetAccessToken() const;
		time_t GetExpirationDate() const;
		const NetworkServiceProfile* ServiceProfile() const;
		void Update();
		
		void Dialog( const std::string& name, IFBDialogListener* listener );
		void Dialog( const std::string& name, const StructuredData* params, IFBDialogListener* listener );
		
		void ApplicationDidBecomeActive( UIApplication* application );
		void ApplicationWillTerminate( UIApplication* application );
		BOOL ApplicationHandleOpenURL( UIApplication* application, NSURL* url );
		BOOL ApplicationOpenURL( UIApplication* application, NSURL* url, NSString* sourceApplication, id annotation );
		
		void DialogDidComplete( FBDialog* dialog );
		void DialogCompleteWithUrl( NSURL* url );
		void DialogDidNotCompleteWithUrl( NSURL* url );
		void DialogDidNotComplete( FBDialog* dialog );
		void DialogDidFailWithError( FBDialog* dialog, NSError* error );
		BOOL DialogShouldOpenURLInExternalBrowser( FBDialog* dialog, NSURL* url );

	private:

		SessionState RemapSessionState( FBSessionState fbss );
		void InitProfileParams();
		void RequestUserData( SessionStateCallback callback, SessionState incomingState );

		SessionState mSessionState;
		Facebook* mFacebook;
		FBDriverDelegate* mDelegate;
		std::string mUserDataFields;
		StructuredData mUserData;
		NetworkServiceProfile mServiceProfile;

		IFBDialogListener* mDialogListener;
		bool mDialogOpen;
		std::string mDialogName;

        NSString* mNSAppId;

#if defined(PRIME_FOR_BEJBLITZ) || defined(PRIME_FOR_PVZ2)
    public:
        int GetFriendCount() const;
        
    private:
        int mFBFriends;
#endif
	};

}
