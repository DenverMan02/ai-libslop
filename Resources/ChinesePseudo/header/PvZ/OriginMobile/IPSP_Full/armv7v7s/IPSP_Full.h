/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/

#ifndef _IPSP_FULL_H_
	#define _IPSP_FULL_H_

#import "IPSP_Minimal.h"
#import "Constants.h"

#if INCLUDE_EBISU_IDENTITY
@class SocialUserNew;
@class MayhemUser;
#endif

#define	PRODUCT_API_VERSION	@"1.1.3"
#define	USER_API_VERSION	@"1.0.0"
#define	DRM_API_VERSION		@"1.0.0"
#define	M2U_API_VERSION		@"1.0.1"
#define	TRACK_API_VERSION	@"1.0.2"
#define	CIPGL_API_VERSION	@"1.0.0"
#define	CLIENT_API_VERSION	@"1.0.2"
#define	S2S_API_VERSION		@"1.0.0"

// Activates the store (listens for transactions)
extern void ActivateMTXStore();

// Deactivates the store (stops listening for transactions)
extern void DeactivateMTXStore();

//Checks the purchased item is still valid or not
extern bool IsMTXItemAllowed(int itemSellId);

//Retrieves products list those matches the specified category.
extern int GetMTXItemsByCategory(NSString* categoryName, bool loadDescPacks = YES);

//Retrieves 5 latest products.
extern int GetNewMTXItems(bool loadDescPacks = YES);

//Retrieves all products.
extern int GetAllMTXItems(bool loadDescPacks = YES);

//Retrieves purchased products
extern int GetMyPurchasedMTXItems(bool loadDescPacks = YES);

//Downloads item from EA server
extern int DownloadMTXItem(int itemSellId);

//Contacts Apple Store and purchases specifies item
extern int PurchaseMTXItem(int itemSellId);

//Contacts Apple Store and purchases specifies item
extern int RestoreMTXItems();

extern int GetBanners(int bannerType);

extern int GetMTXCategories();

extern int GetNewMTXBadgesCount(void);

extern int GetMTXStoreBadgesCount();

extern void CancelNetworkRequest(int requestId);

extern int GetPercentDownloaded(int itemSellId);

extern bool HasPaidMTXItems();

extern NSData* GetUnzipData(NSData* zipData, NSString* fileName);

extern bool MTXItemInstalled(int itemSellId, bool status);

extern NSString* GetProductBuyURL(DEVICE_BUILD_TYPE buildType=DEVICE_BUILD_TYPE_UNSPECIFIED);

extern int DownloadPackFromURL(NSString* fileURL);

#if INCLUDE_SOCIAL	

extern int SendPushNotification (NSString* eaMobileIDs, NSString* templateID, NSDictionary* overrideValues, NSDictionary* customParams);

extern int CustomMayhemRequest(int requestMethod, NSString* requestURI, NSDictionary* requestHeaders, NSString* bodyString=nil);

extern int AuthenticateMayhem(NSString* applicationID, NSString* application, NSString* authMethod, NSString* authParam);

extern bool IsMayhemAuthenticated();

extern NSString* GetMayhemSessionKey();

extern NSString* GetMayhemServerUrl();

#endif // #if INCLUDE_SOCIAL	

//extern bool ShouldChangeInterfaceOrientation(UIInterfaceOrientation interfaceOrientation);

extern void GameOrientationChanged(UIInterfaceOrientation interfaceOrientation);

#if INCLUDE_EBISU_IDENTITY

extern int GetMayhemIds(NSArray* applicationIds);

extern int GetNucleusEntitlement(NSString* projectId=nil, NSString* groupName=nil, NSString* entitlementTag=nil);

extern int PostNucleusEntitlement(NSString* projectId, NSString* entitlementTag, NSString* nucleusProductId=nil, NSString* groupName=nil);

#endif // EBISU_IDENTITY

#if INCLUDE_ORIGIN_BRIDGE

extern void       EADPInitialize();

extern void       EADPShutdown();

extern void       OriginBridgeInitialize(NSString* bundleId=nil);

extern bool       OriginBridgeIsInitialized();

extern void       OriginBridgeUninitialize();

extern UIView*    OriginBridgeGetView(ORIGINBRIDGE_UIMODE mode);

extern void       OriginBridgeShowView(ORIGINBRIDGE_UIMODE mode);

extern void       OriginBridgeShowExpandedModeByPageId(ORIGINBRIDGE_EXPANDED_PAGEID pageId);

extern SocialUserNew*    GetUserById(NSString* friendId, eUserType type);

extern NSArray*   GetNewFriendList(eUserType type=eALL); //< TODO: rename

extern NSString*  GetAuthenticationToken(eUserType type);

extern SocialUserNew*    GetCurrentNewUser(); //< TODO: rename

extern MayhemUser*       GetCurrentMayhemUser();

extern int        GetSynergyIdsWithNucleusIds(NSArray* nucleusIds);

extern NSString*  GetTargetedPromotionFlags();

#endif // #if INCLUDE_ORIGIN_BRIDGE

extern BOOL SetIACConfig(IAC_Config configName = IAC_CONFIG_DL);

extern void GetImageFromCache(NSURL* imageURL, id receiver, SEL selector);

extern void CancelGetImageFromCache(NSURL* imageURL, id receiver);

extern void CancelGetImageFromCache(id receiver);

#endif // _IPSP_FULL_H_
