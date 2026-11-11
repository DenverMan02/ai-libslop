/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
 \*****************************/

#ifndef _IPSP_NUCLEUS_ENTITLEMENT_H_
	#define _IPSP_NUCLEUS_ENTITLEMENT_H_

#import <Foundation/Foundation.h>

@interface IPSPNucleusEntitlement : NSObject<NSCopying, NSCoding> {

	NSString*		entitlementId;
	NSString*		version;
	NSString*		nucleusProductId;
	NSDate*			grantDate;
	NSDate*			terminationDate;
	bool			managedLifeCycle;
	NSString*		status;
	long			useCount;
	bool			isConsumable;
	NSString*		productCatalog;
	NSString*		entitlementTag;
	NSString*		statusReasonCode;
	NSString*		groupName;
	NSString*		entitlementSource;
	NSString*		entitlementType;
	NSString*		projectId;
}

// TODO: add a lot of properties. =P
@property (nonatomic, retain) NSString*		entitlementId;
@property (nonatomic, retain) NSString*		version;
@property (nonatomic, retain) NSString*		nucleusProductId;
@property (nonatomic, retain) NSDate*		grantDate;
@property (nonatomic, retain) NSDate*		terminationDate;
@property (nonatomic, assign) bool			managedLifeCycle;
@property (nonatomic, retain) NSString*		status;
@property (nonatomic, assign) long			useCount;
@property (nonatomic, assign) bool			isConsumable;
@property (nonatomic, retain) NSString*		productCatalog;
@property (nonatomic, retain) NSString*		entitlementTag;
@property (nonatomic, retain) NSString*		statusReasonCode;
@property (nonatomic, retain) NSString*		groupName;
@property (nonatomic, retain) NSString*		entitlementSource;
@property (nonatomic, retain) NSString*		entitlementType;
@property (nonatomic, retain) NSString*		projectId;

-(id) initWithNucleusDictionary:(NSDictionary*)dict;
						
@end

#endif //_IPSP_NUCLEUS_ENTITLEMENT_H_