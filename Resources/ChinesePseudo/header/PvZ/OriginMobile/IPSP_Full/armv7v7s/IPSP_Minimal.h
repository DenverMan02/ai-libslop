/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/

#import "Constants.h"

#ifndef _IPSP_MINIMAL_H_
	#define _IPSP_MINIMAL_H_

// -- Event Handler
typedef void(*MTX_EventCallBack)(MTX_EventID sEventID, int requestId, void* vpUserData);

//Registers an event handler
extern bool RegisterHandler(MTX_EventCallBack pEventHandler);

//Weak-links checks
extern bool IsStoreAvailable();

//Unregisters an event handler
extern bool UnregisterHandler(MTX_EventCallBack pEventHandler);

//sets the tracking events sending start time, time inteval and maximum cache events.
extern bool SetLoggingConfig(double eventsPostStartTime, double eventsPostTimeInterval, double maxEventsCache);

//sets the tracking events disable or enable.
extern void SetLoggingDisable(bool disable);

//returns the tracking events disable value: True - disabled, false - enables.
extern bool GetLoggingDisable(void);

extern int RegisterDeviceToken(NSData* deviceToken);

//Logs at server the product id with UDID
extern bool LogEAServer(int eventType, int eventKeyType01, NSString* eventValue01, int eventKeyType02, NSString* eventValue02, NSDate* timestamp);

//Posts the events data forcefully
extern int PostEventsData();

//Posts the events data forcefully
extern int PostEventsByCount(int noOfEvents);

extern int GetBanner(int bannerType);

extern int GetTickers(int tickerType, int maxTickers);

extern int GetMessage(int messageType, bool show = true);

extern bool ShowMessage();

//Downloads item from Akamai directly
extern int DownloadGameAsset(NSString* itemIdentifier);

extern void PrintLog(NSString* message);

extern NSString* GetSessionId();

extern int GetStepNum();

//Cleans up objects
extern bool CleanIPSP(void);

extern bool IsConnectedToNetwork(void);
	
//Pause App
extern void PauseIPSP();

//Resume App
extern void ResumeIPSP();

// Get current synergy user Id
extern NSString* GetEAMobileUId();

//Setting the synergy user Id
extern void SetEAMobileUId(NSString* eauId);

//App entering into Background
extern void SendIPSPIntoBackground();

//App entering into Foreground
extern void BringIPSPIntoForeground();

//Returns the status of a product: true if it is purchased by a particular user else false
extern int DidInstallApp(int productSellId);

// Retrieves the app sell id
extern int GetAppSellId();

extern bool OpenURLFromIPSP(NSString* urlString);

extern void HandleOpenURL(NSURL* url);

extern NSString* GetLanguage();

extern void SetLanguage(NSString* languageCode);

//Returns EADeviceID
extern NSString* GetDeviceId();

NSString* GetMACAddress(bool encrypt);

extern void IPSPNotifyRemoteNotification(NSDictionary *userInfo);

extern void RetrieveServerURLs();

extern void SetFiksuTrackingDisable(bool disable);

extern bool UseUdid();
extern bool UseMacAddress();

NSString* GetSDKVersion();

NSString* GetEventIDName(MTX_EventID eventId);

extern NSString* getTargetedCrossPromotionTagFlag();

#endif // _IPSP_MINIMAL_H_
