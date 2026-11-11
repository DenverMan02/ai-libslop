
#pragma once
#include <string>
#include <vector>

namespace Sexy
{
	class NetworkServiceManager;
	class NetworkServiceProfile;
	class StructuredData;
	
	class NotificationListener
	{
	public:
		virtual void DidRegisterForRemoteNotifications( const std::string& deviceToken ) {}
		virtual void DidReceiveRemoteNotification( const StructuredData* userInfo ) {}
		virtual void DidReceiveLocalNotification( const StructuredData* userInfo ) {}
        virtual void DidFailToRegisterForRemoteNotificationsWithError( const StructuredData* userInfo ) {}
	};

    /**
     * Version 1.1
     * -----
     * () Updated interfaces and implementation for the mark 2 PopCap Push Notification Service Provider.
     */
	class NotificationManager
	{
	public:
        
		/**
		 * An array of strings containing notification type short names.
		 * NOTE that these notification types are NOT the Apple notification
		 * types such as Badge, Sound, and Alert.
		 */
		typedef std::vector< std::string > NotificationTypes;
		
		/**
		 * Get the shared instance of NotificationManager.  May return NULL
		 * if the instance has not been created.
		 * Call SharedNotificationManagerRequired() if you need to make sure
		 * the instance is created.
		 */
		static NotificationManager* SharedNotificationManagerOptional();
		
		/**
		 * Get the shared instance of NotificationManager.  The instance
		 * will be created if it does not already exist.
		 */
		static NotificationManager* SharedNotificationManagerRequired();
		
		/**
		 * Delete the shared instance of NotificationManager.
		 */
		static void DeleteSharedNotificationManager();
		
		/**
		 * If for some reason, you want to know if the app is provisioned
		 * for a production push environment, this will tell you.
		 */
		virtual bool IsProductionEnvironment() const = 0;
		
		/**
		 * For debugging purposes.
		 */
		virtual const std::string& DeploymentId() const = 0;
		
		/**
		 * For debugging purposes.
		 */
		virtual const std::string& DeviceToken() const = 0; 
        
        /**
         * true if the device has a user alias registered with the provider
         */
        virtual bool HasRegisteredUserAlias() const = 0;
		
		/**
		 * Optional call to set the Provider server URL.
		 */
		virtual void SetProviderEndpoint( const std::string& endpoint ) = 0;
        
		virtual const std::string& ProviderEndpoint() = 0;
        
		virtual void SetProviderAuth( const std::string& username, const std::string& password ) = 0;
		
		/**
		 * Not implemented yet.
		 */
		virtual void ScheduleLocalNotification( const StructuredData* notification ) = 0;
        
		/**
		 * Send a notification to another user of this application.
		 * Sending notifications directly from the client is discouraged for
		 * production environments and the server will probably be configured
		 * to reject these requests.  Use during prototyping and early
		 * development only.
		 * @param recipient The userAlias of the recipient.
		 * @param expiry A fixed UNIX epoch date expressed in seconds (UTC)
		 *   that identifies when the notification is no longer valid and can
		 *   be discarded.
		 * @param payload The notification payload as documented by Apple.
		 *   See https://developer.apple.com/library/ios/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/RemoteNotificationsPG.pdf
		 */
		virtual void SendRemoteNotification( const std::string& recipient, time_t expiry, const StructuredData* payload ) = 0;
        
		/**
		 * Call this during application startup to obtain a device token.
		 * @param userAlias A user identifier to associate with this device.
		 */
		virtual void RegisterForRemoteNotifications() = 0;
		
		/**
		 * You would not normally call this.  You would only unregister for
		 * notifications if the feature was removed from the app in a later
		 * update.
		 */
		virtual void UnregisterForRemoteNotifications() = 0;
        
		/**
		 * Transmit the device token, user alias, and an optional list of
		 * notification types to the push notification service provider.
		 * NOTE that these notification types are NOT the Apple notification
		 * types such as Badge, Sound, and Alert.  They are application
		 * defined types that refer to particular types of content about
		 * which the user is to be notified.
		 */
		virtual void UpdateTokenRegistration( const std::string& userAlias, const NotificationTypes& notificationTypes = NotificationTypes() ) = 0;
        
		virtual void AddNotificationListener( NotificationListener* listener ) = 0;
		virtual void RemoveNotificationListener( NotificationListener* listener ) = 0;
		
// PVZ CHANGE BEGIN - dsiems passing startup notifications through to our app.
		virtual bool HasStartupNotification() { return false; }
		virtual StructuredData* GetStartupNotification() { return NULL; }
// PVZ CHANGE END

        virtual const std::string VersionString() const = 0;

	protected:
		
		NotificationManager() {};
		virtual ~NotificationManager() {};
		
		
	};
    
}
