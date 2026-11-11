/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
 \*****************************/

#ifndef _IPSP_MESSAGE_H_
	#define _IPSP_MESSAGE_H_

#import <Foundation/Foundation.h>

@protocol MessageDelegate;

@interface IAMessage : NSObject <NSCopying, NSCoding, UIAlertViewDelegate>
{
@private
	id<MessageDelegate>	mDelegate;
	
	NSNumber*		mID;
	NSString*		mTitle;
	NSString*		mMessage;
	NSString*		mURL;
	NSString*		mBut1Title;
	NSString*		mBut2Title;
	NSString*		mBut3Title;
}

@property (nonatomic, retain)	id<MessageDelegate>	delegate;
@property (nonatomic, retain)	NSNumber*					messageId;
@property (nonatomic, retain)	NSString*					title;
@property (nonatomic, retain)	NSString*					message;
@property (nonatomic, retain)	NSString*					url;
@property (nonatomic, retain)	NSString*					but1;
@property (nonatomic, retain)	NSString*					but2;
@property (nonatomic, retain)	NSString*					but3;

/* Displays the message
*/
-(void)show;

@end

@protocol MessageDelegate <NSObject>
@optional
-(void)messageFinished:(IAMessage*)msg keep:(BOOL)keep;
@end

#endif //_IPSP_MESSAGE_H_