/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
 \*****************************/

#ifndef _IPSP_SOCIAL_USER_H_
	#define _IPSP_SOCIAL_USER_H_

#import <Foundation/Foundation.h>
#import "Constants.h"

@protocol SocialUserDelegate;
@class IdentityAvatar;

//------------------------------------------------------------------------
@interface OriginUser : NSObject
{
    NSString* nucleusId;
    NSString* displayname;
	NSString* firstname;
	NSString* lastname;
}

@property (nonatomic, strong) NSString*    nucleusId;
@property (nonatomic, strong) NSString*    displayname;
@property (nonatomic, strong) NSString*    firstname;
@property (nonatomic, strong) NSString*    lastname;

@end

//------------------------------------------------------------------------
@interface MayhemUser : NSObject
{
    NSString* mayhemId;
    NSString* mayhemApplication;
}

@property (nonatomic, strong) NSString*    mayhemId;
@property (nonatomic, strong) NSString*    mayhemApplication;

@end

//------------------------------------------------------------------------
@interface FacebookUser : NSObject
{
    NSString* facebookId;
    NSString* displayname;
    NSString* firstname;
    NSString* lastname;
    NSString* pictureUrl;
}

@property (nonatomic, strong) NSString*    facebookId;
@property (nonatomic, strong) NSString*    displayname;
@property (nonatomic, strong) NSString*    firstname;
@property (nonatomic, strong) NSString*    lastname;
@property (nonatomic, strong) NSString*    pictureUrl;

@end

//------------------------------------------------------------------------
@interface SocialUserNew : NSObject
{
    OriginUser*               origin;
    FacebookUser*             facebook;
    
    // Not from a social network, these are tracked by us (AEM, Mobile)
    NSString*                 lastPlayedGame;
    bool                      playedCurrentGame;
}

@property (nonatomic, strong) OriginUser*    origin;
@property (nonatomic, strong) FacebookUser*  facebook;
@property (nonatomic, strong) NSString*      lastPlayedGame;
@property (nonatomic, assign) bool           playedCurrentGame;

@end

#endif //_IPSP_SOCIAL_USER_H_

