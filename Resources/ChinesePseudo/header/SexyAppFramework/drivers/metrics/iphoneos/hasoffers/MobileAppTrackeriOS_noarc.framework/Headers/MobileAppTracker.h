#import <UIKit/UIDevice.h>
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import "MATEncrypter_noarc.h"
#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <netinet/in.h>
#import "Reachability.h"

#define MATVERSION @"1.12"

@protocol MobileAppTrackerDelegate
@optional
- (void)didSucceed:(id)data;
- (void)didFailWithError:(NSString*)errorMessage;
@end

@interface MobileAppTracker : NSObject
{
	NSMutableDictionary * parameters;
    NSMutableArray * queue;
}

@property (nonatomic, retain) NSMutableDictionary * parameters;
@property (nonatomic, retain) NSMutableArray * queue;
-(void)trackAction:(NSString*)_siteEventId withObjects:(NSMutableArray*)queryObjects;
- (void)initWithParams:(NSMutableDictionary *)params;
- (void)initWithAdvertiserId:(NSString*)aid key:(NSString*)key;
+ (id)sharedManager;
-(void)trackAction:(NSString *)_siteEventId;

@end

/********* Queue implementation ********/

@interface NSMutableArray (QueueAdditions)
- (id) pop;
- (void) push:(id)obj;
@end

/********* MNSURLConnection implementation ********/


@interface MNSURLConnection : NSURLConnection {
    NSURL * url;
    NSString * JSON;
}
@property (nonatomic, retain) NSURL * url;
@property (nonatomic, retain) NSString * JSON;

@end