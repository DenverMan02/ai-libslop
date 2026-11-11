//
//  PushNotifications.h
//
//  Created by David Siems on 10/15/2012.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
#if 0 // $$ DLB -- disabling as these are not being used currently
#ifndef ORIGINNOTIFICATIONS_H
#define ORIGINNOTIFICATIONS_H

#include "NotificationManager.h"
#include <set>
#include "StructuredData.h"

namespace Sexy
{
	class OriginNotificationHandler;
}

@interface OriginNotificationDelegate : NSObject<UIApplicationDelegate>
{
	Sexy::OriginNotificationHandler* m_notificationHandler;
}
-(id)initWithNotificationHandler:(Sexy::OriginNotificationHandler*)notificationHandler;
- (void)didReceiveStartupRemoteNotification:(NSDictionary*)notification;
- (void)didReceiveStartupLocalNotification:(UILocalNotification *)notification;
@end

namespace Sexy
{

class OriginNotificationHandler : public NotificationManager
{
	public:
		OriginNotificationHandler();
		~OriginNotificationHandler();

		bool IsProductionEnvironment();
		
		void SetServer(const std::string& url);
		const std::string& Server();
		
		void ScheduleLocalNotification(const StructuredData* notification);
		void SendRemoteNotification(const std::string& recipient, time_t expiry, const StructuredData* payload);
		
		void RegisterForRemoteNotifications(const std::string& userAlias);
		void UnregisterForRemoteNotifications();
		
		void AddNotificationListener(NotificationListener* listener);
		void RemoveNotificationListener(NotificationListener* listener);
		
		void ApplicationDidRegisterForRemoteNotificationsWithDeviceToken(NSData* deviceToken);
		void ApplicationDidFailToRegisterForRemoteNotificationsWithError(NSError* error);
		void ApplicationDidReceiveRemoteNotification(NSDictionary* userInfo);
		void ApplicationDidReceiveLocalNotification(UILocalNotification* notification);
		
		bool HasStartupNotification();
        StructuredData* GetStartupNotification();

		void ApplicationDidReceiveStartupLocalNotification(UILocalNotification* notification);
		void ApplicationDidReceiveStartupRemoteNotification(NSDictionary* userInfo);

        void UseNetworkServiceManager( NetworkServiceManager* nsm, const std::string& channel );
        void SetNetworkServiceProfile( const NetworkServiceProfile* profile );
    
        void ScheduleLocalNotification();
    
        void AddLocalNotificationListener( NotificationListener* listener );
        void RemoveLocalNotificationListener( NotificationListener* listener );
    
        void AddRemoteNotificationListener( NotificationListener* listener );
        void RemoveRemoteNotificationListener( NotificationListener* listener );
    
	private:
		void FireDidReceiveRemoteNotification(const StructuredData* userInfo);
		void FireDidReceiveLocalNotification(const StructuredData* userInfo);

		OriginNotificationDelegate* m_delegate;
    
        typedef std::set<NotificationListener*> Listeners;
		Listeners m_listeners;

		StructuredData m_startupNotification;
		bool m_hasStartupNotification;
	};
}

#endif
#endif // endif 0