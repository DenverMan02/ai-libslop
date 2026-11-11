/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
 \*****************************/

#ifndef _IPSP_DEFINES_H_
	#define _IPSP_DEFINES_H_

#import "Constants.h"

#define	EMAIL_INVITE_TEMPLATE_HTML			@"origin_invite_email"
#define	EMAIL_INVITE_TEMPLATE				@"origin_email_invite_template"
#define	SMS_INVITE_TEMPLATE					@"origin_invite_sms"
#define	FACEBOOK_INVITE_TEMPLATE			@"origin_invite_facebook"
#define CONTACTS_ACCESS_PERMISSIONS_TEMPLATE    @"origin_access_contacts_permissions"
#define GMAIL_ACCESS_PERMISSIONS_TEMPLATE       @"origin_access_gmail_permissions"

// Use this one for tests while CONTACTS_ACCESS_PERMISSIONS_TEMPLATE and GMAIL_ACCESS_PERMISSIONS_TEMPLATE templates do not exist
//#define CONTACTS_ACCESS_PERMISSIONS_TEMPLATE    @"origin_userPermission"

#define FRIEND_ACCEPT_NEWSFEED_CATEGORY 	@"origin_info"
#define FRIEND_ACCEPT_NEWSFEED_TEMPLATE 	@"origin_news_friendaccept"

#define CHALLENGE_SEND_NEWSFEED_CATEGORY 	@"origin_challenge"
#define CHALLENGE_SEND_NEWSFEED_TEMPLATE 	@"origin_news_challenge_casual"


#define ORIGIN_GLOBAL_LOGO_MESSAGE_TEMPLATE	@"origin_logo_message"
#define	ORIGIN_GLOBAL_LOGO_MESSAGE_CODE					@"origin_logo_dynamic"
#define	ORIGIN_LOGO_MESSAGE_USER_WELCOME_BACK_CODE		@"origin_logo_welcomeback"
#define	ORIGIN_LOGO_MESSAGE_USER_LOGGED_IN				@"origin_logo_loggedin"

#define MAYHEM_AUTH_METHOD					@"synergy"
#define ANONYMOUS_MAYHEM_AUTH_METHOD 		@"synergy_device"


#define	PRODUCT_ID_STR						@"%prodid%"
#define	PRODUCT_BUY_URL						@"http://mg.eamobile.com/?ep=mg&p=%prodid%"

#endif //_IPSP_DEFINES_H_
