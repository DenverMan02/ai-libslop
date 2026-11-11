//
//  NotificationManagerGame.h
//  PlantsVersusZombies2
//
//  Game-side implementation of NotificationManager
//
//  (Pusher)
//
//  Created by Jason Emery on 4/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NotificationManagerGame__
#define __PlantsVersusZombies2__NotificationManagerGame__

#include <iostream>
#include "drivers/misc/iphoneos/NotificationManager.h"

class NotificationManagerGame : public Sexy::NotificationListener
{
public:
    NotificationManagerGame();
    ~NotificationManagerGame();
    
    void Init();
    void Register();
    void TestPushNotification(const std::string& message, const std::string& recipient_id);
    
    void AddListener( NotificationListener* listener );

    // Game-Specific Implementation
    const std::string GetCurrentEndpoint();

public:
    
    // Callbacks
    void DidRegisterForRemoteNotifications( const std::string& deviceToken );
    void DidReceiveRemoteNotification( const Sexy::StructuredData* userInfo );
    void DidReceiveLocalNotification( const Sexy::StructuredData* userInfo );
    void DidFailToRegisterForRemoteNotificationsWithError( const StructuredData* userInfo );
};



#endif /* defined(__PlantsVersusZombies2__NotificationManagerGame__) */
