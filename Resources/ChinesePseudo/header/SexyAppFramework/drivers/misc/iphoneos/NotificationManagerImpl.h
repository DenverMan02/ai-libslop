
#pragma once
#include "NotificationManager.h"
#include "NetworkServiceManager.h"

namespace Sexy
{
	class NotificationManagerImpl;
}

@interface NotificationDelegate : NSObject<UIApplicationDelegate>
{
	Sexy::NotificationManagerImpl* mNotificationManager;
}
-(id)initWithNotificationManager:(Sexy::NotificationManagerImpl*)notificationManager;
@end


namespace Sexy
{
	class NotificationManagerImpl
    : public NotificationManager
    , public NetworkServiceListener
	{
	public:
		
		NotificationManagerImpl();
		~NotificationManagerImpl();
        
		bool IsProductionEnvironment() const;
		const std::string& DeploymentId() const;
		const std::string& DeviceToken() const;
        bool HasRegisteredUserAlias() const;
		
		void SetProviderEndpoint( const std::string& endpoint );
		const std::string& ProviderEndpoint();
		
		void SetProviderAuth( const std::string& username, const std::string& password );
		
		void ScheduleLocalNotification( const StructuredData* notification );
		void SendRemoteNotification( const std::string& recipient, time_t expiry, const StructuredData* payload );
		
		void RegisterForRemoteNotifications();
		void UnregisterForRemoteNotifications();
        
		void UpdateTokenRegistration( const std::string& userAlias, const NotificationTypes& notificationTypes );
        
		void AddNotificationListener( NotificationListener* listener );
		void RemoveNotificationListener( NotificationListener* listener );
        
        const std::string VersionString() const;

		void ApplicationDidRegisterForRemoteNotificationsWithDeviceToken( NSData* deviceToken );
		void ApplicationDidFailToRegisterForRemoteNotificationsWithError( NSError* error );
		void ApplicationDidReceiveRemoteNotification( NSDictionary* userInfo );
		void ApplicationDidReceiveLocalNotification( UILocalNotification* notification );
        
		void ServiceRequestValidated( const StructuredData* response, const void* context );
		void ServiceRequestCompleted( const StructuredData* response, const void* context );
		void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
		void ServiceRequestCompleted( const Buffer* buffer, const void* context );
		void ServiceRequestFailed( const StructuredData* response, const void* context );
		
	protected:
        
		void DetermineEnvironment();
        void RegisterTokenWithProvider( const std::string& userAlias, const std::string& locale,
                                       const std::string& timezone, const NotificationTypes& notificationTypes);
		void FireDidRegisterForRemoteNotifications( const std::string& deviceToken );
		void FireDidReceiveRemoteNotification( const StructuredData* userInfo );
		void FireDidReceiveLocalNotification( const StructuredData* userInfo );
		void FireFailedRegisterForRemoteNotifications( const StructuredData* userInfo );
        void ExecuteQueuedProviderRegistration();

		typedef std::set< NotificationListener* > Listeners;
		
		NotificationDelegate* mDelegate;
		std::string mProviderEndpoint;
		std::string mAuthUsername;
		std::string mAuthPassword;
		std::string mApplicationAlias;
		std::string mDeploymentId;
		std::string mDeviceToken;
		NSMutableDictionary* mRegisteredToken;
		bool mSlackCerts;
		bool mProductionEnvironment;
		bool mEnableDebugTrace;
        bool mRemoteRegistrationInProgress;
        bool mHasQueuedRegistrationRequest;
        std::string mQueuedRegistrationUserAlias;
        NotificationTypes mQueuedRegistrationNotificationTypes;
        std::string mQueuedRegistrationLocale;
        std::string mQueuedRegistrationTimeZone;
		Listeners mListeners;
	};
	
}
