//
//  iCloudHandler.h
//  PCSP
//
//  Created by Yang Han on 2/28/13.
//  Copyright (c) 2013 Yang Han. All rights reserved.
//

#ifdef HOST_IPHONEOS

#import <Foundation/Foundation.h>


@protocol iCloudHandlerDelegate <NSObject>

@optional

// iCloud Account

// iCloud initialized properly without account changes
- (void)iCloudDidFinishInitialization;

// User changed iCloud Account
- (void)iCloudAccountDidChange;

// User signed out iCloud Account
- (void)iCloudAccountDidSignout;

// User launched the app w/iCloud enabled first time
- (void)iCloudAccountDidSignInFirstTime;

// Something goes wrong with iCloud service.
- (void)iCloudStorageNotAvailable;

// iCloud Data Section
/*
 A value changed in iCloud. This occurs when another device, running another instance of your app and attached to the same iCloud account, uploads a new value.
 */
- (void)iCloudDataServerChangeWithChangedKeys:(NSArray*)keys;

/*
 Your attempt to write to key-value storage was discarded because an initial download from iCloud has not yet happened. That is, before you can first write key-value data, the system must ensure that your app’s local, on-disk cache matches the truth in iCloud.
 Initial downloads happen the first time a device is connected to an iCloud account, and when a user switches their primary iCloud account.
 */
- (void)iCloudDataInitialSyncChange;

/*
 key-value store has exceeded its space quota on the iCloud server.
 */
- (void)iCloudDataQuataViolationChange;

/*
 The user has changed the primary iCloud account. The keys and values in the local key-value store have been replaced with those from the new account, regardless of the relative timestamps.
 */
- (void)iCloudDataAccountChange;

@end


@interface iCloudHandler : NSObject <iCloudHandlerDelegate>

@property (nonatomic, readonly) BOOL kvEnabled;
@property (nonatomic, readonly) BOOL available;

- (id)initWithParams:(NSDictionary*)params;

- (void)addDelegate:(id<iCloudHandlerDelegate>)delegate;

- (void)start;

- (void)sync;

- (void)saveKVString:(NSString*)str forKey:(NSString*)key;
- (void)saveKVInteger:(NSInteger)integer forKey:(NSString*)key;
- (void)saveKVBool:(BOOL)b forKey:(NSString*)key;
- (void)saveKVDouble:(double)number forKey:(NSString*)key;
- (void)saveKVFloat:(float)number forKey:(NSString*)key;
- (void)saveKVLong:(long)number forKey:(NSString*)key;

- (NSString*)getKVStringForKey:(NSString*)key;
- (NSInteger)getKVIntegerForKey:(NSString*)key;
- (BOOL)getKVBoolForKey:(NSString*)key;
- (double)getKVDoubleForKey:(NSString*)key;
- (float)getKVFloatForKey:(NSString*)key;
- (long)getKVLongForKey:(NSString*)key;

@end

#endif
