/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/

#ifndef _IPSP_TICKER_H_
	#define _IPSP_TICKER_H_

#import <Foundation/Foundation.h>

@interface Ticker : NSObject <NSCoding, NSCopying> {
	int			m_iTickerId;
	NSString*	m_Title;
	NSString*	m_URL;
	NSString*	m_Message;
	NSString*	m_Type;
}

@property (nonatomic) int	m_iTickerId;
@property (nonatomic, retain) NSString*	m_Title;
@property (nonatomic, retain) NSString*	m_URL;
@property (nonatomic, retain) NSString*	m_Message;
@property (nonatomic, retain) NSString*	m_Type;

@end

#endif